package com.example.krzaczek.smartbuilding.exceptions;

import android.util.Log;

/**
 * Created by Wojciech Krzaczek
 */

public class noButtonException extends Exception {

    public noButtonException() {
        Log.e("ERROR", "There is no Activity for this button");
    }
}
