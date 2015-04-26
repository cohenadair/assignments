public class RemoteObject extends java.rmi.server.UnicastRemoteObject implements RemoteInterface {
	private final int MAX_CLIENTS = 10;
	private final String X = "X";
	private final String O = "O";
	
	private UpdateInterface callbacks[];
	private int numClients = 0;
	private String[] boardTokens = new String[9];
	
	private boolean isXAssigned = false;
	private boolean isOAssigned = false;
	
	public RemoteObject() throws java.rmi.RemoteException {
		callbacks = new UpdateInterface[MAX_CLIENTS];
		for (int i = 0; i < this.boardTokens.length; i++)
			this.boardTokens[i] = "";
	}
	
	// Returns all the board values.
	public String[] getBoardTokens() throws java.rmi.RemoteException {
		return this.boardTokens;
	}
	
	// Returns the value on the board at index i.
	public String getBoardToken(int i) throws java.rmi.RemoteException {
		return this.boardTokens[i];
	}
	
	// Sets the value on the board at index i to v.
	public void setBoardToken(int i, String t) throws java.rmi.RemoteException {
		this.boardTokens[i] = t;
		this.doCallbacks();
	}
	
	public void setCallback(UpdateInterface i) throws java.rmi.RemoteException {
		this.callbacks[numClients++] = i;
	}
	
	private void doCallbacks() {
		for (int i = 0; i < numClients; i++) {
			try {
				this.callbacks[i].getNewData();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}
	
	// Returns "X" if X's win.
	// Returns "O" if O's win.
	// Returns "" if there is no winner.
	public String getWinner() throws java.rmi.RemoteException {
		String[] V = this.boardTokens;
		
		if (V[0].equals(V[1]) && V[1].equals(V[2])) if (!V[0].equals("")) return V[0]; 	// row 1
		if (V[3].equals(V[4]) && V[4].equals(V[5])) if (!V[3].equals("")) return V[3];	// row 2
		if (V[6].equals(V[7]) && V[7].equals(V[8])) if (!V[6].equals("")) return V[6];	// row 3
		if (V[0].equals(V[3]) && V[3].equals(V[6])) if (!V[0].equals("")) return V[0];	// column 1
		if (V[1].equals(V[4]) && V[4].equals(V[7])) if (!V[1].equals("")) return V[1];	// column 2
		if (V[2].equals(V[5]) && V[5].equals(V[8])) if (!V[2].equals("")) return V[2];	// column 3
		if (V[0].equals(V[4]) && V[4].equals(V[8])) if (!V[0].equals("")) return V[0];	// top left to bottom right diagonal
		if (V[2].equals(V[4]) && V[4].equals(V[6])) if (!V[2].equals("")) return V[2];	// top right to bottom left diagonal
		
		return "";
	}
	
	// Returns true if the game is done; false if it isn't.
	// A game is done if there is a winner or a tie.
	public boolean isGameDone() throws java.rmi.RemoteException {
		if (!this.getWinner().equals(""))
			return true;
		
		// check for empty cells
		for (int i = 0; i < this.boardTokens.length; i++)
			if (this.boardTokens[i].equals(""))
				return false;
			
		return true;
	}
	
	// Returns an available token or the empty string if there isn't one available.
	public String getAvailableToken() throws java.rmi.RemoteException {
		if (!this.isXAssigned) {
			this.isXAssigned = true;
			return X;
		}
		
		if (!this.isOAssigned) {
			this.isOAssigned = true;
			return O;
		}
		
		return "";
	}
}