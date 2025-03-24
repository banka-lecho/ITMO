package utilites;

import antlr4.GrammarBaseListener;
import antlr4.GrammarParser;
import entity.LexRule;
import entity.SyntRule;
import org.antlr.v4.runtime.tree.ParseTree;

import java.util.*;

public class GrammarListener extends GrammarBaseListener {
    private final List<LexRule> tokens = new ArrayList<>();
    private final Map<String, List<SyntRule>> grammar = new LinkedHashMap<>();
    private final List<String> attrs = new ArrayList<>();
    private final List<String> context = new ArrayList<>();
    private final Set<String> knownTransitions = new HashSet<>();

    @Override
    public void exitGlobal(GrammarParser.GlobalContext ctx) {
        String attr = ctx.VAR().getText().substring(1);
        attrs.add(attr);
    }

    @Override
    public void exitAcc(GrammarParser.AccContext ctx) {
        String acc = ctx.VARACC().getText().substring(1);
        context.add(acc);
    }


    @Override
    public void exitLexRule(GrammarParser.LexRuleContext ctx) {
        String tkName = ctx.TOKEN().getText();
        if (tkName.equals("END")) {
            throw new IllegalArgumentException("END token is reserved and cannot be used");
        }
        boolean isRegex = ctx.REGEX_RULE() != null;
        String rule = isRegex ? ctx.REGEX_RULE().getText() : ctx.STRING_RULE().getText();
        rule = rule.substring(1, rule.length() - 1);
        tokens.add(new LexRule(tkName, rule, isRegex));
        knownTransitions.add(tkName);
    }

    @Override
    public void exitNontermRule(GrammarParser.NontermRuleContext ctx) {
        String ntName = ctx.NONTERM().getText();
        List<ParseTree> ch = ctx.children;
        List<SyntRule> deps = new ArrayList<>();
        for (int i = 2; i < ch.size(); i += 2) {
            ParseTree cur = ch.get(i);
            if (cur.getChild(0) == null || cur.getChild(0).getText().startsWith("{")) {
                if (cur.getChild(0) == null) {
                    List<String> nullList = new ArrayList<>();
                    nullList.add(null);
                    deps.add(new SyntRule(ntName, List.of("$EPS"), nullList));
                } else {
                    String code = cur.getChild(0).getText();
                    deps.add(new SyntRule(ntName, List.of("$EPS"), List.of(code.substring(1, code.length() - 1))));
                }
            } else {
                List<String> seq = new ArrayList<>();
                List<String> codes = new ArrayList<>();
                for (int j = 0; j < cur.getChildCount(); j++) {
                    seq.add(cur.getChild(j).getText());
                    if (j + 1 < cur.getChildCount() && cur.getChild(j + 1).getText().startsWith("{")) {
                        String code = cur.getChild(j + 1).getText();
                        codes.add(code.substring(1, code.length() - 1));
                        j++;
                    } else {
                        codes.add(null);
                    }
                }
                deps.add(new SyntRule(ntName, seq, codes));
            }
        }
        knownTransitions.add(ntName);
        grammar.put(ntName, deps);
    }


    public List<LexRule> getTokens() {
        return tokens;
    }

    public Map<String, List<SyntRule>> getGrammar() {
        return grammar;
    }

    public void checkGrammar() {
        knownTransitions.add("$EPS");
        for (List<SyntRule> k : grammar.values()) {
            for (SyntRule l : k) {
                for (String s : l.getDependencies()) {
                    if (!knownTransitions.contains(s)) {
                        throw new IllegalArgumentException("Unknown transition: " + s);
                    }
                }
            }
        }
    }

    public List<String> getContext() {
        return context;
    }

    public List<String> getAttrs() {
        return attrs;
    }

    ;
}
