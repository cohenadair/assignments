import java.util.*;

public class NullObject {
    private static ArrayList<Apple> apples = new ArrayList();
    
    public static void main(String[] args) {
        System.out.println(addApple("Gala").getKind());
        System.out.println(addApple("Granny Smith").getKind());
        System.out.println(addApple("Gala").getKind());
    }
    
    // returns the newly added apple
    // return the null object if the apple wasn't added
    private static Apple addApple(String kind) {
        Apple result = null;
        if (!appleExists(kind)) {
            result = new Apple(kind);
            apples.add(new Apple(kind));
            return result;
        } else
            result = new NullApple(kind);
        return result;
    }
    
    // check to see if an apple of "kind" already exists in the list
    private static boolean appleExists(String kind) {
        for (int i = 0; i < apples.size(); i++)
            if (apples.get(i).getKind().equals(kind))
                return true;
        return false;
    }
}