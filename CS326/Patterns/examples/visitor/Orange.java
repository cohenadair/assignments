public class Orange implements Visitable {
    private String name;
    
    public Orange() {
        name = "Orange";
    }
    
    public String getName() {
        return this.name;
    }
    
    public void accept(Visitor aVisitor) {
        aVisitor.visitOrange(this);
    }
}