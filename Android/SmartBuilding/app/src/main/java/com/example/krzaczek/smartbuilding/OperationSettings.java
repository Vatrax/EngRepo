package com.example.krzaczek.smartbuilding;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.example.krzaczek.smartbuilding.model.Sector;
import com.example.krzaczek.smartbuilding.utils.HttpGetAsyncTask;
import com.example.krzaczek.smartbuilding.utils.SmartBuildingConstants;
import com.google.gson.Gson;

import java.util.concurrent.ExecutionException;


public class OperationSettings extends Activity {

    private static final String URL_GET_DEVICE = SmartBuildingConstants.IP + "/byid/";
    private static final String URL_UPDATE_DEVICE = SmartBuildingConstants.IP + "/update/";
    private Sector sector;

    ToggleButton toggleButton;
    SeekBar seekBar;
    TextView seekBarPercentage;
    TextView deviceType;
    TextView sectorNameText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_operation_settings);

        Intent intent = getIntent();
        String id = intent.getStringExtra(GroupViewActivity.KEY);

        toggleButton = (ToggleButton) findViewById(R.id.toggleButton);
        seekBar = (SeekBar) findViewById(R.id.seekBar);
        seekBarPercentage = (TextView) findViewById(R.id.seekBarPercentage);
        deviceType = (TextView) findViewById(R.id.deviceType);
        sectorNameText = (TextView) findViewById(R.id.sectorName);

        HttpGetAsyncTask httpGetAsyncTask = new HttpGetAsyncTask();
        String response = "";

        try {
            response = httpGetAsyncTask.execute(URL_GET_DEVICE + id).get();
        } catch (InterruptedException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        } catch (ExecutionException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        }

        Gson gson = new Gson();
        sector = gson.fromJson(response, Sector.class);

        deviceType.setText(sector.getDeviceType().toString());
        sectorNameText.setText(sector.getName());
        if (sector.getValue() > 0) {
            toggleButton.setChecked(true);
            seekBar.setProgress(sector.getValue());
            seekBarPercentage.setText(sector.getValue() + "%");
        }

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                seekBarPercentage.setText(i + "%");
                sector.setValue(i);
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
            sector.setValue(100);
        } else {
            setComponentVisibility(View.INVISIBLE);
            sector.setValue(0);
        }

    }

    private void setComponentVisibility(int visibility) {
        seekBarPercentage.setVisibility(visibility);
        seekBar.setVisibility(visibility);
    }

    public void startOperation(View view) {
        String response = null;
        HttpGetAsyncTask httpGetAsyncTask = new HttpGetAsyncTask();
        try {
            response = httpGetAsyncTask.execute(URL_UPDATE_DEVICE + sector.getId() +"/" + sector.getValue()).get();
        } catch (InterruptedException | ExecutionException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        }
        if (response != null) {
            Toast.makeText(this, "Operation started...", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Connection Error", Toast.LENGTH_SHORT).show();
        }
        this.finish();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_operation_settings, menu);
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
