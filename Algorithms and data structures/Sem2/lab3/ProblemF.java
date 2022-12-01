import java.util.*;

public class ProblemF {
    static String zero = "Aa";
    static String one = "BB";

    private static String generate(int number, int length) {
        String binaryString = Integer.toBinaryString(number);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length - binaryString.length(); i++) {
            sb.append(zero);
        }
        for (int i = 0; i < binaryString.length(); i++) {
            if (binaryString.charAt(i) == '1') {
                sb.append(one);
            }
            else {
                sb.append(zero);
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        int length = Integer.toBinaryString(count).length();
        for (int i = 0; i < count; i++) {
            System.out.println(generate(i, length));
        }
    }
}
