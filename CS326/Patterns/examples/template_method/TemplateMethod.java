import java.util.*;

public class TemplateMethod {
    public static ArrayList<Integer> ints = new ArrayList<Integer>();
    
    public static void main(String[] args) {
        addInteger(5);
        addInteger(10);
        System.out.println(ints);
    }
    
    public static void addInteger(int intToAdd) {
        for (Integer i: ints)
            if (i == intToAdd)
                return;
        ints.add(intToAdd);
    }
}