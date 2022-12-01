import java.util.*;

public class ProblemG {
    ArrayList<ArrayList<Integer>> links = new ArrayList<>(); // вот тут храним матрицу смежности
    ArrayList<ArrayList<Integer>> links2 = new ArrayList<>();
    ArrayList<Boolean> deleted = new ArrayList<>(); // удалили или нет
    Queue<Integer> last = new LinkedList<>(); // просто надо для асимптотики
    ArrayList<Boolean> visit = new ArrayList<>();
    ArrayList<Integer> size = new ArrayList<>();

    private class Pair {
        int first;
        int second;

        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }

    Pair findCenter() {
        int count = 0;
        for (int i = 0; i < links.size(); i++) {
            if (links.get(i).size() == 1) {
                last.add(i);
                deleted.set(i, true);
                count++;
            }
        }
        while (count < links.size() - 3) {
            int number = last.remove();
            for (int i = 0; i < links.get(number).size(); i++) {
                if (checkLeaf(links.get(number).get(i))) {
                    last.add(links.get(number).get(i));
                    deleted.set(links.get(number).get(i), true);
                    count++;
                }
            }
        }
        int first = -1;
        for (int i = 1; i < deleted.size(); i++) {
            if (!deleted.get(i)) {
                if (first == -1) {
                    first = i;
                } else {
                    return new Pair(first, i);
                }
            }
        }
        return new Pair(first, -1);
    }

    boolean checkLeaf(int number) {
        int count = 0;
        for (int i = 0; i < links.get(number).size(); i++) {
            if (!deleted.get(links.get(number).get(i))) {
                count++;
                if (count > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    boolean check(int number) {
        if (number < 1 || links.get(number).size() != 2) {
            return false;
        }
        for (int i = 0; i < links.size(); i++) {
            visit.add(false);
            size.add(0);
        }
        dfs(number);
        links2 = links;
        for (int i = 0; i < links2.size(); i++) { // Посортили список смежности
            links2.get(i).sort(new Comparator<Integer>() {
                @Override
                public int compare(Integer o1, Integer o2) {
                    if (size.get(o1) >= size.get(o2)) {
                        return 1;
                    }
                    return -1;
                }
            });
        }
        for (int i = 0; i < visit.size(); i++) {
            visit.set(i, false);
        }
        visit.set(number, true);
        String first = dfs_forCheck(links.get(number).get(0), new StringBuilder()).toString();
        String second = dfs_forCheck(links.get(number).get(1), new StringBuilder()).toString();
        return first.equals(second);
    }

    int dfs(int number) {
        visit.set(number, true);
        int s = 0;
        for (int i = 0; i < links.get(number).size(); i++) {
            if (!visit.get(links.get(number).get(i))) {
                s += dfs(links.get(number).get(i));
            }
        }
        size.set(number, s + 1);
        return s + 1;
    }

    StringBuilder dfs_forCheck(int number, StringBuilder sb) {
        visit.set(number, true);
        sb.append("(");
        for (int i = 0; i < links2.get(number).size(); i++) {
            if (!visit.get(links2.get(number).get(i))) {
                dfs_forCheck(links2.get(number).get(i), sb);
            }
        }
        sb.append(")");
        return sb;
    }

    public static void main(String[] args) {
        new ProblemG().run();
    }

    void run() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        if (n % 2 == 0) {
            for (int i = 0; i < n - 1; i++) {
                int a = in.nextInt();
                int b = in.nextInt();
            }
            System.out.println("NO");
            return;
        }
        for (int i = 0; i < n + 1; i++) {
            ArrayList<Integer> a = new ArrayList<>();
            links.add(a);
            deleted.add(false);
        }
        for (int i = 0; i < n - 1; i++) {
            int first = in.nextInt();
            int second = in.nextInt();
            links.get(first).add(second);
            links.get(second).add(first);
        }
        Pair a = findCenter();
        int first = a.first;
        int second = a.second;
        if (check(first) || check(second)) {
            System.out.println("YES");
            return;
        }
        System.out.println("NO");
    }
}
