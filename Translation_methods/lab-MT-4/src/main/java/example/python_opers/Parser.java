package example.python_opers;

import java.util.ArrayList;
import java.util.List;

public class Parser {
    private Lexer lex;

    public MainNode parse(String text) {
        lex = new Lexer();
        lex.setExpr(text);
        lex.nextToken();
        return main();
    }
    public Token OPNPRTH() {
        Token t = lex.getCurToken();
        if (t.getType() != 0)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public Token CLPRTH() {
        Token t = lex.getCurToken();
        if (t.getType() != 1)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public Token AND() {
        Token t = lex.getCurToken();
        if (t.getType() != 2)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public Token OR() {
        Token t = lex.getCurToken();
        if (t.getType() != 3)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public Token XOR() {
        Token t = lex.getCurToken();
        if (t.getType() != 4)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public Token NOT() {
        Token t = lex.getCurToken();
        if (t.getType() != 5)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public Token VAR() {
        Token t = lex.getCurToken();
        if (t.getType() != 6)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }
    public MainNode main() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
            case 5:
            case 0:
            case 6: {
                MainNode result = new MainNode();
                children.add(t());
                children.add(ePrime());
                result.setChildren(children);
                return result;
            }
            default:
                throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
        }
    }
    public EPrimeNode ePrime() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
            case 3: {
                EPrimeNode result = new EPrimeNode();
                children.add(OR());
                children.add(t());
                children.add(ePrime());
                result.setChildren(children);
                return result;
            }
            case 4: {
                EPrimeNode result = new EPrimeNode();
                children.add(XOR());
                children.add(t());
                children.add(ePrime());
                result.setChildren(children);
                return result;
            }
            case 1:
            case 7: {
                return new EPrimeNode();
            }
            default:
                throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
        }
    }
    public TNode t() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
            case 5:
            case 0:
            case 6: {
                TNode result = new TNode();
                children.add(f());
                children.add(tPrime());
                result.setChildren(children);
                return result;
            }
            default:
                throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
        }
    }
    public TPrimeNode tPrime() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
            case 2: {
                TPrimeNode result = new TPrimeNode();
                children.add(AND());
                children.add(f());
                children.add(tPrime());
                result.setChildren(children);
                return result;
            }
            case 1:
            case 3:
            case 4:
            case 7: {
                return new TPrimeNode();
            }
            default:
                throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
        }
    }
    public FNode f() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
            case 5: {
                FNode result = new FNode();
                children.add(NOT());
                children.add(f());
                result.setChildren(children);
                return result;
            }
            case 0:
            case 6: {
                FNode result = new FNode();
                children.add(s());
                result.setChildren(children);
                return result;
            }
            default:
                throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
        }
    }
    public SNode s() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
            case 6: {
                SNode result = new SNode();
                children.add(VAR());
                result.setChildren(children);
                return result;
            }
            case 0: {
                SNode result = new SNode();
                children.add(OPNPRTH());
                children.add(main());
                children.add(CLPRTH());
                result.setChildren(children);
                return result;
            }
            default:
                throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
        }
    }
}