package antlr4;// Generated from /Users/anastasiaspileva/Desktop/MT/lab-MT-4/src/main/java/Grammar.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GrammarParser}.
 */
public interface GrammarListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GrammarParser#gram}.
	 * @param ctx the parse tree
	 */
	void enterGram(GrammarParser.GramContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#gram}.
	 * @param ctx the parse tree
	 */
	void exitGram(GrammarParser.GramContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#global}.
	 * @param ctx the parse tree
	 */
	void enterGlobal(GrammarParser.GlobalContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#global}.
	 * @param ctx the parse tree
	 */
	void exitGlobal(GrammarParser.GlobalContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#acc}.
	 * @param ctx the parse tree
	 */
	void enterAcc(GrammarParser.AccContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#acc}.
	 * @param ctx the parse tree
	 */
	void exitAcc(GrammarParser.AccContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#nontermRule}.
	 * @param ctx the parse tree
	 */
	void enterNontermRule(GrammarParser.NontermRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#nontermRule}.
	 * @param ctx the parse tree
	 */
	void exitNontermRule(GrammarParser.NontermRuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#alt}.
	 * @param ctx the parse tree
	 */
	void enterAlt(GrammarParser.AltContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#alt}.
	 * @param ctx the parse tree
	 */
	void exitAlt(GrammarParser.AltContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#lexRule}.
	 * @param ctx the parse tree
	 */
	void enterLexRule(GrammarParser.LexRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#lexRule}.
	 * @param ctx the parse tree
	 */
	void exitLexRule(GrammarParser.LexRuleContext ctx);
}