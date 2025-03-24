package output.calc;

import java.util.List;

public abstract class Node {
protected List<Node> children;
	public double val = 0;
    public List<Node> getChildren() {
        return children;
    }

    public void setChildren(List<Node> children) {
        this.children = children;
    }

    public abstract String getName();
}