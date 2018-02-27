package com.yudi;

/**
 * Created by yudi on 2/8/17.
 */

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Button;
import java.text.NumberFormat;
import android.content.Intent;
import android.util.Log;

public class drink_menu extends AppCompatActivity {
    int quantity = 2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.drink_menu);

        (findViewById(R.id.sunset)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(drink_menu.this, DrinkIntro.class);
                String sessionID = "a";
                i.putExtra("SESSION_ID", sessionID);
                startActivity(i);
            }
        });
        (findViewById(R.id.pinapple)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(drink_menu.this, DrinkIntro.class);
                String sessionID = "p";
                i.putExtra("SESSION_ID", sessionID);
                startActivity(i);
            }
        });
        (findViewById(R.id.iceTea)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(drink_menu.this, DrinkIntro.class);
                String sessionID = "i";
                i.putExtra("SESSION_ID", sessionID);
                startActivity(i);
            }
        });
        (findViewById(R.id.fizz)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(drink_menu.this, DrinkIntro.class);
                String sessionID = "o";
                i.putExtra("SESSION_ID", sessionID);
                startActivity(i);
            }
        });
        (findViewById(R.id.punch)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(drink_menu.this, DrinkIntro.class);
                String sessionID = "g";
                i.putExtra("SESSION_ID", sessionID);
                startActivity(i);
            }
        });
        (findViewById(R.id.cinderalla)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(drink_menu.this, DrinkIntro.class);
                String sessionID = "n";
                i.putExtra("SESSION_ID", sessionID);
                startActivity(i);
            }
        });
    }
    /** This method is called when the plus button is clicked.**/
    public void increment(View view) {
        quantity = quantity + 1;
        display(quantity);
    }

    /** This method is called when the minus button is clicked.**/
    public void decrement(View view) {
        quantity = quantity - 1;
        display(quantity);
    }

    /**
     * This method is called when the order button is clicked.
     */
    public void submitOrder(View view) {
        int Price = quantity * 5;
        String PriceMessage = "Total: $" + Price + "\nThank you!";
        //displayMessage(PriceMessage);
    }

    /**
     * This method displays the given quantity value on the screen.
     */
    private void display(int number) {
        /*TextView quantityTextView = (TextView) findViewById(
                R.id.quantity_text_view);
        quantityTextView.setText("" + number);*/
    }




    /**
     * This method displays the given price on the screen.
     */
    private void displayPrice(int number) {
        //TextView priceTextView = (TextView) findViewById(R.id.price_text_view);
        //priceTextView.setText(NumberFormat.getCurrencyInstance().format(number));
    }

    /**
     * This method displays the given text on the screen.
     */
    private void displayMessage(String message) {
        //TextView priceTextView = (TextView) findViewById(R.id.price_text_view);
        //priceTextView.setText(message);
    }
}

