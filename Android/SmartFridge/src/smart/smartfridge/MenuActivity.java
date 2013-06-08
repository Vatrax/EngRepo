package smart.smartfridge;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MenuActivity extends Activity {

	Button history;
	Button logout;
	Button stan;
	Context context;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.menu);
        context = getApplicationContext();
        
        history = (Button) findViewById(R.id.history_button);
 
    	
        history.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
        		Intent intent = new Intent(context, HistoryActivity.class);
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
    
}
