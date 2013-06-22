package smart.smartfridge.activities;

import smart.smartfridge.R;
import smart.smartfridge.connections.ConnectionService;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MenuActivity extends Activity {

	Button history;
	Button logout;
	Button state;
	Context context;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
        context = getApplicationContext();
        history = (Button) findViewById(R.id.history_button);
        state = (Button) findViewById(R.id.state_button);
        logout = (Button) findViewById(R.id.logout_button);
 
    	
        history.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
        		Intent intent = new Intent(context, HistoryActivity.class);
        		startActivity(intent);
         	}
        });	
        state.setOnClickListener(new OnClickListener() {
           	public void onClick(View v) {
           		Intent intent = new Intent(context, StateActivity.class);
          		startActivity(intent);
         	}
        });	
        logout.setOnClickListener(new OnClickListener() {
           	public void onClick(View v) {
          		ConnectionService.TOKEN=null;
              	Log.w("LOGIN", "TOKEN="+ConnectionService.TOKEN);
                Toast.makeText(context, "Wylogowano", Toast.LENGTH_LONG).show();
           		Intent intent = new Intent(context, MainActivity.class);
          		startActivity(intent);
         	}
        });	
    
    
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
   	@Override
   	public void onBackPressed() {
   		return;
   	}    
    
}
