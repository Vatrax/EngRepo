package com.example.smartbuilding.main;

import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.example.smartbuilding.R;

public class OperationSettings extends Activity {

    public static final int VISIBLE = 0;
    public static final int INVISIBLE = 100;

    ToggleButton toggleButton;
    SeekBar seekBar;
    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.opteration_settings);
        Intent intent = getIntent();
        String id = intent.getStringExtra(GroupViewActivity.KEY);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            getActionBar().setDisplayHomeAsUpEnabled(true);
        }

        toggleButton = (ToggleButton) findViewById(R.id.toggleButton);
        seekBar = (SeekBar) findViewById(R.id.seekBar);
        textView = (TextView) findViewById(R.id.seekBarPercentage);
        //TODO set start values

        seekBar.setOnSeekBarChangeListener( new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                textView.setText(i + "%");
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        if(seekBar.getProgress()==0) {
            setComponentVisibility(INVISIBLE);
        }
    }

        public void disableWidgets(View view){
            if(toggleButton.isChecked()){
                setComponentVisibility(VISIBLE);
                seekBar.setProgress(100);
            }
            else {
                setComponentVisibility(INVISIBLE);
            }

        }

    private void setComponentVisibility(int visibility) {
        textView.setVisibility(visibility);
        seekBar.setVisibility(visibility);
    }

    public void startOperation(View view) {}


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.operation_settings, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        switch (item.getItemId()) {
            case R.id.home:
                NavUtils.navigateUpFromSameTask(this);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }


}
