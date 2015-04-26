public class StorageManager {
    private static StorageManager sharedManager = null;
    public Integer numberOfFiles = new Integer(0);
    
    protected StorageManager() {
        
    }
    
    // only create a new instance if it hasn't already been initialized
    public static StorageManager getSharedManager() {
        if (sharedManager == null)
            sharedManager = new StorageManager();
        return sharedManager;
    }
}