// FindSymbols.java —— 在已分析项目里按正则搜索符号（类名/函数名/标签）
//
// 用法:
//   analyzeHeadless <proj> <name> -process <file> -noanalysis \
//     -scriptPath <此目录> -postScript FindSymbols.java "Inventory|Gear|Loadout"
//
// 用途：Ghidra 完整分析后，Mach-O 的 ObjC 类名/方法名/导出符号都在符号表里，
// 按关键词搜索比在 214 MB 里逐个反编译快得多。

import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

import java.util.regex.Pattern;

public class FindSymbols extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            println("用法: FindSymbols.java <regex>");
            return;
        }
        Pattern p = Pattern.compile(args[0], Pattern.CASE_INSENSITIVE);
        SymbolTable st = currentProgram.getSymbolTable();
        int n = 0;
        for (Symbol s : st.getAllSymbols(true)) {
            if (p.matcher(s.getName()).find()) {
                println(s.getAddress() + "\t" + s.getSymbolType() + "\t" + s.getName());
                if (++n >= 300) {
                    println("... 截断于 300 条");
                    break;
                }
            }
        }
        println("total=" + n);
    }
}
