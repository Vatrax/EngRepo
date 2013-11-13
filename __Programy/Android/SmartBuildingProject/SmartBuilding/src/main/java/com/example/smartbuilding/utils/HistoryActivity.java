package com.example.smartbuilding.utils;

import java.util.ArrayList;

import org.json.JSONArray;
import org.json.JSONObject;

import smart.smartfridge.R;
import smart.smartfridge.connections.ConnectionService;
import smart.smartfridge.custom_lists.RB_History_Adapter;
import smart.smartfridge.custom_lists.RowBean;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListView;
import android.widget.Toast;

public class HistoryActivity extends Activity {
 
	private ListView listView1;
	private String response;
	private String MSG_ERROR = "error";
	Context context;
	
    // url to make request
    private static String URL = "http://pawelszczerbicki.pl/smart-fridge/ws/productsHistory";
     
    // JSON Node names
    private static final String TAG_NAME = "visibleName";
    private static final String TAG_MAXWEIGHT = "maxWeight";
    private static final String TAG_PRICE = "price";
    
    // contacts JSONArray
    JSONArray products = null;
 
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
  	    setContentView(R.layout.activity_history);
        context = getApplicationContext();
  	    
        response = ConnectionService.post(null, URL, true);
        
        if(response.equals(MSG_ERROR))
        {
        	Log.w("Connection", "Wrong tokken");
            Toast.makeText(context, "Sesja wygas�a", Toast.LENGTH_LONG).show();
  			Intent intent = new Intent(context, MainActivity.class);
  			startActivity(intent);
        }
        // Hashmap for ListView
        ArrayList<RowBean> productList = new ArrayList<RowBean>();
 
        try {
            // Getting Array of Products
            JSONArray products = new JSONArray(response);
 
            // looping through All Products
            for(int i = 0; i < products.length() && i<16; i++){
                JSONObject c = products.getJSONObject(i);
 
                // Storing each json item in variable
                String name = c.getString(TAG_NAME);
                String maxweight = c.getString(TAG_MAXWEIGHT);
                String price = c.getString(TAG_PRICE);

                // creating new HashMap
                RowBean product = new RowBean();

                // adding each child node to HashMap key => value
                product.name=name;
                product.maxweight=maxweight;
                product.price=price;
                
                // adding HashList to ArrayList
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
        	RowBean_data[i]=new RowBean(productList.get(i).name, null, productList.get(i).maxweight, productList.get(i).price+" z�");
        }
        
        RB_History_Adapter adapter = new RB_History_Adapter(this,
                R.layout.custom_history, RowBean_data);
 
        listView1 = (ListView)findViewById(R.id.History_List);
 
        listView1.setAdapter(adapter);

    }
 
}