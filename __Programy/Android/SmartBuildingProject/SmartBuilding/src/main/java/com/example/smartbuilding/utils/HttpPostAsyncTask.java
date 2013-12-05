package com.example.smartbuilding.utils;

import android.os.AsyncTask;
import android.util.Log;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Wojciech Krzaczek
 */

public class HttpPostAsyncTask extends AsyncTask<String, Void, String> {
    @Override
    protected String doInBackground(String... params) {
        String response = null;
        try {
            HttpClient httpclient = new DefaultHttpClient();
            HttpPost httppost = new HttpPost(params[0]);

            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("id", params[1]));
            nameValuePairs.add(new BasicNameValuePair("value", params[2]));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

            HttpResponse httpResponse = httpclient.execute(httppost);
            response = httpResponse.getEntity().getContent().toString();
            Log.i("Response", response);

        } catch (ClientProtocolException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        } catch (UnsupportedEncodingException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        } catch (IOException e) {
            Log.e("HTTP_ERROR", String.valueOf(e));
        }
        return response;
    }

}

