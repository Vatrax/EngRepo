package com.example.krzaczek.contactlistener;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.text.Editable;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

/**
 * Created by krzaczek on 20.03.15.
 */
public class SecoundaryActivity extends ActionBarActivity {

    private EditText input1;
    private EditText input2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_secound);


        input1 = (EditText) findViewById(R.id.input1);
        input2 = (EditText) findViewById(R.id.input2);
        Button button = (Button) findViewById(R.id.result);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                Editable input1text = input1.getText();
                Editable input2Text = input2.getText();
                if (input1text != null && input2Text != null) {
                    double value = Double.parseDouble(input1text.toString()) + Double.parseDouble(input2Text.toString());
                    intent.putExtra("result", value+"");
                }
                setResult(Activity.RESULT_OK, intent);
                finish();
            }
        });
    }
}

