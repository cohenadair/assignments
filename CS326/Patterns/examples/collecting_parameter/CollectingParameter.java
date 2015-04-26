import java.util.*;

public class CollectingParameter {
    private static Integer total = new Integer(1);
    
    public static void main(String[] args) {
        ArrayList<Boolean> results = new ArrayList<>();
        
        int c = 0;
        while (c < 8) {
            doubleTotal(results);
            c++;
        }
        
        for (Boolean b: results)
            System.out.print(b + " ");
    }
    
    public static void doubleTotal(ArrayList<Boolean> results) {
        total += total;
        if (total > 100)
            results.add(true);
        else
            results.add(false);
    }
}