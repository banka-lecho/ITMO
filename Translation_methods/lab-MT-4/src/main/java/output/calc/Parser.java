package output.calc;
import java.util.ArrayList;
import java.util.List;

public class Parser {
    private Lexer lex;

 	double acc = 0;
    public MainNode parse(String text) {
        lex = new Lexer();
        lex.setExpr(text);
        lex.nextToken();
        return main();
    }

    public Token PLUS() {
        Token t = lex.getCurToken();
        if (t.getType() != 0)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token MINUS() {
        Token t = lex.getCurToken();
        if (t.getType() != 1)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token DIV() {
        Token t = lex.getCurToken();
        if (t.getType() != 2)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token MUL() {
        Token t = lex.getCurToken();
        if (t.getType() != 3)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token CLPRTH() {
        Token t = lex.getCurToken();
        if (t.getType() != 4)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token OPNPRTH() {
        Token t = lex.getCurToken();
        if (t.getType() != 5)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token MOD() {
        Token t = lex.getCurToken();
        if (t.getType() != 6)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token SIN() {
        Token t = lex.getCurToken();
        if (t.getType() != 7)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token COS() {
        Token t = lex.getCurToken();
        if (t.getType() != 8)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token TAN() {
        Token t = lex.getCurToken();
        if (t.getType() != 9)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public Token NUM() {
        Token t = lex.getCurToken();
        if (t.getType() != 10)
            throw new IllegalArgumentException("Expected " + t.getType());
        lex.nextToken();
        return t;
    }

    public MainNode main() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
			case 9:
			case 5:
			case 6:
			case 8:
			case 10:
			case 7:
			case 1:
			{
				MainNode result = new MainNode();
				children.add(t());
				double old = acc; acc = children.get(0).val;
				children.add(e2());
				result.val = children.get(1).val; acc = old;
				result.setChildren(children);
				return result;
			}
			default:
				throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
		}
	}
    public E2Node e2() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
			case 6:
			case 4:
			case 11:
			{
				E2Node result = new E2Node();
				result.val = acc;
				result.setChildren(children);
				return result;
			}
			case 0:
			{
				E2Node result = new E2Node();
				children.add(PLUS());
				children.add(t());
				double old = acc; acc = acc + children.get(1).val;
				children.add(e2());
				result.val = children.get(2).val; acc = old;
				result.setChildren(children);
				return result;
			}
			case 1:
			{
				E2Node result = new E2Node();
				children.add(MINUS());
				children.add(t());
				double old = acc; acc = acc - children.get(1).val;
				children.add(e2());
				result.val = children.get(2).val; acc = old;
				result.setChildren(children);
				return result;
			}
			default:
				throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
		}
	}
    public TNode t() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
			case 9:
			case 5:
			case 6:
			case 8:
			case 10:
			case 7:
			case 1:
			{
				TNode result = new TNode();
				children.add(f());
				double old = acc; acc = children.get(0).val;
				children.add(t2());
				result.val = children.get(1).val; acc = old;
				result.setChildren(children);
				return result;
			}
			default:
				throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
		}
	}
    public T2Node t2() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
			case 6:
			case 4:
			case 11:
			case 0:
			case 1:
			{
				T2Node result = new T2Node();
				result.val = acc;
				result.setChildren(children);
				return result;
			}
			case 3:
			{
				T2Node result = new T2Node();
				children.add(MUL());
				children.add(f());
				double old = acc; acc = acc * children.get(1).val;
				children.add(t2());
				result.val = children.get(2).val; acc = old;
				result.setChildren(children);
				return result;
			}
			case 2:
			{
				T2Node result = new T2Node();
				children.add(DIV());
				children.add(f());
				double old = acc; acc = acc / children.get(1).val;
				children.add(t2());
				result.val = children.get(2).val; acc = old;
				result.setChildren(children);
				return result;
			}
			default:
				throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
		}
	}
    public FNode f() {
        List<Node> children = new ArrayList<>();
        switch (lex.getCurToken().getType()) {
			case 5:
			{
				FNode result = new FNode();
				children.add(OPNPRTH());
				children.add(main());
				children.add(CLPRTH());
				result.val = children.get(1).val;
				result.setChildren(children);
				return result;
			}
			case 10:
			{
				FNode result = new FNode();
				children.add(NUM());
				result.val = Integer.parseInt(children.get(0).getName());
				result.setChildren(children);
				return result;
			}
			case 6:
			{
				FNode result = new FNode();
				children.add(MOD());
				children.add(main());
				children.add(MOD());
				result.val = Math.abs(children.get(1).val);
				result.setChildren(children);
				return result;
			}
			case 7:
			{
				FNode result = new FNode();
				children.add(SIN());
				children.add(OPNPRTH());
				children.add(main());
				children.add(CLPRTH());
				result.val = Math.round(Math.sin(children.get(2).val));
				result.setChildren(children);
				return result;
			}
			case 8:
			{
				FNode result = new FNode();
				children.add(COS());
				children.add(OPNPRTH());
				children.add(main());
				children.add(CLPRTH());
				result.val = Math.round(Math.cos(children.get(2).val));
				result.setChildren(children);
				return result;
			}
			case 9:
			{
				FNode result = new FNode();
				children.add(TAN());
				children.add(OPNPRTH());
				children.add(main());
				children.add(CLPRTH());
				result.val = Math.round(Math.tan(children.get(2).val));
				result.setChildren(children);
				return result;
			}
			case 1:
			{
				FNode result = new FNode();
				children.add(MINUS());
				children.add(f());
				result.val = -children.get(1).val;
				result.setChildren(children);
				return result;
			}
			default:
				throw new IllegalArgumentException("Unexpected token: " + lex.getCurToken().getName());
		}
	}
}
