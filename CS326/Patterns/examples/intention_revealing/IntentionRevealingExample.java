public class IntentionRevealingExample {
    public static void main(String[] args) {
        System.out.println(addIntegers(5, 3));
    }
    
    // good
    public static int addIntegers(int a, int b) {
        return a + b;
    }
    
    // bad
    public static int a(int a, int b) {
        return a + b;
    }
}