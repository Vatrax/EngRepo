package com.example.smartbuilding.main;

import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.example.smartbuilding.R;
import com.example.smartbuilding.model.Sector;
import com.example.smartbuilding.utils.HttpGetAsyncTask;
import com.example.smartbuilding.utils.HttpPostAsyncTask;
import com.example.smartbuilding.utils.SmartBuildingConstants;
import com.google.gson.Gson;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

/**
 * Created by Wojciech Krzaczek
 */

public class OperationSettings extends Activity {

    private static final String URL_GET = SmartBuildingConstants.IP
            + "/ws/rest/first/sector/byid/";
    private static final String URL_POST = SmartBuildingConstants.IP
            + "/ws/rest/first/sector/update";
    private Sector sector;

    ToggleButton toggleButton;
    SeekBar seekBar;
    TextView seekBarPercentage;
    TextView deviceType;
    TextView sectorNameText;

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
        sectorNameText = (TextView) findViewById(R.id.sectorName);

        HttpGetAsyncTask httpGetAsyncTask = new HttpGetAsyncTask();
        String response = "";

        try {
            response = httpGetAsyncTask.execute(URL_GET + id).get();
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
        HttpPostAsyncTask httpPostAsyncTask = new HttpPostAsyncTask();
        String response = null;
        try {
            response = httpPostAsyncTask.execute(URL_POST, sector.getId(), Integer.toString(sector.getValue())).get();
        } catch (InterruptedException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        } catch (ExecutionException e) {
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
