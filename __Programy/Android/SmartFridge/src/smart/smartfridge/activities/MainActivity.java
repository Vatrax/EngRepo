package smart.smartfridge.activities;

import smart.smartfridge.R;
import smart.smartfridge.connections.HttpFridgeService;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener{
	  

	EditText username;
	EditText password;
	Button login;
	Context context;
	HttpFridgeService httpFridgeService;
	@Override
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.activity_main);
        context = getApplicationContext();
        
        login = (Button)findViewById(R.id.log_button);
        login.setOnClickListener(this);
        httpFridgeService = new HttpFridgeService();
        username = (EditText)findViewById(R.id.username);
        password = (EditText)findViewById(R.id.password);
        
    }
  
    @Override
    public void onClick(View view) {
      if(view == login) {
    	  String user = username.getText().toString();
          String pass = password.getText().toString();
          
          if(httpFridgeService.login(user,pass))
          {
          	Log.w("Fridge", "TRUE");
              Toast.makeText(context, "Zalogowano", Toast.LENGTH_LONG).show();
      		Intent intent = new Intent(context, MenuActivity.class);
      		startActivity(intent);
          }
          else
          {
          	Log.w("Fridge", "FALSE");
              Toast.makeText(context, "B³¹d logowania", Toast.LENGTH_LONG).show();
          }
                    
      }
      
    }
    
   	@Override
   	public void onBackPressed() {
   	Intent intent = new Intent(getApplicationContext(),MainActivity.class);
   	intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);              
   	startActivity(intent);
    this.moveTaskToBack(true);
   	}    
    
}