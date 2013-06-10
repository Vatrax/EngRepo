package smart.smartfridge;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

public class HistoryActivity extends Activity {
	 private ListView lista;
     
     @Override
     public void onCreate(Bundle savedInstanceState) {
         super.onCreate(savedInstanceState);
         setContentView(R.layout.history);
  
         RowBean RowBean_data[] = new RowBean[] {
  
                 new RowBean("Mas³o","200g","3.50"),
                 new RowBean("Mleko","1000g","2.00"),
         };
  
         RowAdapter adapter = new RowAdapter(this,R.layout.custom_row, RowBean_data);
  
         lista = (ListView)findViewById(R.id.history_list);
  
         lista.setAdapter(adapter);
     }
    
    public class RowBean {
    	 
    	
        public String name;
        public String weight;
        public String price;
     
        public RowBean(){
     
        }
     
        public RowBean(String name, String weight, String price) {
     
            this.name = name;
            this.weight = weight;
            this.price = price;
        }
    }
    
    public class RowAdapter extends ArrayAdapter<RowBean>{
    	 
        Context context;
        int layoutResourceId;  
        RowBean data[] = null;
     
        public RowAdapter(Context context, int layoutResourceId, RowBean[] data) {
            super(context, layoutResourceId, data);
            this.layoutResourceId = layoutResourceId;
            this.context = context;
            this.data = data;
        }
     
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            View row = convertView;
            RowBeanHolder holder = null;
     
            if(row == null)
            {
                LayoutInflater inflater = ((Activity)context).getLayoutInflater();
                row = inflater.inflate(layoutResourceId, parent, false);
     
                holder = new RowBeanHolder();
                holder.name = (TextView)row.findViewById(R.id.name);
                holder.weight = (TextView)row.findViewById(R.id.weight);
                holder.price = (TextView)row.findViewById(R.id.price);
     
                row.setTag(holder);
            }
            else
            {
                holder = (RowBeanHolder)row.getTag();
            }
     
            RowBean object = data[position];
            holder.name.setText(object.name);
            holder.weight.setText(object.weight);
            holder.price.setText(object.price);
     
            return row;
        }
     
        class RowBeanHolder
        {
            TextView name;
            TextView weight;
            TextView price;
        }
    }

  
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
