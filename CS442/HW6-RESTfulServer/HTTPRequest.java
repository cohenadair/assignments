import java.net.*;
import java.io.*;

public class HTTPRequest {
    public static final String GET = "GET";
    public static final String PUT = "PUT";
    
    private String homeURL = "";
    
    public HTTPRequest() {
        
    }
    
    public HTTPRequest(String url) {
        this.homeURL = url;
    }
    
    public String getHomeURL() {
        return this.homeURL;
    }
    
    public void setHomeURL(String url) {
        this.homeURL = url;
    }
    
    private String fullURL(String suffixPath) {
        return this.homeURL + suffixPath;    
    }
    
    public boolean put(String url, String args) {
        return (this.doRequest(HTTPRequest.PUT, url, args) != "");
    }
    
    public String get(String url) {
        return this.doRequest(HTTPRequest.GET, url);
    }
    
    private String doRequest(String type, String url, String args) {
        String result = "";
        
        try {
            URL myURL = new URL(this.fullURL(url));
            URLConnection conn = myURL.openConnection();
            
            // PUT
            if (type.equals(HTTPRequest.PUT)) {
                conn.setDoOutput(true);
                OutputStreamWriter out = new OutputStreamWriter(conn.getOutputStream());
                out.write(args);
                out.close();
            }
            
            BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            
            String line;
            while ((line = in.readLine()) != null)
                result += line;
                
            in.close();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return result;
    }
    
    private String doRequest(String type, String url) {
        return this.doRequest(type, url, null);
    }
}