public class Composite {
    public static void main(String[] args) {
        Leaf left = new Leaf(5, null, null);
        Leaf right = new Leaf(15, null, null);
        Node root = new Node(10, left, right);
        
        System.out.println(root.getLeft().getValue());
        System.out.println(root.getLeft().getValue());
        System.out.println(root.getValue());
    }
}