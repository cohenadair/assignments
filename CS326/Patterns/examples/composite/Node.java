public class Node implements CompositeInterface {
    private int value;
    private CompositeInterface right;
    private CompositeInterface left;
    
    public Node(int val, CompositeInterface leftNode, CompositeInterface rightNode) {
        value = val;
        left = leftNode;
        right = rightNode;
    }
    
    public int getValue() {
        return this.value;
    }
    
    public CompositeInterface getRight() {
        return this.right;
    }
    
    public CompositeInterface getLeft() {
        return this.left;
    }
}