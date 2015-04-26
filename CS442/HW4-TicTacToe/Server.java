public class Server {
	public static void main(String[] args) {
		try {
			System.setSecurityManager(new java.rmi.RMISecurityManager());
			RemoteInterface v = new RemoteObject();
			java.rmi.registry.LocateRegistry.createRegistry(8465);
			java.rmi.Naming.rebind("//:8465/count", v);
		} catch(java.rmi.UnknownHostException x) {
			x.printStackTrace();
		} catch(java.rmi.RemoteException x) {
			x.printStackTrace();
		} catch(java.net.MalformedURLException x){
			x.printStackTrace();
		} catch(Exception x) {
			x.printStackTrace();
		}
	}
}