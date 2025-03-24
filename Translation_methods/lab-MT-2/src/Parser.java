import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.text.ParseException;


public class Parser {

    private static LexicalAnalyzer lex;

    private static Tree E(LexicalAnalyzer lex) throws ParseException, AssertionError {
        return new Tree("E", T(lex), EPrime(lex));
    }

    private static Tree EPrime(LexicalAnalyzer lex) throws ParseException, AssertionError {
        switch (lex.curToken()) {
            case OR:
                lex.nextToken();
                return new Tree("E'", new Tree("or"), T(lex), EPrime(lex));
            case XOR:
                lex.nextToken();
                return new Tree("E'", new Tree("xor"), T(lex), EPrime(lex));
        }
        return new Tree("E'", new Tree("eps"));
    }

    private static Tree T(LexicalAnalyzer lex) throws ParseException, AssertionError {
        return new Tree("T", K(lex), TPrime(lex));
    }

    private static Tree TPrime(LexicalAnalyzer lex) throws ParseException, AssertionError {
        if (lex.curToken() == Token.AND) {
            lex.nextToken();
            return new Tree("T'", new Tree("and"), K(lex), TPrime(lex));
        }
        return new Tree("T'", new Tree("eps"));
    }

    private static Tree K(LexicalAnalyzer lex) throws ParseException, AssertionError {
        return new Tree("K", F(lex), KPrime(lex));
    }

    private static Tree KPrime(LexicalAnalyzer lex) throws ParseException, AssertionError {
        if (lex.curToken == Token.IMPL) {
            lex.nextToken();
            return new Tree("K'", new Tree("=>"), F(lex), KPrime(lex));
        }
        return new Tree("K'", new Tree("eps"));
    }
    private static Tree F(LexicalAnalyzer lex) throws ParseException, AssertionError {
        if (lex.curToken == Token.NOT) {
            lex.nextToken();
            return new Tree("F", new Tree("not"), F(lex));
        }
        return new Tree("F", S(lex));
    }

    private static Tree S(LexicalAnalyzer lex) throws ParseException, AssertionError {
        switch (lex.curToken()) {
            case VAR -> {
                lex.nextToken();
                return new Tree("S", new Tree("var"));
            }
            case LPAREN -> {
                lex.nextToken();
                final Tree E = E(lex);
                expect(Token.RPAREN, lex);
                return new Tree("S", new Tree("("), E, new Tree(")"));
            }
            default -> throw error("Expected var or lbracket, actual: " + lex.curToken());
        }
    }

    private static void expect(Token token, LexicalAnalyzer lex) throws ParseException, AssertionError {
        if (lex.curToken() == token) {
            lex.nextToken();
            return;
        }
        throw error("Expect: %s, actual: %s".formatted(token, lex.curToken()));
    }

    private static ParseException error(final String msg) {
        return new ParseException(msg + ", pos: " + lex.curPos(), lex.curPos());
    }

    public static Tree parse(String s) throws ParseException {
        // короче, проблема в том, что я не перевожу curToken в END
        InputStream is = new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8));
        LexicalAnalyzer lex = new LexicalAnalyzer(is);
        lex.nextToken();
        Tree result = E(lex);
        if (lex.curToken() == Token.END)
            return result;
        else
            throw new AssertionError();
    }
}