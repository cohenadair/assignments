import java.util.*;

public class VisitorExample {
    public static void main(String[] args) {
        Visitor v = new Visitor();
        ArrayList<Visitable> fruit = new ArrayList<Visitable>();

        fruit.add(new Orange());
        fruit.add(new Apple());
        
        for (Visitable f: fruit)
            f.accept(v);
    }
}