import java.util.*;

public interface RemoteInterface extends java.rmi.Remote {
	public void store(String key, String value) throws java.rmi.RemoteException;
	public String read(String key) throws java.rmi.RemoteException;
	public void delete(String key) throws java.rmi.RemoteException;
	public boolean exists(String key) throws java.rmi.RemoteException;
	public Enumeration getKeys() throws java.rmi.RemoteException;
}