package com.example.krzaczek.contactlistener;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.support.v7.app.ActionBarActivity;
import android.text.Editable;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends ActionBarActivity {

    private static final int PICK_CONTACT = 1234;
    private static final int MY_REQUEST_ID = 1235;
    private TextView phoneNumber;
    private TextView nameLabel;
    private EditText longtitute;
    private EditText latitude;
    private TextView result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button loadContact = (Button) findViewById(R.id.loadContact);
        Button callButton = (Button) findViewById(R.id.call);
        Button searchGoogle = (Button) findViewById(R.id.search);
        Button calculate = (Button) findViewById(R.id.calculate);
        phoneNumber = (TextView) findViewById(R.id.phoneNumber);
        result = (TextView) findViewById(R.id.result);
        nameLabel = (TextView) findViewById(R.id.name);
        longtitute = (EditText) findViewById(R.id.lon);
        latitude = (EditText) findViewById(R.id.lat);

        loadContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent it = new Intent(Intent.ACTION_PICK, ContactsContract.Contacts.CONTENT_URI);
                startActivityForResult(it, PICK_CONTACT);

            }
        });

        callButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (phoneNumber.getText() != null) {
                    String uri = "tel:" + phoneNumber.getText();
                    Intent intent = new Intent(Intent.ACTION_CALL, Uri.parse(uri));
                    startActivity(intent);
                }
            }
        });

        searchGoogle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Editable latitude = MainActivity.this.latitude.getText();
                Editable longitude = MainActivity.this.longtitute.getText();
                if (longitude != null && latitude != null) {
                    String uri = "geo:" + longitude + "," + latitude;
                    Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(uri));
                    startActivity(intent);
                }
            }
        });
        calculate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, SecoundaryActivity.class);
                startActivityForResult(intent, MY_REQUEST_ID);
            }
        });
    }


    @Override
    public void onActivityResult(int reqCode, int resultCode, Intent data) {
        super.onActivityResult(reqCode, resultCode, data);
        if (reqCode == PICK_CONTACT && resultCode == Activity.RESULT_OK) {
            performUserData(data.getData());
        }
        if (reqCode == MY_REQUEST_ID && resultCode == Activity.RESULT_OK) {
            result.setText(data.getStringExtra("result"));
        }
    }

    private void performUserData(Uri data1) {
        Cursor c = managedQuery(data1, null, null, null, null);
        if (c.moveToFirst()) {
            setLabels(c);
        }
    }

    private void setLabels(Cursor c) {
        phoneNumber.setText(getPhoneNumber(c));
        nameLabel.setText(getContactName(c));

    }

    private String getContactName(Cursor c) {
        return c.getString(c.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
    }

    private String getPhoneNumber(Cursor c) {
        String id = c.getString(c.getColumnIndexOrThrow(ContactsContract.Contacts._ID));
        String hasPhone = c.getString(c.getColumnIndex(ContactsContract.Contacts.HAS_PHONE_NUMBER));
        if (hasPhone.equalsIgnoreCase("1")) {
            return getPhoneNumberByID(id);
        }
        return id;
    }

    private String getPhoneNumberByID(String id) {
        Cursor phones = getContentResolver().query(
                ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null,
                ContactsContract.CommonDataKinds.Phone.CONTACT_ID + " = " + id,
                null, null);
        phones.moveToFirst();
        String phoneNumber = phones.getString(phones.getColumnIndex("data1"));
        phones.close();
        return phoneNumber;
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
