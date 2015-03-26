package com.example.krzaczek.myapplication1;

import android.support.v7.app.ActionBarActivity;
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


public class MainActivity extends ActionBarActivity {

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

        txtUSDollars = (EditText)findViewById(R.id.txtUSDollars);
        txtEuros = (EditText)findViewById(R.id.txtEuros);
        txtEuros.setInputType(EditorInfo.TYPE_NULL);
        txtColones = (EditText)findViewById(R.id.txtColones);

        btnClear = (Button)findViewById(R.id.btnClear);
        Toast.makeText(getApplicationContext(), "registred", Toast.LENGTH_SHORT).show();
        btnClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "clicked", Toast.LENGTH_SHORT).show();
                txtColones.setText("");
                txtEuros.setText("");
                txtUSDollars.setText("");
            }

        });

        btnConvert = (Button) findViewById(R.id.btnConvert);
        btnConvert.setOnClickListener(new View.OnClickListener() {
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
