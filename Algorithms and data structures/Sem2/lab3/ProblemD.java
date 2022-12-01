import java.io.*;
import java.util.ArrayList;

public class ProblemD {
    BufferedReader in;
    PrintWriter out;

    private class Element {
        String key;
        Map values;
        boolean deleted;

        Element(String key) {
            this.key = key;
            this.values = new Map();
            deleted = false;
        }
    }

    private class Map { // [хэш][значение]
        int mod = 5;
        int size = 0;
        ArrayList<ArrayList<String>> map = new ArrayList<>();

        Map() {
            for (int i = 0; i < 7; i++) {
                ArrayList<String> a = new ArrayList<>();
                map.add(a);
            }
        }

        int hash(String key) {
            long result = 0;
            for (int i = 0; i < key.length(); i++) {
                result += (i + 7) * key.charAt(i);
                result %= mod;
            }
            return (int) result;
        }

        void resize() {
            mod = 1237;
            ArrayList<ArrayList<String>> newList = new ArrayList<>();
            for (int i = 0; i < 1237; i++) {
                ArrayList<String> a = new ArrayList<>();
                newList.add(a);
            }
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < map.get(i).size(); j++) {
                    int index = hash(map.get(i).get(j));
                    newList.get(index).add(map.get(i).get(j));
                }
            }
            map = newList;
        }

        boolean exists(String key, int index) {
            for (int i = 0; i < map.get(index).size(); i++) {
                if (map.get(index).get(i).equals(key)) {
                    return true;
                }
            }
            return false;
        }

        void put(String key) {
            int keyHash = hash(key);
            if (exists(key, keyHash)) {
                return;
            }
            map.get(keyHash).add(key);
            size++;
            if (size > 23 && mod == 5) {
                resize();
            }
        }

        void print() {
            System.out.println("size: " + size);
            for (int i = 0; i < map.size(); i++) {
                System.out.print("Хэш" + i + ": ");
                for (int j = 0; j < map.get(i).size(); j++) {
                    System.out.print(map.get(i).get(j));
                }
                System.out.println();
            }
        }
    }

    private class MultiMap { // [хэш][ключ]
        int mod = 996487;
        ArrayList<ArrayList<Element>> hashMap;

        MultiMap() {
            hashMap = new ArrayList<>();
            for (int i = 0; i < mod; i++) {
                hashMap.add(new ArrayList<>());
            }
        }

        int hash(String key) {  // OK
            long result = 0;
            for (int i = 0; i < key.length(); i++) {
                result += (i + 1) * key.charAt(i) * 13;
                result %= mod;
            }
            return (int) result;
        }

        int exists(String key, int index) {  // OK
            for (int i = 0; i < hashMap.get(index).size(); i++) {
                if (hashMap.get(index).get(i).key.equals(key) && !hashMap.get(index).get(i).deleted) {
                    return i;
                }
            }
            return -1;
        }

        void put(String key, String value) {
            int index = hash(key);  // Посчитал хэш для ключа
            int indexOfKey = exists(key, index);  // Проверил есть ли элемент с таким ключом
            if (indexOfKey == -1) {
                Element element = new Element(key);
                element.values.put(value);
                hashMap.get(index).add(element);
                return;
            }
            hashMap.get(index).get(indexOfKey).values.put(value);
        }

        Element get(String key) {  // OK
            int index = hash(key);
            int indexOfKey = exists(key, index);
            if (indexOfKey != -1) {
                return hashMap.get(index).get(indexOfKey);
            }
            return null;
        }

        void delete(String key, String value) {  // OK
            Element element = get(key);
            if (element != null) {
                int valueHash = element.values.hash(value);
                if (element.values.map.get(valueHash).indexOf(value) != -1) {
                    element.values.map.get(valueHash).remove(value);
                    element.values.size--;
                }
            }
        }

        void deleteAll(String key) {  // OK
            Element element = get(key);
            if (element != null) {
                element.deleted = true;
                element.values = null;
            }
        }
    }

    public static void main(String[] args) {
        new ProblemD().run();
    }

    void run() {
        try {
            in = new BufferedReader(new FileReader("multimap.in"));
            out = new PrintWriter("multimap.out");
            String str = in.readLine();
            MultiMap multiMap = new MultiMap();
            while (str != null) {
                String[] a = str.split(" ");
                Element res;
                switch (a[0]) {
                    case "put":
                        multiMap.put(a[1], a[2]);
                        break;
                    case "get":
                        res = multiMap.get(a[1]);
                        if (res != null) {
                            out.print(res.values.size + " ");
                            for (int i = 0; i < res.values.map.size(); i++) {
                                for (int j = 0; j < res.values.map.get(i).size(); j++) {
                                    out.print(res.values.map.get(i).get(j) + " ");
                                }
                            }
                            out.println();
                            break;
                        }
                        out.println(0);
                        break;
                    case "deleteall":
                        multiMap.deleteAll(a[1]);
                        break;
                    default:
                        multiMap.delete(a[1], a[2]);
                }
                str = in.readLine();
            }
            out.close();
        } catch (IOException e) {
            System.out.println("Плюсы отстой");
        }
    }
}