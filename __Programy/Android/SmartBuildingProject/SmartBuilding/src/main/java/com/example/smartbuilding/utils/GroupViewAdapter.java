package com.example.smartbuilding.utils;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.smartbuilding.R;
import com.example.smartbuilding.model.Sector;

/**
 * Created by Wojciech Krzaczek
 */

public class GroupViewAdapter extends ArrayAdapter<Sector> {

    private final Context context;
    private final Sector[] values;

    public GroupViewAdapter(Context context, Sector[] values) {
        super(context, R.layout.row_allview, values);
        this.context = context;
        this.values = values;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) context
                .getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        View rowView = inflater.inflate(R.layout.row_groupview, parent, false);
        TextView name = (TextView) rowView.findViewById(R.id.name);
        name.setText(values[position].getName());

        return rowView;
    }

}
