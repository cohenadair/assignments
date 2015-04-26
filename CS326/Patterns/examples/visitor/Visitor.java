public class Visitor {
    public Visitor() {
        
    }
    
    public static void visitApple(Apple a) {
        System.out.println("Apple color: " + a.getColor());
    }
    
    public static void visitOrange(Orange o) {
        System.out.println("Orange name: " + o.getName());
    }
}