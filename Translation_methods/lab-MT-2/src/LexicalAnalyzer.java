import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

public class LexicalAnalyzer {
    InputStream is;
    int curChar;
    int curPos;
    Token curToken;

    public LexicalAnalyzer(InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    private boolean isBlank(int c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    private void nextChar() throws ParseException {
        curPos++;
        try {
            curChar = is.read();
        } catch (IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    public void nextToken() throws ParseException {
        while (isBlank(curChar)) {
            nextChar();
        }
        switch (curChar) {
            case '(':
                nextChar();
                curToken = Token.LPAREN;
                break;
            case ')':
                nextChar();
                curToken = Token.RPAREN;
                break;
            case 'a':
                check("nd", Token.AND);
                break;
            case 'o':
                check("r", Token.OR);
                break;
            case 'x':
                check("or", Token.XOR);
                break;
            case 'n':
                check("ot", Token.NOT);
                break;
            case '=':
                check(">", Token.IMPL);
                break;
            case -1:
                curToken = Token.END;
                break;
            default:
                if ('a' <= curChar && curChar <= 'z') {
                    nextChar();
                    if (isBlank(curChar)) {
                        nextChar();
                        curToken = Token.VAR;
                        break;
                    } else if (curChar == ')' || curChar == -1) {
                        curToken = Token.VAR;
                        break;
                    }
                }
                throw new ParseException("Illegal character " + (char) curChar, curPos);
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos;
    }

    private void check(String s, Token t) throws ParseException {
        nextChar();
        if (isBlank(curChar)) {
            nextChar();
            curToken = Token.VAR;
            return;
        }
        if (curChar == ')' || curChar == -1) {
            curToken = Token.VAR;
            return;
        }
        for (int i = 0; i < s.length(); i++) {
            if (curChar != s.charAt(i)) {
                throw new ParseException("Illegal character " + (char) curChar, curPos);
            }
            nextChar();
        }
        if (isBlank(curChar) || curChar == '(' || curChar == ')' || curChar == -1 ) {
            curToken = t;
            return;
        }
        throw new ParseException("Illegal character " + (char) curChar, curPos);
    }
}