package com.example.smartbuilding.main;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;
import android.widget.TextView;

import com.example.smartbuilding.R;
import com.example.smartbuilding.model.Sector;
import com.example.smartbuilding.utils.AllViewAdapter;
import com.example.smartbuilding.utils.CustomComparator;
import com.example.smartbuilding.utils.HttpGetAsyncTask;
import com.example.smartbuilding.utils.SmartBuildingConstants;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutionException;

/**
 * Created by Wojciech Krzaczek
 */

public class AllViewActivity extends Activity {
    public static final String ALL_SECTORS = "All sectors";
    private static final String URL = SmartBuildingConstants.IP
            + "/ws/rest/first/sector/all";
    TextView textView;

    @SuppressLint("NewApi")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fragment_groupview);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            getActionBar().setDisplayHomeAsUpEnabled(true);
        }

        textView = (TextView) findViewById(R.id.deviceType);
        textView.setText(ALL_SECTORS);

        final ListView list = (ListView) findViewById(R.id.GroupList);

        HttpGetAsyncTask httpGetAsyncTask = new HttpGetAsyncTask();
        String response = "";

        try {
            response = httpGetAsyncTask.execute(URL).get();
        } catch (InterruptedException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        } catch (ExecutionException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        }

        Gson gson = new Gson();
        List<Sector> sectorList = gson.fromJson(response, new TypeToken<List<Sector>>() {
        }.getType());
        Collections.sort(sectorList, new CustomComparator());
        Sector[] sectors = sectorList.toArray(new Sector[sectorList.size()]);

        list.setAdapter(new AllViewAdapter(this, sectors));

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
