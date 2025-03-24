package output.calc;
import java.util.HashMap;
import java.util.Map;
public class Lexer {
    private String expr;
    private StringBuilder consumed = new StringBuilder();
    private Map<Integer, String> regexes = new HashMap<>();
    private Map<Integer, String> stricts = new HashMap<>();
    private int endId = 11;
    private int stringPtr;
    private Token curToken;
    private String lastConsumed;
	public Lexer() {
		stricts.put(0, "+");
		stricts.put(1, "-");
		stricts.put(2, "/");
		stricts.put(3, "*");
		stricts.put(4, ")");
		stricts.put(5, "(");
		stricts.put(6, "|");
		stricts.put(7, "sin");
		stricts.put(8, "cos");
		stricts.put(9, "tan");
		regexes.put(10, "(-)*[0-9]+");
	}
	public void setExpr(final String expr) {
        this.expr = expr;
    }

    private void skip() {
        while (stringPtr < expr.length() && Character.isWhitespace(expr.charAt(stringPtr))) {
            stringPtr++;
        }
    }

    public Token getCurToken() {
        return curToken;
    }

    public void nextToken() {
        skip();
        if (stringPtr >= expr.length()) {
            curToken = new Token(endId, "");
            return;
        }
        for (int i = 0; i < endId; i++) {
            if (stricts.containsKey(i) && expr.length() - stringPtr >= stricts.get(i).length()) {
                String s = expr.substring(stringPtr, stringPtr + stricts.get(i).length());
                if (s.equals(stricts.get(i))) {
                    flush(s, i);
                    stringPtr += s.length();
                    return;
                }
            }
        }
        while (true) {
            consumed.append(expr.charAt(stringPtr++));
            String s = consumed.toString();
            for (int i = 0; i < endId; i++) {
                if (regexes.containsKey(i) && s.matches(regexes.get(i))) {
                    while (s.matches(regexes.get(i)) && stringPtr < expr.length()) {
                        consumed.append(expr.charAt(stringPtr++));
                        s = consumed.toString();
                    }
                    if (!s.matches(regexes.get(i))) {
                        // pop back
                        consumed.setLength(consumed.length() - 1);
                        s = consumed.toString();
                        stringPtr--;
                    }
                    flush(s, i);
                    return;
                }
            }
        }
    }

    private void flush(String s, int i) {
        lastConsumed = s;
        curToken = new Token(i, s);
        consumed.setLength(0);
    }}
