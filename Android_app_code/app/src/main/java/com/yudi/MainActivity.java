package com.yudi;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Button;
import android.content.Intent;
import android.view.Window;

public class MainActivity extends AppCompatActivity {
    int quantity = 2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        (findViewById(R.id.Drinkmenu)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, drink_menu.class);
                startActivity(i);
            }
        });
        (findViewById(R.id.custom_drink)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this,ShoppingCartItemActivity.class);
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
