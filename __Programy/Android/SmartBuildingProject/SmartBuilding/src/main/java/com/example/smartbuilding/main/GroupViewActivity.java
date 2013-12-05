package com.example.smartbuilding.main;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;

import com.example.smartbuilding.R;
import com.example.smartbuilding.model.Sector;
import com.example.smartbuilding.utils.GroupViewAdapter;
import com.example.smartbuilding.utils.HttpGetAsyncTask;
import com.example.smartbuilding.utils.SmartBuildingConstants;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.util.List;
import java.util.concurrent.ExecutionException;

/**
 * Created by Wojciech Krzaczek
 */

public class GroupViewActivity extends Activity {

    public static final String KEY = "sector_ID";
    private static final String URL = SmartBuildingConstants.IP
            + "/ws/rest/first/sector/byDT/";

    TextView textView;

    @SuppressLint("NewApi")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fragment_groupview);
        Intent intent = getIntent();
        String deviceType = intent.getStringExtra(MainActivity.DEVICE_TYPE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            getActionBar().setDisplayHomeAsUpEnabled(true);
        }

        final ListView list = (ListView) findViewById(R.id.GroupList);
        textView = (TextView) findViewById(R.id.deviceType);
        textView.setText(deviceType);

        HttpGetAsyncTask httpGetAsyncTask = new HttpGetAsyncTask();
        String response = "";

        try {
            response = httpGetAsyncTask.execute(URL + deviceType).get();
        } catch (InterruptedException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        } catch (ExecutionException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        }

        Gson gson = new Gson();
        List<Sector> sectorList = gson.fromJson(response, new TypeToken<List<Sector>>() {
        }.getType());

        Sector[] sectors = sectorList.toArray(new Sector[sectorList.size()]);
        list.setAdapter(new GroupViewAdapter(this, sectors));

        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {
                final Sector item = (Sector) parent.getItemAtPosition(position);
                Intent intent = new Intent(GroupViewActivity.this,
                        OperationSettings.class);
                intent.putExtra(KEY, item.getId());
                startActivity(intent);

            }

        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.group_view, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        switch (item.getItemId()) {
            case android.R.id.home:
                NavUtils.navigateUpFromSameTask(this);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }


}