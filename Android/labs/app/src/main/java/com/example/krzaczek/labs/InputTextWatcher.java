package com.example.krzaczek.labs;

import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

/**
 * Created by krzaczek on 06.03.15.
 */
public class InputTextWatcher implements TextWatcher {

    private TextView output;
    private Context applicationContext;

    public InputTextWatcher(TextView output, Context applicationContext) {
        this.output = output;
        this.applicationContext = applicationContext;
    }

    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after) {
        Toast.makeText(applicationContext, "before", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count) {
        Toast.makeText(applicationContext, "in", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void afterTextChanged(Editable s) {
        Toast.makeText(applicationContext, "end", Toast.LENGTH_SHORT).show();
        output.setText(s);
        Log.v("test", "after");
    }
}
