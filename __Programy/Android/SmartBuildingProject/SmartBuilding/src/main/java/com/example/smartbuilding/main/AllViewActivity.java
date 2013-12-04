package com.example.smartbuilding.main;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;
import android.widget.TextView;

import com.example.smartbuilding.R;
import com.example.smartbuilding.model.DeviceType;
import com.example.smartbuilding.model.Sector;
import com.example.smartbuilding.utils.AllViewAdapter;
import com.example.smartbuilding.utils.IPList;

/**
 * Created by Vatrax on 17.11.13.
 */
public class AllViewActivity extends Activity{
    public static final String ALL_SECTORS = "All sectors";
    private static final String URL = IPList.PHONE + "/ws/rest/first/sector/all";
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
        //connectWithHttpGet(URL);
        //TODO HTTP GET parametrized by deviceType
        Sector[] sectors = new Sector[3];
        sectors[0]=(new Sector("sample_id", "Room", DeviceType.ACC, 0));
        sectors[1]=(new Sector("sample_id1", "Bathroom", DeviceType.LIGHT, 50));
        sectors[2]=(new Sector("sample_id2", "Kitchen", DeviceType.SHUTTERS, 100));

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
