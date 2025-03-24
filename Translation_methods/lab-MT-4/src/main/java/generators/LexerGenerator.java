package generators;

import entity.LexRule;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class LexerGenerator {
    private final Path destination;
    private final String pkgName;

    public LexerGenerator(Path destination, final String pkgName) {
        this.destination = destination;
        this.pkgName = pkgName;
    }

    public void generate(List<LexRule> tokens) {
        try (BufferedWriter writer = Files.newBufferedWriter(destination)) {
            if (pkgName != null) {
                writer.write("package " + pkgName + ";" + System.lineSeparator());
            }
            writer.write(
                    "import java.util.HashMap;\n" +
                            "import java.util.Map;\n");
            writer.write("public class Lexer {" + System.lineSeparator());
            writer.write("    private String expr;\n" +
                    "    private StringBuilder consumed = new StringBuilder();\n" +
                    "    private Map<Integer, String> regexes = new HashMap<>();\n" +
                    "    private Map<Integer, String> stricts = new HashMap<>();\n" +
                    "    private int endId = " + tokens.size() + ";\n" +
                    "    private int stringPtr;\n" +
                    "    private Token curToken;\n" +
                    "    private String lastConsumed;\n");
            writer.write("\tpublic Lexer() {\n");
            int id = 0;
            for (LexRule p : tokens) {
                if (p.isRegex()) {
                    writer.write("\t\tregexes.put(" + id + ", \"" + p.getRule() + "\");\n");
                } else {
                    writer.write("\t\tstricts.put(" + id + ", \"" + p.getRule() + "\");\n");
                }
                id++;
            }
            writer.write("\t}\n");
            writer.write("\tpublic void setExpr(final String expr) {\n" +
                    "        this.expr = expr;\n" +
                    "    }\n" +
                    "\n" +
                    "    private void skip() {\n" +
                    "        while (stringPtr < expr.length() && Character.isWhitespace(expr.charAt(stringPtr))) {\n" +
                    "            stringPtr++;\n" +
                    "        }\n" +
                    "    }\n" +
                    "\n" +
                    "    public Token getCurToken() {\n" +
                    "        return curToken;\n" +
                    "    }\n" +
                    "\n" +
                    "    public void nextToken() {\n" +
                    "        skip();\n" +
                    "        if (stringPtr >= expr.length()) {\n" +
                    "            curToken = new Token(endId, \"\");\n" +
                    "            return;\n" +
                    "        }\n" +
                    "        for (int i = 0; i < endId; i++) {\n" +
                    "            if (stricts.containsKey(i) && expr.length() - stringPtr >= stricts.get(i).length()) {\n" +
                    "                String s = expr.substring(stringPtr, stringPtr + stricts.get(i).length());\n" +
                    "                if (s.equals(stricts.get(i))) {\n" +
                    "                    flush(s, i);\n" +
                    "                    stringPtr += s.length();\n" +
                    "                    return;\n" +
                    "                }\n" +
                    "            }\n" +
                    "        }\n" +
                    "        while (true) {\n" +
                    "            consumed.append(expr.charAt(stringPtr++));\n" +
                    "            String s = consumed.toString();\n" +
                    "            for (int i = 0; i < endId; i++) {\n" +
                    "                if (regexes.containsKey(i) && s.matches(regexes.get(i))) {\n" +
                    "                    while (s.matches(regexes.get(i)) && stringPtr < expr.length()) {\n" +
                    "                        consumed.append(expr.charAt(stringPtr++));\n" +
                    "                        s = consumed.toString();\n" +
                    "                    }\n" +
                    "                    if (!s.matches(regexes.get(i))) {\n" +
                    "                        // pop back\n" +
                    "                        consumed.setLength(consumed.length() - 1);\n" +
                    "                        s = consumed.toString();\n" +
                    "                        stringPtr--;\n" +
                    "                    }\n" +
                    "                    flush(s, i);\n" +
                    "                    return;\n" +
                    "                }\n" +
                    "            }\n" +
                    "        }\n" +
                    "    }\n" +
                    "\n" +
                    "    private void flush(String s, int i) {\n" +
                    "        lastConsumed = s;\n" +
                    "        curToken = new Token(i, s);\n" +
                    "        consumed.setLength(0);\n" +
                    "    }");
            writer.write("}" + System.lineSeparator());
        } catch (IOException e) {
            System.err.println("Error while generating Lexer: " + e.getMessage());
        }
    }

}
