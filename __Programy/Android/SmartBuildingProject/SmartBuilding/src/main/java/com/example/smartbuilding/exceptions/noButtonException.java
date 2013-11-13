package com.example.smartbuilding.exceptions;

import android.util.Log;

/**
 * Created by Vatrax on 02.11.13.
 */
public class noButtonException extends Exception {

    public noButtonException(){
        Log.e("ERROR", "There is no Activity for this button");
    }
}
