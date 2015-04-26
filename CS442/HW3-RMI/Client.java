import java.util.*;

public class Client {
	private static final String HELP_STRING = "Type HELP for valid commands.";
	
	private static final String HELP = "HELP";
	private static final String STORE = "STORE";
	private static final String READ = "READ";
	private static final String DELETE = "DELETE";
	private static final String EXISTS = "EXISTS";
	private static final String EXIT = "EXIT";
	
	private static Scanner in = new Scanner(System.in);
	private static RemoteInterface remote = null;
	
	public static void main(String[] args) {
		try {
			remote = (RemoteInterface)java.rmi.Naming.lookup("rmi://euclid.nmu.edu:4837/count");
			if (remote == null) {
				System.out.println("Failed to connect.");
				return;
			}
			
			System.out.println(HELP_STRING);
			
			String command, key, value;
			String[] parameters = null;
			
			while (true) {
				command = "";
				key = "";
				value = "";
				
				System.out.format("Enter a command: ");
				parameters = in.nextLine().split(" ");
				
				switch (parameters.length) {
					case 1:
						command = parameters[0];
						break;
					case 2:
						command = parameters[0];
						key = parameters[1];
						break;
					case 3:
						command = parameters[0];
						key = parameters[1];
						value = parameters[2];
						break;
					default:
						System.out.println("Invalid command parameters. " + HELP_STRING);
				}
				
				switch (command) {
					case HELP:
						System.out.format("%s\n%s <key> <value>\n%s <key>\n%s <key>\n%s <key>\n%s\n", HELP, STORE, READ, DELETE, EXISTS, EXIT);
						break;
					case STORE:
						store(key, value);
						break;						
					case READ:
						read(key);
						break;						
					case DELETE:
						delete(key);
						break;						
					case EXISTS:
						exists(key);
						break;											
					case EXIT:
						return;						
					default:
						System.out.println("Invalid command. " + HELP_STRING);
				}
			}
		} catch (Exception x) {
			x.printStackTrace();
		}
	}
	
	private static void store(String key, String value) {
		try { 
			remote.store(key, value);
		} catch (Exception x) {
		
		}
	}
	
	private static void read(String key) {
		try {
			String value = remote.read(key);
			if (value.equals(""))
				System.out.format("%s does not exist.\n", key);
			else
				System.out.format("Value for %s is %s.\n", key, remote.read(key));
		} catch (Exception x) {
		
		}
	}
	
	private static void delete(String key) {
		try {
			remote.delete(key);
		} catch (Exception x) {
		
		}
	}
	
	private static void exists(String key) {
		try {
			System.out.format("%s %s.\n", key, remote.exists(key) ? "exists" : "does not exist");
		} catch (Exception x) {
		
		}
	}
}