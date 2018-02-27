package com.yudi;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

/**
 * Created by yudi on 3/21/17.
 */

public class Popup extends AppCompatActivity {
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.popup);


        Intent i = new Intent(Popup.this, MainActivity.class);
        startActivity(i);


    }

}

