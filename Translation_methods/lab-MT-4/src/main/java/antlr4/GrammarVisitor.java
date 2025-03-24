package antlr4;// Generated from /Users/anastasiaspileva/Desktop/MT/lab-MT-4/src/main/java/Grammar.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link GrammarParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface GrammarVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link GrammarParser#gram}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGram(GrammarParser.GramContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarParser#global}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGlobal(GrammarParser.GlobalContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarParser#acc}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAcc(GrammarParser.AccContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarParser#nontermRule}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNontermRule(GrammarParser.NontermRuleContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarParser#alt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAlt(GrammarParser.AltContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarParser#lexRule}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLexRule(GrammarParser.LexRuleContext ctx);
}