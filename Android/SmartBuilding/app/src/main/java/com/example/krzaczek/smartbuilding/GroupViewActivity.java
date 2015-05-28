package com.example.krzaczek.smartbuilding;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;

import com.example.krzaczek.smartbuilding.model.Sector;
import com.example.krzaczek.smartbuilding.utils.GroupViewAdapter;
import com.example.krzaczek.smartbuilding.utils.HttpGetAsyncTask;
import com.example.krzaczek.smartbuilding.utils.SmartBuildingConstants;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.util.List;
import java.util.concurrent.ExecutionException;


public class GroupViewActivity extends Activity {

    public static final String KEY = "sector_ID";
    private static final String URL = SmartBuildingConstants.IP + "/byDT/";

    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group_view);

        Intent intent = getIntent();
        String deviceType = intent.getStringExtra(MainActivity.DEVICE_TYPE);

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
        getMenuInflater().inflate(R.menu.menu_group_view, menu);
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
