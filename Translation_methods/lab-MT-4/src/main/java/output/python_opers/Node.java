package output.python_opers;

import java.util.List;

public abstract class Node {
protected List<Node> children;
    public List<Node> getChildren() {
        return children;
    }

    public void setChildren(List<Node> children) {
        this.children = children;
    }

    public abstract String getName();
}