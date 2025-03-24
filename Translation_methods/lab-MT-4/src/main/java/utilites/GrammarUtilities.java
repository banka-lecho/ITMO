package utilites;

import entity.SyntRule;

import java.io.IOException;
import java.util.*;

public class GrammarUtilities {
    private final Map<String, Set<String>> followSet = new HashMap<>();
    private final Map<List<String>, Set<String>> firstSet = new HashMap<>();
    private static final String EPS = "$EPS";

    private void buildFirstNT(List<SyntRule> gr) {
        gr.forEach(rule -> {
            List<String> lst = List.of(rule.getName());
            firstSet.put(lst, new HashSet<>());
        });
        boolean changed = true;
        while (changed) {
            changed = false;
            for (SyntRule rule : gr) {
                List<String> deps = rule.getDependencies();
                changed = changed || firstSet.get(List.of(rule.getName())).addAll(firstLemma(deps));
            }
        }
    }

    private Set<String> firstLemma(List<String> lst) {
        if (lst.isEmpty() || lst.getFirst().charAt(0) == '$') {
            return new HashSet<>(Set.of(EPS));
        }
        if (Character.isUpperCase(lst.getFirst().charAt(0))) {
            return new HashSet<>(Set.of(lst.getFirst()));
        }
        List<String> ntSeek = List.of(lst.getFirst());
        if (firstSet.get(ntSeek).contains(EPS)) {
            Set<String> res = new HashSet<>(firstSet.get(ntSeek));
            res.remove(EPS);
            Set<String> nxt = firstLemma(lst.subList(1, lst.size()));
            res.addAll(nxt);
            return res;
        }
        return firstSet.get(ntSeek);
    }

    private void buildFollow(List<SyntRule> gr) {
        gr.forEach(rule -> followSet.put(rule.getName(), new HashSet<>()));
        if (!followSet.containsKey("main")) {
            throw new IllegalArgumentException("<main> start rule is required");
        }
        followSet.put("main", new HashSet<>(Set.of("END")));
        boolean changed = true;
        while (changed) {
            changed = false;
            for (SyntRule rule : gr) {
                for (int i = 0; i < rule.getDependencies().size(); i++) {
                    if (Character.isLowerCase(rule.getDependencies().get(i).charAt(0))) {
                        Set<String> s = firstLemma(rule.getDependencies().subList(i + 1, rule.getDependencies().size()));
                        boolean rm = s.remove(EPS);
                        changed = changed || followSet.get(rule.getDependencies().get(i)).addAll(s);
                        if (rm) {
                            changed = changed || followSet.get(rule.getDependencies().get(i)).addAll(followSet.get(rule.getName()));
                        }
                    }
                }
            }
        }
    }

    public Map<List<String>, Set<String>> getFirstSet() {
        return firstSet;
    }

    public Map<String, Set<String>> getFollowSet() {
        return followSet;
    }

    public void check(final List<SyntRule> gr) throws IOException {
        buildFirstNT(gr);
        buildFollow(gr);
        for (int i = 0; i < gr.size(); i++) {
            for (int j = i + 1; j < gr.size(); j++) {
                if (gr.get(i).getName().equals(gr.get(j).getName())) {
                    Set<String> fst = firstLemma(gr.get(i).getDependencies());
                    Set<String> fstBeta = firstLemma(gr.get(j).getDependencies());
                    Set<String> chk;
                    if (fst.contains(EPS)) {
                        chk = new HashSet<>(fstBeta);
                        chk.retainAll(followSet.get(gr.get(i).getName()));
                    } else {
                        chk = new HashSet<>(fst);
                        chk.retainAll(fstBeta);
                    }
                    if (!chk.isEmpty()) {
                        throw new IOException("Grammar is not LL(1)");
                    }
                }
            }
        }
    }

    public Set<String> firstS(final SyntRule rule) {
        List<String> deps = rule.getDependencies();
        Set<String> cur = firstLemma(deps);
        if (cur.contains(EPS)) {
            cur.remove(EPS);
            cur.addAll(followSet.get(rule.getName()));
        }
        return cur;
    }
}
