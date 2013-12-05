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
import android.widget.Toast;
import android.widget.ToggleButton;

import com.example.smartbuilding.R;

/**
 * Created by Wojciech Krzaczek
 */

public class OperationSettings extends Activity {

    ToggleButton toggleButton;
    SeekBar seekBar;
    TextView seekBarPercentage;
    TextView deviceType;
    TextView sector;

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
        seekBarPercentage = (TextView) findViewById(R.id.seekBarPercentage);
        deviceType = (TextView) findViewById(R.id.deviceType);
        sector = (TextView) findViewById(R.id.sectorName);

        // TODO set start values
        deviceType.setText("Device Name");
        sector.setText("Sector Name");

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                seekBarPercentage.setText(i + "%");
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        if (seekBar.getProgress() == 0) {
            setComponentVisibility(View.INVISIBLE);
        }
    }

    public void disableWidgets(View view) {
        if (toggleButton.isChecked()) {
            setComponentVisibility(View.VISIBLE);
            seekBar.setProgress(100);
        } else {
            setComponentVisibility(View.INVISIBLE);
        }

    }

    private void setComponentVisibility(int visibility) {
        seekBarPercentage.setVisibility(visibility);
        seekBar.setVisibility(visibility);
    }

    public void startOperation(View view) {
        // TODO HTTP POST
        Toast.makeText(this, "Operation started...", Toast.LENGTH_SHORT).show();
        this.finish();
    }

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
