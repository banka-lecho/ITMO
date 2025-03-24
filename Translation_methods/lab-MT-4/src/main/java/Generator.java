import antlr4.GrammarLexer;
import antlr4.GrammarParser;
import entity.LexRule;
import entity.SyntRule;
import generators.LexerGenerator;
import generators.ParserGenerator;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.Lexer;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import utilites.GrammarListener;
import utilites.GrammarUtilities;

import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

public class Generator {

    private static void runParser(String pathTest, String pathDir, String pathPack) {
        try {
            String input = Files.readString(Paths.get(pathTest));
            Lexer lex = new GrammarLexer(CharStreams.fromString(input));
            GrammarParser parser = new GrammarParser(new CommonTokenStream(lex));
            GrammarListener listener = new GrammarListener();
            GrammarUtilities utilities = new GrammarUtilities();

            parser.addParseListener(listener);
            parser.gram();
            listener.checkGrammar();
            List<SyntRule> gr = listener.getGrammar().values().stream().flatMap(Collection::stream).collect(Collectors.toList());
            utilities.check(gr);
            System.out.println("Grammar check OK");
            System.out.println("\n");
            System.out.println(utilities.getFirstSet());
            System.out.println("\n");
            for (SyntRule rule : gr) {
                System.out.println(rule.getName() + " " + utilities.firstS(rule) + " " + rule.getDependencies());
            }

            List<LexRule> tokens = listener.getTokens();
            // generators
            LexerGenerator lexerGenerator = new LexerGenerator(Paths.get(pathDir, "Lexer.java"), pathPack);
            lexerGenerator.generate(tokens);
            ParserGenerator parserGenerator = new ParserGenerator(Paths.get(pathDir), pathPack, utilities);
            parserGenerator.generate(tokens, listener.getGrammar(), listener.getAttrs(), listener.getContext());
            System.out.println("SUCCESS");
        } catch (IOException e) {
            System.err.println("Error while reading input: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        String pathToCalcTest = "src/test/resources/grammar_calc.text";
        String pathToCalcDir = "src/main/java/output/calc/";
        String calcPackName = "output.calc";

        String pathToPythonTest = "src/test/resources/grammar_python.text";
        String pathToPythonDir = "src/main/java/output/python_opers/";
        String pythonPackName = "output.python_opers";

        runParser(pathToCalcTest, pathToCalcDir, calcPackName);
        runParser(pathToPythonTest, pathToPythonDir, pythonPackName);
    }
}
