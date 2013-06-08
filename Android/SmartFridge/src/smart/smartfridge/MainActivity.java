package smart.smartfridge;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class AndroidLogin extends Activity implements OnClickListener {
	  

	EditText username;
	EditText password;
	Button login;
	Context context;
	TextView result;
	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        context = getApplicationContext();


    	login = (Button) findViewById(R.id.log_button);
        login.setOnClickListener(this);
        result = (TextView)findViewById(R.id.result);

        
    }

             
    public void postLoginData() {
    // Create a new HttpClient and Post Header
    HttpClient httpclient = new DefaultHttpClient();
    HttpPost httppost = new HttpPost("http://www.fridge.pawelszczerbicki.pl/login");
         
    try {
    // Add user name and password
    username = (EditText) findViewById(R.id.username);
    String name = username.getText().toString();
        
    password = (EditText) findViewById(R.id.password);
    String pass = password.getText().toString();
                  
    List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
	nameValuePairs.add(new BasicNameValuePair("username", name));
	nameValuePairs.add(new BasicNameValuePair("password", pass));
	httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
         
    // Execute HTTP Post Request
    Log.w("SENCIDE", "Execute HTTP Post Request");
    HttpResponse response = httpclient.execute(httppost);
                    
    String str = inputStreamToString(response.getEntity().getContent()).toString();
    Log.w("SENCIDE", str);
    
    if(str.toString().equalsIgnoreCase("true"))
    {
    	Log.w("SENCIDE", "TRUE");
    	result.setText("Login successful"); 
    }
    else
    {
    	Log.w("SENCIDE", "FALSE");
    	result.setText(str);
    }
    }
    catch (ClientProtocolException e) {
    	e.printStackTrace(); }
    catch (IOException e) {
    	e.printStackTrace(); }
    } 
         
    private StringBuilder inputStreamToString(InputStream is) {
    	String line = "";
    	StringBuilder total = new StringBuilder();
        // Wrap a BufferedReader around the InputStream
        BufferedReader rd = new BufferedReader(new InputStreamReader(is));
        // Read response until the end
        try {
        	while ((line = rd.readLine()) != null) { 
        		total.append(line); 
            }
        } 
        catch (IOException e) {
        	e.printStackTrace(); }
        // Return full string
        return total;
        }
    @Override
    public void onClick(View view) {
    	if(view == login){
    		postLoginData();
    	}
    }
}

    

        
        /*new OnClickListener() {
        	public void onClick(View v) {
                Toast.makeText(context, "Logowanie", Toast.LENGTH_LONG).show();
        		Intent intent = new Intent(context, MenuActivity.class);
        		startActivity(intent);
        	}*/



   /* @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
*/