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
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.example.smartbuilding.R;

import java.util.ArrayList;
import java.util.Collections;


public class GroupViewActivity extends Activity {

    public static final String KEY = "sector_ID";

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

        String cars[] = {deviceType, "Kuchnia", "Łazienka - Parter", "Łazienka - Piętro", "Salon", "Pokój 1", "Pokój 2", "Sypialnia"};
        //TODO HTTP GET parametrized by deviceType
        ArrayList<String> carL = new ArrayList<String>();
        Collections.addAll(carL, cars);

        final ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.row_groupview, carL);
        list.setAdapter(adapter);

        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, final View view,
                                    int position, long id) {
                final String item = (String) parent.getItemAtPosition(position);    //TODO get item ID
                Intent intent = new Intent(GroupViewActivity.this, OperationSettings.class) ;
                intent.putExtra(KEY, item);
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