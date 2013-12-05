package com.example.smartbuilding.utils;

import com.example.smartbuilding.model.Sector;

import java.util.Comparator;

/**
 * Created by Wojciech Krzaczek
 */

public class CustomComparator implements Comparator<Sector> {
    @Override
    public int compare(Sector s1, Sector s2) {
        return s1.getDeviceType().toString().compareTo(s2.getDeviceType().toString());
    }
}
