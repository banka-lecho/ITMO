package parser;// Generated from /Users/anastasiaspileva/Desktop/МТ/lab-MT-3/src/main/java/GrammarHaskell.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GrammarHaskellParser}.
 */
public interface GrammarHaskellListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#code}.
	 * @param ctx the parse tree
	 */
	void enterCode(GrammarHaskellParser.CodeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#code}.
	 * @param ctx the parse tree
	 */
	void exitCode(GrammarHaskellParser.CodeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(GrammarHaskellParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(GrammarHaskellParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#headerFunc}.
	 * @param ctx the parse tree
	 */
	void enterHeaderFunc(GrammarHaskellParser.HeaderFuncContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#headerFunc}.
	 * @param ctx the parse tree
	 */
	void exitHeaderFunc(GrammarHaskellParser.HeaderFuncContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#bodyFunc}.
	 * @param ctx the parse tree
	 */
	void enterBodyFunc(GrammarHaskellParser.BodyFuncContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#bodyFunc}.
	 * @param ctx the parse tree
	 */
	void exitBodyFunc(GrammarHaskellParser.BodyFuncContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(GrammarHaskellParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(GrammarHaskellParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#args}.
	 * @param ctx the parse tree
	 */
	void enterArgs(GrammarHaskellParser.ArgsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#args}.
	 * @param ctx the parse tree
	 */
	void exitArgs(GrammarHaskellParser.ArgsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#oneArg}.
	 * @param ctx the parse tree
	 */
	void enterOneArg(GrammarHaskellParser.OneArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#oneArg}.
	 * @param ctx the parse tree
	 */
	void exitOneArg(GrammarHaskellParser.OneArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#data}.
	 * @param ctx the parse tree
	 */
	void enterData(GrammarHaskellParser.DataContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#data}.
	 * @param ctx the parse tree
	 */
	void exitData(GrammarHaskellParser.DataContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#localStatement}.
	 * @param ctx the parse tree
	 */
	void enterLocalStatement(GrammarHaskellParser.LocalStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#localStatement}.
	 * @param ctx the parse tree
	 */
	void exitLocalStatement(GrammarHaskellParser.LocalStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#condition}.
	 * @param ctx the parse tree
	 */
	void enterCondition(GrammarHaskellParser.ConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#condition}.
	 * @param ctx the parse tree
	 */
	void exitCondition(GrammarHaskellParser.ConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarHaskellParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(GrammarHaskellParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarHaskellParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(GrammarHaskellParser.ExpressionContext ctx);
}