import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;


public class TestParser {

    @Test
    public void base_tests_correct() {
        ArrayList<String> lines = new ArrayList<>(Arrays.asList("a and b", "a or b", "a xor b", "not a", "a"));
        for (String line : lines) {
            System.out.println(expressionWithPrefix(line));
            try {
                Tree tr = Parser.parse(line);
                Assertions.assertNotNull(tr);
            } catch (final ParseException | NullPointerException | AssertionError e) {
                Assertions.fail(e.getMessage());
            }
        }
        System.out.println("\n");
    }

    @Test
    public void test_impl() {
        ArrayList<String> lines = new ArrayList<>(Arrays.asList("a => b", "(a => b) => ((b => c) => (a => c))",
                "(a and b) => a", "a => (a or b)", "a => not not a", "not not a => a"));
        for (String line : lines) {
            System.out.println(expressionWithPrefix(line));
            try {
                Tree tr = Parser.parse(line);
                Assertions.assertNotNull(tr);
            } catch (final ParseException | NullPointerException | AssertionError e) {
                Assertions.fail(e.getMessage());
            }
        }
        System.out.println("\n");
    }


    @Test
    public void test1_correct() {
        String line = "not b or ( a )";
        System.out.println(expressionWithPrefix(line));
        try {
            Tree tr = Parser.parse(line);
            Assertions.assertNotNull(tr);
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.fail(e.getMessage());
        }
        System.out.println("\n");
    }

    @Test
    public void test2_correct() {
        String line = "not not a or not b and not not not c";
        System.out.println(expressionWithPrefix(line));
        try {
            Tree tr = Parser.parse(line);
            Assertions.assertNotNull(tr);
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.fail(e.getMessage());
        }
        System.out.println("\n");
    }

    @Test
    public void test3_correct() {
        String line = "not (not (z and not d) and (d xor not b))";
        System.out.println(expressionWithPrefix(line));
        try {
            Tree tr = Parser.parse(line);
            Assertions.assertNotNull(tr);
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.fail(e.getMessage());
        }
        System.out.println("\n");
    }

    @Test
    public void test4_correct() {
        String line = "a and not b or c xor d";
        System.out.println(expressionWithPrefix(line));
        try {
            Tree tr = Parser.parse(line);
            Assertions.assertNotNull(tr);
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.fail(e.getMessage());
        }
        System.out.println("\n");
    }

    @Test
    public void test5_correct() {
        String line = "a     xor       not (a or b)";
        System.out.println(expressionWithPrefix(line));
        try {
            Tree tr = Parser.parse(line);
            Assertions.assertNotNull(tr);
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.fail(e.getMessage());
        }
        System.out.println("\n");
    }

    @Test
    public void test6_correct() {
        String line = "((a) or not (b)) xor (c xor c) or not (y xor not not x)";
        System.out.println(expressionWithPrefix(line));
        try {
            Tree tr = Parser.parse(line);
            Assertions.assertNotNull(tr);
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.fail(e.getMessage());
        }
        System.out.println("\n");
    }

    @Test
    public void base_tests_incorrect() {
        ArrayList<String> lines = new ArrayList<>(Arrays.asList("a b", "a b c", "a or", "xor a", "a xor a"));
        for (String line : lines) {
            System.out.println(expressionWithPrefix(line));
            try {
                Parser.parse(line);
                Assertions.fail();
            } catch (final ParseException | NullPointerException | AssertionError e) {
                Assertions.assertNotNull(e);
            }
            System.out.println("\n");
        }
    }

    @Test
    public void test1_incorrect() {
        String line = "a ornot b";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    @Test
    public void test2_incorrect() {
        String line = "a and or b or (c xor d)";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    @Test
    public void test3_incorrect() {
        String line = "not not a or not b and not not not c)";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    @Test
    public void test4_incorrect() {
        String line = "(not    a    or   (  b )";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    @Test
    public void test5_incorrect() {
        String line = "(a or b) + bjhbjhb";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    @Test
    public void test6_incorrect() {
        String line = "a or b not()";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    @Test
    public void test7_incorrect() {
        String line = "(a andnot b))";
        System.out.println(expressionWithPrefix(line));
        try {
            Parser.parse(line);
            Assertions.fail();
        } catch (final ParseException | NullPointerException | AssertionError e) {
            Assertions.assertNotNull(e);
        }
        System.out.println("\n");
    }

    private static String expressionWithPrefix(final String s) {
        return "expression: \"%s\"".formatted(s);
    }

    public static void toDot(String filename, String test) {
        try (FileWriter writer = new FileWriter(filename, false)) {
            try {
                Tree t = Parser.parse(test);
                writer.append(t.toDot(test));
            } catch (AssertionError e) {
                writer.append("test failed: ").append(e.getMessage());
            } catch (ParseException e) {
                writer.append("parse error: ").append(e.getMessage());
            }
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }

    public static void main(String[] args) {
        String filename = "testsOutput/output1.txt";
        toDot(filename, "a => b => c");
        filename = "testsOutput/output2.txt";
        toDot(filename, "not (not (j and n) and m)");
    }
}