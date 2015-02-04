package smart.smartfridge.connections;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import android.util.Log;

public class ConnectionService {

	private static String MSG_ERROR = "error";	
	public static String TOKEN;	
	
	   public static String post (List<NameValuePair> nameValuePairs, String URL, boolean token) {
	        // Create a new HttpClient and Post Header
		   if(nameValuePairs==null)
			   nameValuePairs= new ArrayList<NameValuePair>();
		   if(token)
			   nameValuePairs.add(new BasicNameValuePair("sessionId", TOKEN));
		   
	        HttpClient httpclient = new DefaultHttpClient();
	         
	        HttpPost httppost = new HttpPost(URL);
	 
	        try {
           
	            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
	 
	            // Execute HTTP Post Request
	            Log.w("CONNECTION", "Execute HTTP Post Request");
	            HttpResponse response = httpclient.execute(httppost);
	            System.out.print(response);
	            String str = inputStreamToString(response.getEntity().getContent());
	            Log.w("CONNECTION", str);
	            if(!token)
	            {
	            	TOKEN = str;
	            }
	            
	            return str;
	 
	        } catch (Exception e){
	        	return MSG_ERROR;
	        }
	    } 

	   private static String inputStreamToString(InputStream is) {
		     String line = "";
		     StringBuilder total = new StringBuilder();
		     // Wrap a BufferedReader around the InputStream
		     BufferedReader rd = new BufferedReader(new InputStreamReader(is));
		     // Read response until the end
		     try {
		      while ((line = rd.readLine()) != null) { 
		        total.append(line); 
		      }
		     } catch (IOException e) {
		      e.printStackTrace();
		     }
		     // Return full string
		     return total.toString();
		    }


}