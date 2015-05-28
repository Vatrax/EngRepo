package com.example.krzaczek.smartbuilding;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import com.example.krzaczek.smartbuilding.exceptions.noButtonException;
import com.example.krzaczek.smartbuilding.model.DeviceType;


public class MainActivity extends Activity {

    public static final String DEVICE_TYPE = "Device_type";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    public void logout(View view) {
        this.finish();
    }

    public void showAll(View view) {
        Intent intent = new Intent(this, AllViewActivity.class);
        startActivity(intent);
    }

    public void loadGroupList(View view) {
        try {
            Intent intent = new Intent(this, GroupViewActivity.class);
            intent.putExtra(DEVICE_TYPE, getType(view).toString());
            startActivity(intent);
        } catch (noButtonException e) {
            e.printStackTrace();
        }
    }

    private DeviceType getType(View view) throws noButtonException {
        switch (view.getId()) {
            case R.id.shutters:
                return DeviceType.SHUTTERS;
            case R.id.light:
                return DeviceType.LIGHT;
            case R.id.acc:
                return DeviceType.ACC;
        }
        throw new noButtonException();
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
