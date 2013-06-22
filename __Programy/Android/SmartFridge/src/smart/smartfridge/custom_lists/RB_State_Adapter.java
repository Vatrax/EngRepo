package smart.smartfridge.custom_lists;

import smart.smartfridge.R;
import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public class RB_State_Adapter extends ArrayAdapter<RowBean>{
	 
    Context context;
    int layoutResourceId;  
    RowBean data[] = null;
 
    public RB_State_Adapter(Context context, int layoutResourceId, RowBean[] data) {
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
            holder.txtName = (TextView)row.findViewById(R.id.name);
            holder.txtWeight = (TextView)row.findViewById(R.id.weight);

 
            row.setTag(holder);
        }
        else
        {
            holder = (RowBeanHolder)row.getTag();
        }
 
        RowBean object = data[position];
        holder.txtName.setText(object.name);
        holder.txtWeight.setText(object.weight);
 
        return row;
    }
 
    static class RowBeanHolder
    {
        TextView txtName;
        TextView txtWeight;

    }
}
