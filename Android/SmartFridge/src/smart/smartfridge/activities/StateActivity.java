package smart.smartfridge.activities;

import java.util.ArrayList;

import org.json.JSONArray;
import org.json.JSONObject;

import smart.smartfridge.R;
import smart.smartfridge.connections.ConnectionService;
import smart.smartfridge.custom_lists.RB_State_Adapter;
import smart.smartfridge.custom_lists.RowBean;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListView;
import android.widget.Toast;

public class StateActivity extends Activity {
 
	private ListView listView1;
	private String response;
	private String MSG_ERROR = "error";
	Context context;

    // url to make request
    private static String URL = "http://pawelszczerbicki.pl/smart-fridge/ws/products";
     
    // JSON Node names
    private static final String TAG_NAME = "visibleName";
    private static final String TAG_WEIGHT = "weight";
    private static final String TAG_MAXWEIGHT = "maxWeight";

    // contacts JSONArray
    JSONArray products = null;
 
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
  	    setContentView(R.layout.activity_state);
        context = getApplicationContext();

        response = ConnectionService.post(null, URL, true);

        if(response.equals(MSG_ERROR))
        {
        	Log.w("Connection", "Wrong tokken");
            Toast.makeText(context, "Sesja wygas³a", Toast.LENGTH_LONG).show();
  			Intent intent = new Intent(context, MainActivity.class);
  			startActivity(intent);
        }
        // Hashmap for ListView
        ArrayList<RowBean> productList = new ArrayList<RowBean>();
 
        try {
            // Getting Array of Products
            JSONArray products = new JSONArray(response);
 
            // looping through All Products
            for(int i = 0; i < products.length(); i++)
            {
            	JSONObject c = products.getJSONObject(i);
 
                // Storing each json item in variable
                String name = c.getString(TAG_NAME);
                String weight = c.getString(TAG_WEIGHT);
                String maxweight = c.getString(TAG_MAXWEIGHT);
                
            	RowBean product = new RowBean();

            	product.name=name;
            	product.weight=weight;
            	product.maxweight=maxweight;

            	productList.add(product);

            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        /**
         * Updating parsed JSON data into ListView
         * */
        RowBean RowBean_data[] = new RowBean[productList.size()];
        for(int i=0; i<productList.size(); i++)
        {
        	RowBean_data[i]=new RowBean(productList.get(i).name, productList.get(i).weight+"/"+productList.get(i).maxweight, null , null);
        }
        
        RB_State_Adapter adapter = new RB_State_Adapter(this,
                R.layout.custom_state, RowBean_data);
 
        listView1 = (ListView)findViewById(R.id.State_List);
 
        listView1.setAdapter(adapter);
    }
 
}