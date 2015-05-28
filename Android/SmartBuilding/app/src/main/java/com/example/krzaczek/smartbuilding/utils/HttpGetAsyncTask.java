package com.example.krzaczek.smartbuilding.utils;

import android.os.AsyncTask;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

/**
 * Created by Wojciech Krzaczek
 */
public class HttpGetAsyncTask extends AsyncTask<String, Void, String> {

    @Override
    protected String doInBackground(String... params) {
        HttpClient httpClient = new DefaultHttpClient();
        System.out.println(params[0]);
        HttpGet httpGet = new HttpGet(params[0]);

        try {
            System.out.println("execute HTTP");
            HttpResponse httpResponse = httpClient.execute(httpGet);
            System.out.println("httpResponse");
            InputStream inputStream = httpResponse.getEntity().getContent();
            BufferedReader bufferedReader = new BufferedReader(
                    new InputStreamReader(inputStream));
            StringBuilder stringBuilder = new StringBuilder();
            String bufferedStrChunk = null;
            while ((bufferedStrChunk = bufferedReader.readLine()) != null) {
                stringBuilder.append(bufferedStrChunk);
            }
            System.out.println("Returning value of doInBackground :"
                    + stringBuilder.toString());

            return stringBuilder.toString();

        } catch (ClientProtocolException cpe) {
            System.out.println("Exception generates caz of httpResponse :"
                    + cpe);
            cpe.printStackTrace();
        } catch (IOException ioe) {
            System.out
                    .println("Second exception generates caz of httpResponse :"
                            + ioe);
            ioe.printStackTrace();
        }

        return null;
    }

}
