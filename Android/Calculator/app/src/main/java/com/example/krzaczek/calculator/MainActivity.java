package com.example.krzaczek.calculator;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.example.krzaczek.calculator.startedy.AddStrategy;
import com.example.krzaczek.calculator.startedy.CalculationStrategy;
import com.example.krzaczek.calculator.startedy.DivideStrategy;
import com.example.krzaczek.calculator.startedy.MultiplicationStrategy;
import com.example.krzaczek.calculator.startedy.OverStrategy;
import com.example.krzaczek.calculator.startedy.PowerStrategy;
import com.example.krzaczek.calculator.startedy.SubstractionStrategy;

import java.util.HashMap;
import java.util.Map;


public class MainActivity extends ActionBarActivity {

    Map<Operation, CalculationStrategy> startegies = new HashMap<>();

    double result = 0;
    Operation operation;

    private Button plusButton;
    private Button minusButton;
    private Button multiplyButton;
    private Button divideButton;
    private Button overButton;
    private Button powerButton;
    private Button clearButton;
    private Button resultButton;
    private EditText inputText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initFields();
        addListeners();
        populateStrategies();
    }

    private void populateStrategies() {
        startegies.put(Operation.PLUS, new AddStrategy());
        startegies.put(Operation.MINUS, new SubstractionStrategy());
        startegies.put(Operation.MULTI, new MultiplicationStrategy());
        startegies.put(Operation.DIVIDE, new DivideStrategy());
        startegies.put(Operation.POWER, new PowerStrategy());
        startegies.put(Operation.OVER, new OverStrategy());
    }

    private void addListeners() {
        plusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    inputText.setText("");
                    operation = Operation.PLUS;
                }
            }
        });

        minusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    inputText.setText("");
                    operation = Operation.MINUS;
                }
            }
        });

        multiplyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    inputText.setText("");
                    operation = Operation.MULTI;
                }
            }
        });

        divideButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    inputText.setText("");
                    operation = Operation.DIVIDE;
                }
            }
        });

        plusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    inputText.setText("");
                    operation = Operation.PLUS;
                }
            }
        });

        powerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    inputText.setText("");
                    operation = Operation.POWER;
                }
            }
        });

        overButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = inputText.getText().toString();
                if (text != null && !text.isEmpty()) {
                    result = Double.parseDouble(text);
                    operation = null;
                    inputText.setText(Double.toString(startegies.get(Operation.OVER).execute(result, 0)));

                }
            }
        });

        clearButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                inputText.setText("");
                result = 0;
                operation = null;
            }
        });

        resultButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (operation == null) {
                    return;
                }
                String value = inputText.getText().toString();
                if (value == null || value.isEmpty()) {
                    value = "0";
                }
                try {
                    result = startegies.get(operation).execute(result, Double.parseDouble(value));
                    inputText.setText(Double.toString(result));
                } catch (ArithmeticException e) {
                    inputText.setText("#ERR");
                }
                result = 0;
                operation = null;
            }
        });

    }

    private void initFields() {
        plusButton = (Button) findViewById(R.id.plus);
        minusButton = (Button) findViewById(R.id.minus);
        multiplyButton = (Button) findViewById(R.id.multiply);
        divideButton = (Button) findViewById(R.id.devide);
        overButton = (Button) findViewById(R.id.over);
        powerButton = (Button) findViewById(R.id.power);
        clearButton = (Button) findViewById(R.id.clear);
        resultButton = (Button) findViewById(R.id.result);

        inputText = (EditText) findViewById(R.id.input);
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
