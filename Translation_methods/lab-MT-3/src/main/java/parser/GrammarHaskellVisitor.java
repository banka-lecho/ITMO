package parser;// Generated from /Users/anastasiaspileva/Desktop/МТ/lab-MT-3/src/main/java/GrammarHaskell.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link GrammarHaskellParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface GrammarHaskellVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#code}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCode(GrammarHaskellParser.CodeContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#function}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction(GrammarHaskellParser.FunctionContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#headerFunc}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitHeaderFunc(GrammarHaskellParser.HeaderFuncContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#bodyFunc}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBodyFunc(GrammarHaskellParser.BodyFuncContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType(GrammarHaskellParser.TypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#args}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgs(GrammarHaskellParser.ArgsContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#oneArg}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOneArg(GrammarHaskellParser.OneArgContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#data}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitData(GrammarHaskellParser.DataContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#localStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLocalStatement(GrammarHaskellParser.LocalStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#condition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCondition(GrammarHaskellParser.ConditionContext ctx);
	/**
	 * Visit a parse tree produced by {@link GrammarHaskellParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(GrammarHaskellParser.ExpressionContext ctx);
}