public class NullApple extends Apple {
    public NullApple(String kind) {
        super(kind);
    }
    
    public String getKind() {
        System.out.println("Accessing instance of NullApple.");
        return "NULL";
    }
}