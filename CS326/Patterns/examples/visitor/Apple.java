public class Apple implements Visitable {
    private String color;
    
    public Apple() {
        color = "Green";
    }
    
    public String getColor() {
        return this.color;
    }
    
    public void accept(Visitor aVisitor) {
        aVisitor.visitApple(this);
    }
}