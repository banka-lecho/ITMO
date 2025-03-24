package entity;

public class LexRule implements Rule {
    private final String name;
    private final String rule;
    private final boolean isRegex;

    public LexRule(String name, String rule, boolean isRegex) {
        this.name = name;
        this.rule = rule;
        this.isRegex = isRegex;
    }

    @Override
    public String getName() {
        return name;
    }

    public String getRule() {
        return rule;
    }

    public boolean isRegex() {
        return isRegex;
    }
}
