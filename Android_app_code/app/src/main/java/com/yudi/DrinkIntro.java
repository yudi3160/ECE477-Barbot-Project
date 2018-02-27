package com.yudi;

import android.content.Intent;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;
import android.widget.ImageView.ScaleType;
import android.widget.TextView;
import android.widget.LinearLayout.LayoutParams;
import android.text.method.ScrollingMovementMethod;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import java.util.ArrayList;

/**
 * Created by yudi on 1/25/17.
 */

public class DrinkIntro extends AppCompatActivity {
    private ArrayList<String> receipe = new ArrayList<String>();
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        final String session = getIntent().getStringExtra("SESSION_ID");
        setContentView(R.layout.drink_intro);
        ImageView myImage = (ImageView) findViewById(R.id.imageView7);
        myImage.setScaleType(ScaleType.FIT_XY);
        LayoutParams lparams = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
        TextView tv = (TextView) findViewById(R.id.textView3);
        tv.setLayoutParams(lparams);
        tv.setMovementMethod(new ScrollingMovementMethod());
        TextView tv2 = (TextView) findViewById(R.id.textView2);
        tv2.setLayoutParams(lparams);
        tv2.setMovementMethod(new ScrollingMovementMethod());
        if(session.equals("a")) {
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.sunset);
            myImage.setImageBitmap(bitmap);

            tv.setText("\n\nArizona Sunset is a fun and fruity, non-alcoholic drink, perfect for warmer weather - it's reminiscent of Arizona's awesomely beautiful sunsets! Since there is no alcohol, it's great for adults and kids!\n");
            //tv.setTextColor(0x191919); // hex color 0xAARRGGBB
            //tv.setBackgroundColor(0x191919);
            //tv.setPadding(20, 100, 20, 20);// in pixels (left, top, right, bottom)

            tv2.setText("RECEIPE:                            \n" +
                    "  2 ounce Sprite\n" +
                    "  2 ounce Orange Juice\n" +
                    "\n\n\n");
            receipe.add("4");
            receipe.add("4");
            receipe.add("8");
            receipe.add("8");
            receipe.add("0");

            //receipe.add("4");
            //receipe.add("5");


            //tv.setTextColor(0x191919); // hex color 0xAARRGGBB
            //tv.setBackgroundColor(0x191919);

        }
        else if(session.equals("p")){
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.pineapple);
            myImage.setImageBitmap(bitmap);
            tv.setText("\n\nThis pineapple lemonade is such a fun twist on traditional lemonade, with the perfect combination of that tangy, slightly-sweet, tropical goodness.\n\n");
            tv2.setText("RECEIPE:                         \n" +
                    "  2 ounce pinapple juice\n" +
                    "  1 ounce lemonade\n" +
                    "  1 ounce water\n" +
                    "  1 ounce Sprite\n" +
                    "  1 cup crushed ice\n" +  "\n\n\n");
            receipe.add("6");
            receipe.add("5");
            receipe.add("8");
            receipe.add("3");
            receipe.add("6");
            receipe.add("0");
        }
        else if(session.equals("i")){
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.icedtea);
            myImage.setImageBitmap(bitmap);
            tv.setText("\n\nThis pineapple lemonade is such a fun twist on traditional lemonade, with the perfect combination of that tangy, slightly-sweet, tropical goodness.\n\n");
            tv2.setText("RECEIPE:                         \n" +
                    "  2 ounce Coke\n" +
                    "  2 ounce Sweet Tea\n" +
                    "  1 ounce water\n" +
                    "  1 ounce Lemonade\n" +
                    "  1 cup crushed ice\n" +  "\n\n\n");
            receipe.add("2");
            receipe.add("2");
            receipe.add("7");
            receipe.add("7");
            receipe.add("5");
            receipe.add("3");
            receipe.add("0");
        }
        else if(session.equals("o")){
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.fizz);
            myImage.setImageBitmap(bitmap);
            tv.setText("\n\nOrange Fizz is refreshing mocktail made with the combination of fresh orange juice and mint. Beverages quench your thirst in colourful spring or in hot summer or warm you up in cold winter.\n\n"
                    );
            tv2.setText("RECEIPE:                         \n" +
                    "  2 ounce orange juice\n" +
                    "  1 ounce lemonade\n" +
                    "  1 ounce Sprite\n" +
                    "  1 ounce ginger ale\n" +
                    "  1 cup crushed ice\n" +  "\n\n\n");
            receipe.add("4");
            receipe.add("3");
            receipe.add("8");
            receipe.add("1");
            receipe.add("4");
            receipe.add("0");
        }
        else if(session.equals("g")){
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.punch);
            myImage.setImageBitmap(bitmap);
            tv.setText("\n\nGabbie's Punch is a sparkling, non-alcoholic punch. The flavors are citrus and spice, with just enough sweetness to bring it all together.\n\n"
            );
            tv2.setText("RECEIPE:                         \n" +
                    "  2 ounce pinapple juice\n" +
                    "  2 ounce lemonade\n" +
                    "  1 ounce ginger ale\n" +
                    "  1 cup crushed ice\n" +  "\n\n\n");
            receipe.add("6");
            receipe.add("1");
            receipe.add("3");
            receipe.add("3");
            receipe.add("6");
            receipe.add("0");
        }
        else if(session.equals("n")){
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.cinderella);
            myImage.setImageBitmap(bitmap);
            tv.setText("\n\nThe Cinderella is an easy mix of three juices, grenadine, and ginger ale. The fruit juices create a tart base that is mellowed by the sweetness of the grenadine and you can adjust it to make it as sweet as you like.\n\n"
            );
            tv2.setText("RECEIPE:                         \n" +
                    "  1 ounce pinapple juice\n" +
                    "  1 ounce lemonade\n" +
                    "  1 ounce orange juice\n" +
                    "  2 ounce ginger ale\n" +
                    "  1 cup crushed ice\n" +  "\n\n\n");
            receipe.add("3");
            receipe.add("4");
            receipe.add("1");
            receipe.add("1");
            receipe.add("0");
        }



        (findViewById(R.id.order)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(DrinkIntro.this, DeviceScanActivity.class);
                String receipeString = getStringRepresentation(receipe);
                i.putExtra("RECEIPE", receipeString);
                i.putExtra("SESSION",session);
                startActivity(i);
            }
        });
    }
    String getStringRepresentation(ArrayList<String> list)
    {
        StringBuilder builder = new StringBuilder(list.size());
        builder.append("[");
        for(String str: list)
        {
            builder.append(str);
            builder.append(",");
        }
        String str = builder.substring(0, builder.toString().length()-1);
        str=str+"]";
        return str;
    }

}
