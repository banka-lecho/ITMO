import example.python_opers.Parser;

public class PythonTest {
    public static void main(String[] args) {
        Parser parser = new Parser();
        String test = "a or c";
        parser.parse(test);
        System.out.println("test: a or c  -  OK");

        test = "a and c";
        parser.parse(test);
        System.out.println("test: a and c  -  OK");

        test = "a xor c";
        parser.parse(test);
        System.out.println("test: a xor c  -  OK");

        test = "not a";
        parser.parse(test);
        System.out.println("test: not a  -  OK");

        test = "(a and c)";
        parser.parse(test);
        System.out.println("test: (a and c) -  OK");

        test = "not b or ( a )";
        parser.parse(test);
        System.out.println("test: not b or ( a )  -  OK");

        test = "not not a or not b and not not not c";
        parser.parse(test);
        System.out.println("test: not not a or not b and not not not c  -  OK");


        try {
            parser.parse("a b");
        } catch (IllegalArgumentException e) {
            System.out.println("test: a b  -  Error was caught");
        }

        try {
            parser.parse("(a or b) + bjhbjhb");
        } catch (StringIndexOutOfBoundsException | IllegalArgumentException e) {
            System.out.println("test: (a or b) + bjhbjhb  -  Error was caught");
        }

        try {
            parser.parse("(not    a    or   (  b )");
        } catch (IllegalArgumentException e) {
            System.out.println("test: (not    a    or   (  b )  -  Error was caught");
        }
    }
}
