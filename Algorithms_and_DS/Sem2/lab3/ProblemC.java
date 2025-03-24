import java.io.*;
import java.util.ArrayList;

public class ProblemC {
    BufferedReader in;
    PrintWriter out;

    private class Element {
        String key;
        String value;
        boolean deleted;
        Element next;
        Element prev;

        Element(String key, String value, Element next, Element prev) {
            this.key = key;
            this.value = value;
            deleted = false;
            this.next = next;
            this.prev = prev;
        }
    }

    private class LinkedMap {
        int mod = 996487;
        Element last = null;
        ArrayList<ArrayList<Element>> hashMap;

        LinkedMap() {
            hashMap = new ArrayList<>();
            for (int i = 0; i < mod; i++) {
                hashMap.add(new ArrayList<>());
            }
        }

        int hash(String key) {
            long result = 0;
            for (int i = 0; i < key.length(); i++) {
                result += (i + 1) * key.charAt(i) * 13;
                result %= mod;
            }
            return (int) result;
        }

        int exists(String key, int index) {
            for (int i = 0; i < hashMap.get(index).size(); i++) {
                if (hashMap.get(index).get(i).key.equals(key) && !hashMap.get(index).get(i).deleted) {
                    return i;
                }
            }
            return -1;
        }

        void put(String key, String value) {
            int index = hash(key);
            int indexOfKey = exists(key, index);
            if (indexOfKey != -1) {
                hashMap.get(index).get(indexOfKey).value = value;
            } else {
                Element newElement = new Element(key, value, null, last);
                hashMap.get(index).add(newElement);
                if (last != null) {
                    last.next = newElement;
                }
                last = newElement;
            }
        }

        Element get(String key) {
            int index = hash(key);
            int indexOfKey = exists(key, index);
            if (indexOfKey != -1) {
                return hashMap.get(index).get(indexOfKey);
            }
            return null;
        }

        Element prev(String key) {
            Element element = get(key);
            if (element == null) {
                return null;
            }
            return element.prev;
        }

        Element next(String key) {
            Element element = get(key);
            if (element == null) {
                return null;
            }
            return element.next;
        }

        void delete(String key) {
            Element element = get(key);
            if (element != null) {
                if (last == element) {
                    last = element.prev;
                }
                if (element.prev != null) {
                    element.prev.next = element.next;
                }
                if (element.next != null) {
                    element.next.prev = element.prev;
                }
                element.deleted = true;
            }
        }
    }

    public static void main(String[] args) {
        new ProblemC().run();
    }

    void run() {
        try {
            in = new BufferedReader(new FileReader("linkedmap.in"));
            out = new PrintWriter("linkedmap.out");
            String str = in.readLine();
            LinkedMap linkedMap = new LinkedMap();
            while (str != null) {
                String[] a = str.split(" ");
                Element res;
                switch (a[0]) {
                    case "put":
                        linkedMap.put(a[1], a[2]);
                        break;
                    case "get":
                        res = linkedMap.get(a[1]);
                        out.println(res != null ? res.value : "none");
                        break;
                    case "prev":
                        res = linkedMap.prev(a[1]);
                        out.println(res != null ? res.value : "none");
                        break;
                    case "next":
                        res = linkedMap.next(a[1]);
                        out.println(res != null ? res.value : "none");
                        break;
                    default:
                        linkedMap.delete(a[1]);
                }
                str = in.readLine();
            }
            out.close();
        } catch (IOException e) {
            System.out.println("Плюсы отстой");
        }
    }
}
