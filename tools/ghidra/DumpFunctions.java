// DumpFunctions.java —— Ghidra headless 定点反编译，跳过全量自动分析
//
// 用法（配合 -noanalysis）:
//   analyzeHeadless <proj_dir> <proj_name> -import <binary> -noanalysis \
//     -scriptPath <此目录> -postScript DumpFunctions.java 0x1002fbe5c 0x1002d6984
//
// 原理：Ghidra 导入 214 MB 的 Mach-O 只需数秒，耗时全在 auto-analysis。
// 我们已经有 addresses.txt 里的目标地址，只需对这几个地址反汇编 + 建函数 + 反编译。
// 输出为 Ghidra 伪代码，函数边界由 flow 推断，可能比全量分析略窄。

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.app.decompiler.ClangNode;
import ghidra.app.decompiler.ClangToken;
import ghidra.app.decompiler.ClangTokenGroup;

public class DumpFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            println("用法: DumpFunctions.java <addr> [addr ...]");
            return;
        }
        DecompInterface di = new DecompInterface();
        di.setSimplificationStyle("normalize");
        boolean opened = di.openProgram(currentProgram);
        println("openProgram=" + opened);
        ghidra.app.decompiler.DecompileOptions opts =
                new ghidra.app.decompiler.DecompileOptions();
        opts.grabFromProgram(currentProgram);
        di.setOptions(opts);
        println("toggleCCode=" + di.toggleCCode(true)
                + " toggleSyntaxTree=" + di.toggleSyntaxTree(true));
        for (String s : args) {
            Address a;
            try {
                a = toAddr(s);
            } catch (Exception e) {
                println("BAD ADDR " + s);
                continue;
            }
            boolean dis = disassemble(a);
            Function f = getFunctionAt(a);
            if (f == null) {
                f = getFunctionContaining(a);   // 传入的是函数体内地址时，取所属函数
            }
            if (f == null) {
                f = createFunction(a, null);
            }
            if (f == null) {
                println("SKIP no function at " + s + " (disassemble=" + dis + ")");
                continue;
            }
            println("INFO " + s + " disassemble=" + dis
                    + " body=" + f.getBody().getNumAddresses()
                    + " instructions=" + countInstructions(f));
            DecompileResults r = di.decompileFunction(f, 90, monitor);
            println("DIAG completed=" + r.decompileCompleted()
                    + " cancelled=" + r.isCancelled()
                    + " hf=" + (r.getHighFunction() != null));
            String code = null;
            if (r.getDecompiledFunction() != null) {
                code = r.getDecompiledFunction().getC();
            } else if (r.getCCodeMarkup() != null) {
                StringBuilder sb = new StringBuilder();
                collect(r.getCCodeMarkup(), sb);
                code = sb.toString();
            }
            if (!r.decompileCompleted() || code == null) {
                println("FAIL " + s + " (" + f.getName() + "): completed="
                        + r.decompileCompleted() + " msg=" + r.getErrorMessage());
                continue;
            }
            println("");
            println("/* ===== " + f.getName() + " @ " + a + " | "
                    + f.getBody().getNumAddresses() + " bytes ===== */");
            println(code == null ? "(no code)" : code);
        }
        di.dispose();
    }

    private void collect(ClangNode n, StringBuilder sb) {
        if (n instanceof ClangToken) {
            sb.append(((ClangToken) n).getText());
            return;
        }
        for (int i = 0; i < n.numChildren(); i++) {
            collect(n.Child(i), sb);
        }
    }

    private int countInstructions(Function f) {
        int n = 0;
        for (Instruction i : currentProgram.getListing().getInstructions(f.getBody(), true)) {
            n++;
        }
        return n;
    }
}
