package com.yudi;
import android.app.Activity;
import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import java.util.ArrayList;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.appindexing.Thing;
import com.google.android.gms.common.api.GoogleApiClient;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class ShoppingCartItemActivity extends ListActivity {
    private ShoppingCartAdapter mAdapter;
    private ArrayList<shoppingCart> data;


    /*shoppingCart item1 = new shoppingCart();
    shoppingCart item2 = new shoppingCart();
    shoppingCart item3 = new shoppingCart();
    shoppingCart item4 = new shoppingCart();
    shoppingCart item5 = new shoppingCart();
    shoppingCart item6 = new shoppingCart();
    shoppingCart item7 = new shoppingCart();
    shoppingCart item8 = new shoppingCart();*/
    int num = 0;
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.item);
        data = new ArrayList<shoppingCart>();
        data.add(new shoppingCart(R.drawable.ginger,"Ginger ale","0",0));
        data.add(new shoppingCart(R.drawable.coke,"Coke","0",0));
        data.add(new shoppingCart(R.drawable.lemonade,"Lemonade","0",0));
        data.add(new shoppingCart(R.drawable.orangejuice,"Orange juice","0",0));
        data.add(new shoppingCart(R.drawable.dasani,"Water","0",0));
        data.add(new shoppingCart(R.drawable.pjuice,"Pineapple juice","0",0));
        data.add(new shoppingCart(R.drawable.peaktea,"Sweet tea","0",0));
        data.add(new shoppingCart(R.drawable.sprite,"Sprite","0",0));
        mAdapter = new ShoppingCartAdapter(data);

        setListAdapter(mAdapter);
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();
    }

    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    public Action getIndexApiAction() {
        Thing object = new Thing.Builder()
                .setName("ShoppingCartItem Page") // TODO: Define a title for the content shown.
                // TODO: Make sure this auto-generated URL is correct.
                .setUrl(Uri.parse("http://[ENTER-YOUR-URL-HERE]"))
                .build();
        return new Action.Builder(Action.TYPE_VIEW)
                .setObject(object)
                .setActionStatus(Action.STATUS_TYPE_COMPLETED)
                .build();
    }

    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        AppIndex.AppIndexApi.start(client, getIndexApiAction());
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        AppIndex.AppIndexApi.end(client, getIndexApiAction());
        client.disconnect();
    }


    public class ShoppingCartAdapter extends BaseAdapter {
        //private ArrayList mData = new ArrayList();
        private Map<Integer, Integer> numbers;
        private ArrayList<shoppingCart> mData;
        private LayoutInflater mInflater;
        private ArrayList<String> receipe = new ArrayList<String>();

        public ShoppingCartAdapter(ArrayList<shoppingCart> data) {
            mInflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            mData = data;
            numbers = new HashMap<Integer, Integer>();
            initDate();

        }

        public Map<Integer, Integer> getNumbers() {
            return numbers;
        }

        private void initDate() {
            for (int i = 0; i < mData.size(); i++) {
                getNumbers().put(i, 0);

            }

        }

        public void addItem(final shoppingCart item) {
            mData.add(item);
            notifyDataSetChanged();
        }

        @Override
        public shoppingCart getItem(int position) {
            return mData.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public int getCount() {
            return mData.size();
        }

        public class ViewHolder {
            ImageView image;
            TextView proName;
            TextView proPrice;
            TextView proCount;
            Button plus;
            Button minus;
            Button order;
        }

        public View getView(int position, View convertView, ViewGroup parent) {
            ViewHolder holder = null;
            if (convertView == null) {
                holder = new ViewHolder();
                convertView = mInflater.inflate(R.layout.item, null);
                holder.image = (ImageView) convertView.findViewById(R.id.pro_image);
                holder.proName = (TextView) convertView.findViewById(R.id.pro_name);
                holder.proPrice = (TextView) convertView.findViewById(R.id.pro_shopPrice);
                holder.proCount = (TextView) convertView.findViewById(R.id.pro_count);
                holder.plus = (Button) convertView.findViewById(R.id.pro_add);
                holder.minus = (Button) convertView.findViewById(R.id.pro_reduce);
                holder.order = (Button) convertView.findViewById(R.id.orderNow);
                convertView.setTag(holder);
            } else {
                holder = (ViewHolder) convertView.getTag();
            }
            holder.order.setVisibility(View.GONE);
            shoppingCart shoppingList = this.mData.get(position);
            holder.proName.setText(shoppingList.getProName().toString());
            //Bitmap bitmap = BitmapFactory.decodeResource(getResources(), shoppingList.getProImg());
            //holder.image.setImageBitmap(bitmap);
            holder.image.setImageResource(shoppingList.getProImg());
            init(holder, position);

            holder.proCount.setText(numbers.get(position).toString());
            //String a = holder.proCount.getText().toString();
            //mData.get(position).setNum(Integer.valueOf(a));
            if (position == 7) {
                holder.order.setVisibility(View.VISIBLE);
            }
            return convertView;
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

        private void init(final ViewHolder holder, final int position) {
            final String numString = String.valueOf(numbers.get(position));
            holder.plus.setOnClickListener(new Button.OnClickListener() {
                @Override
                public void onClick(View v) {

                    if (numString == null || numString.equals("")) {
                        //num = 1;
                        //holder.proCount.setText("1");
                    } else {
                        if (++num < 1) {
                            num--;
                        } else {

                            numbers.put(position, numbers.get(position) + 1);
                            mData.get(position).setNum(numbers.get(position));
                            holder.proCount.setText(numbers.get(position).toString());
                        }
                    }

                }
            });

            holder.minus.setOnClickListener(new Button.OnClickListener() {
                @Override
                public void onClick(View v) {

                    if (numString == null || numString.equals("")) {
                        //num = 1;
                        //holder.proCount.setText("1");
                    } else {
                        if (--num < 1) {
                            num--;
                        } else {
                            numbers.put(position, numbers.get(position) - 1);
                            mData.get(position).setNum(numbers.get(position));
                            holder.proCount.setText(numbers.get(position).toString());
                        }
                    }

                }
            });

            holder.order.setOnClickListener(new Button.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String session = "c";
                    for(int i=0;i<mData.size();i++){
                        int quantity = mData.get(i).num;
                        for(int j=0;j<quantity;j++){
                            receipe.add(String.valueOf(i+1));
                        }

                    }
                    receipe.add("0");
                    Intent i = new Intent(ShoppingCartItemActivity.this, DeviceScanActivity.class);
                    String receipeString = getStringRepresentation(receipe);
                    i.putExtra("RECEIPE", receipeString);
                    i.putExtra("SESSION",session);
                    startActivity(i);

                }

            });
        }
    }
}