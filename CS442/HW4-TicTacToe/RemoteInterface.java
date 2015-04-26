public interface RemoteInterface extends java.rmi.Remote {
	public String[] getBoardTokens() throws java.rmi.RemoteException;
	public String getBoardToken(int i) throws java.rmi.RemoteException;
	public void setBoardToken(int i, String t) throws java.rmi.RemoteException;
	public void setCallback(UpdateInterface i) throws java.rmi.RemoteException;
	public String getWinner() throws java.rmi.RemoteException;
	public boolean isGameDone() throws java.rmi.RemoteException;
	public String getAvailableToken() throws java.rmi.RemoteException;
}