import output.calc.Parser;

public class CalcTest {
    public static void main(String[] args) {
        Parser parser = new Parser();

        String test = "43343 + 234324 - 234234";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "1--2";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "2 + 2 * 2";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "7 / 3";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "1 - 2 -(1 -2 -3)";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "(24 - 5) / 6 + 7";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "-34342 - -5";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "|-6 - -5|";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "-6 + |-5|";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "|-6| - -5";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        // test for mod
        test = "sin(90)";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "5 + sin(90)";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "sin(90) + 5";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "sin(90) + sin(90)";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "|-sin(90)|";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "||-sin(90)| - 5|";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        test = "-cos(90)| - 5 + cos(0) -- tan(1)";
        System.out.println("test: " + test + " = " + parser.parse(test).val);

        try {
            test = "55555 a 12";
            parser.parse("55555 a 12");
        } catch (StringIndexOutOfBoundsException | IllegalArgumentException e) {
            System.out.println("test: " + test + " = Error was caught");
        }

        try {
            test = "55555 3234324";
            parser.parse("55555 3234324");
        } catch (StringIndexOutOfBoundsException | IllegalArgumentException e) {
            System.out.println("test: " + test + " = Error was caught");
        }
    }
}
