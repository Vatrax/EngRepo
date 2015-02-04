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

public class AllViewAdapter extends ArrayAdapter<Sector> {

    private final Context context;
    private final Sector[] values;

    public AllViewAdapter(Context context, Sector[] values) {
        super(context, R.layout.row_allview, values);
        this.context = context;
        this.values = values;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) context
                .getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        View rowView = inflater.inflate(R.layout.row_allview, parent, false);
        TextView name = (TextView) rowView.findViewById(R.id.name);
        TextView percentage = (TextView) rowView.findViewById(R.id.percentage);
        ImageView imageView = (ImageView) rowView.findViewById(R.id.logo);
        name.setText(values[position].getName() + " - " + values[position].getDeviceType().toString());

        if (values[position].getValue() > 0) {
            percentage.setText(values[position].getValue() + "%");
            percentage.setVisibility(View.VISIBLE);
            imageView.setImageResource(R.drawable.on);
        }


        return rowView;
    }
}







