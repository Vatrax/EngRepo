package com.example.smartbuilding.main;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.example.smartbuilding.R;
import com.example.smartbuilding.model.Sector;
import com.example.smartbuilding.utils.IPList;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class GroupViewActivity extends Activity {

    public static final String KEY = "sector_ID";

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
        httpGetAsyncTask.execute(deviceType);
        ArrayList<Sector> sectors = httpGetAsyncTask.getSectors();

        String[] strings = null;
        for(int i=0; i< sectors.size(); i++) {
            strings[i]= sectors.get(i).getGroupName();
        }
        list.setAdapter(new ArrayAdapter<String>(this, R.layout.row_groupview, strings));

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

        class HttpGetAsyncTask extends AsyncTask<String, Void, String> {

            private ArrayList<Sector> sectors =null;
            public static final String URL = IPList.PHONE+"/ws/rest/first/sector/byDT/";

            @Override
            protected String doInBackground(String... params) {
                HttpClient httpClient = new DefaultHttpClient();
                HttpGet httpGet = new HttpGet(URL+ params[0]);

                try {
                    System.out.println("execute HTTP");
                    HttpResponse httpResponse = httpClient.execute(httpGet);
                    System.out.println("httpResponse");
                    InputStream inputStream = httpResponse.getEntity().getContent();
                    BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
                    StringBuilder stringBuilder = new StringBuilder();
                    String bufferedStrChunk = null;
                    while((bufferedStrChunk = bufferedReader.readLine()) != null){
                        stringBuilder.append(bufferedStrChunk);
                    }
                    System.out.println("Returning value of doInBackground :" + stringBuilder.toString());

                    return stringBuilder.toString();

                } catch (ClientProtocolException cpe) {
                    System.out.println("Exception generates caz of httpResponse :" + cpe);
                    cpe.printStackTrace();
                } catch (IOException ioe) {
                    System.out.println("Second exception generates caz of httpResponse :" + ioe);
                    ioe.printStackTrace();
                }

                return null;
            }

            // Argument comes for this method according to the return type of the doInBackground() and
            //it is the third generic type of the AsyncTask
            @Override
            protected void onPostExecute(String result) {
                super.onPostExecute(result);
                Gson gson = new Gson();
                sectors = gson.fromJson(result,new TypeToken<List<Sector>>(){}.getType());
            }

            public ArrayList<Sector> getSectors() {
                return sectors;
            }
        }

   }