import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.CharStreams;

import java.io.*;

import parser.*;


public class Main {
    private static void runTest(String name) {
        try (BufferedWriter writer =
                     new BufferedWriter(new OutputStreamWriter(
                             new FileOutputStream("src/test/" + name)));
             BufferedReader reader =
                     new BufferedReader(new InputStreamReader(
                             new FileInputStream("src/main/java/tests/" + name)))
        ) {
            StringBuilder code = new StringBuilder();
            String next;
            while ((next = reader.readLine()) != null) {
                code.append(next).append("\n");
            }
            runANTLR(code.toString(), writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void runANTLR(String code, BufferedWriter writer) throws IOException {
        GrammarHaskellLexer lexer = new GrammarHaskellLexer(CharStreams.fromString(code));
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        GrammarHaskellParser parser = new GrammarHaskellParser(tokens);
        StringBuilder program = parser.code().value;
        writer.write(program.toString());
    }

    public static void main(String[] args) {
        String path = "src/main/java/tests";

        File directory = new File(path);
        int countFiles = 7;
        File[] files = directory.listFiles();
        if (files != null) {
            countFiles = files.length;
        } else {
            System.out.println("Директория не существует или не доступна");
        }
        for (int i = 7; i < countFiles + 1; i++) {
            String nameFile = "test" + i;
            runTest(nameFile);
        }
    }
}
