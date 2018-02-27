package com.yudi;

import android.content.Context;
import android.os.Bundle;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Button;
import junit.framework.Test;
import java.util.List;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import android.R.string;

import static android.R.attr.button;

public class shoppingCart implements Serializable {
        public int proImg;
        public String ProName;
        public String proCount;
        public int num;
        public shoppingCart(int Img,String Name,String Count,int Num){
            setProCount(Count);
            setProName(Name);
            setNum(Num);
            setProImg(Img);
        }
        public int getProImg() {
            return proImg;
        }
        public void setProImg(int Img) {
            proImg = Img;
        }
        public String getProName() {
            return ProName;
        }
        public void setProName(String proName) {
        ProName = proName;
    }
    public String getProCount() {
        return proCount;
    }
    public void setProCount(String proCount) {
        proCount = proCount;
    }

    public void setNum(int number){
        num = number;
    }
}