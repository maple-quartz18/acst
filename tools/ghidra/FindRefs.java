// FindRefs.java —— 查某个地址/字符串的所有引用来源（含所属函数）
//
// 用法:
//   analyzeHeadless <proj> <name> -process <file> -noanalysis \
//     -scriptPath <此目录> -postScript FindRefs.java 0x10a880dae 0x10a880db3
//
// 与 FindSymbols 的区别：这里查的是"谁引用了这个地址"，
// 输出引用类型 + 引用点 + 所属函数，可直接拿去 DumpFunctions 反编译。

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;

public class FindRefs extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            println("用法: FindRefs.java <addr> [addr ...]");
            return;
        }
        ReferenceManager rm = currentProgram.getReferenceManager();
        for (String s : args) {
            Address a = toAddr(s);
            println("");
            println("=== refs to " + a + " ===");
            ReferenceIterator it = rm.getReferencesTo(a);
            int n = 0;
            while (it.hasNext()) {
                Reference r = it.next();
                Address from = r.getFromAddress();
                Function f = getFunctionContaining(from);
                String fn = f == null ? "(no function)"
                        : f.getName() + " @ " + f.getEntryPoint();
                println("  " + from + "\t" + r.getReferenceType() + "\t" + fn);
                n++;
            }
            if (n == 0) {
                println("  (none)");
            }
            println("  total=" + n);
        }
    }
}
