public class Singleton {
    public static void main(String[] args) {
        StorageManager m = StorageManager.getSharedManager();
        m.numberOfFiles += 5;
        
        StorageManager m2 = StorageManager.getSharedManager();
        
        // even though they are different variables, they are pointed to the
        // same instance of StorageManager
        System.out.println(m.numberOfFiles);
        System.out.println(m2.numberOfFiles);
    }
}