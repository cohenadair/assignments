import java.util.*;

public class RemoteObject extends java.rmi.server.UnicastRemoteObject implements RemoteInterface {
	// Note: Every operation of a Hashtable is synchronized.
	private Hashtable<String, String> table = null;
	
	public RemoteObject() throws java.rmi.RemoteException {
		this.table = new Hashtable<String, String>();
	}
	
	// Stores the key and value in this.table.
	// Does nothing if key or value equals an empty string.
	// If key doesn't exists, a new key/value pair is added.
	// If key does exist, its value is reset to value.
	public void store(String key, String value) throws java.rmi.RemoteException {
		if (key.equals("") || value.equals(""))
			return;
		this.table.put(key, value);
	}
	
	// Returns the value for key.
	// Returns the null string if key doesn't exist in this.table.
	public String read(String key) throws java.rmi.RemoteException {
		Object result = this.table.get(key);
		if (result == null)
			return "";
		return result.toString();
	}
	
	// Removes the key/value pair from this.table.
	public void delete(String key) throws java.rmi.RemoteException {
		this.table.remove(key);
	}
	
	// Returns true if the key is a key in this.table, false if not.
	public boolean exists(String key) throws java.rmi.RemoteException {
		return this.table.containsKey(key);
	}
	
	// Returns an Enumeration of all this.table's keys.
	// Returns null if this.table is null.
	public Enumeration getKeys() throws java.rmi.RemoteException {
		if (this.table != null)
			return this.table.keys();
		return null;
	}
}