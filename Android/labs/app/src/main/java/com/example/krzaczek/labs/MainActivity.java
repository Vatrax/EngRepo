package com.example.krzaczek.labs;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.text.DecimalFormat;

import static android.view.View.OnClickListener;


public class MainActivity extends Activity {

    private final double EURO2USD = 1.35;
    private final char EUROSYM = '\u20AC';
    private final double COLON2USD = 0.0019;
    private final char COLONSYM = '\u20A1';
    DecimalFormat usaDf = new DecimalFormat("###,###,###,###.##");

    EditText txtUSDollars;
    EditText txtEuros;
    EditText txtColones;
    Button btnClear;
    Button btnConvert;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"created", Toast.LENGTH_SHORT).show();

        txtUSDollars = (EditText)findViewById(R.id.txtUSDollars);
        txtEuros = (EditText)findViewById(R.id.txtEuros);
        txtEuros.setInputType(EditorInfo.TYPE_NULL);
        txtColones = (EditText)findViewById(R.id.txtColones);

        btnClear = (Button)findViewById(R.id.btnClear);
        Toast.makeText(getApplicationContext(), "registred", Toast.LENGTH_SHORT).show();
        btnClear.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "clicked", Toast.LENGTH_SHORT).show();
                txtColones.setText("");
                txtEuros.setText("");
                txtUSDollars.setText("");
            }

        });

        btnConvert = (Button) findViewById(R.id.btnConvert);
        btnConvert.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String usdStr = txtUSDollars.getText().toString();
                    double usd = Double.parseDouble(usdStr);
                    String euros = EUROSYM +
                            String.valueOf(usaDf.format(usd / EURO2USD));
                    String colones = COLONSYM +
                            String.valueOf(usaDf.format(usd / COLON2USD));
                    txtEuros.setText(euros);
                    txtColones.setText(colones);
                } catch (NumberFormatException e) {
                    Log.e("number", "cannot cout currency");
                }
            }
        });
    }

        @Override
    protected void onStart() {
        super.onStart();
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"started", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"restarted", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onResume() {
        super.onResume();
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"resumed", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onPause() {
        super.onPause();
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"paused", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onStop() {
        super.onStop();
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"stop", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"destroyed", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toast.makeText(getApplicationContext(),"saveInstanceState", Toast.LENGTH_SHORT).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
