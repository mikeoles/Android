package edu.pitt.cs.cs1635.mbo10.postagecalculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button calculate = (Button)findViewById(R.id.calculate);
        calculate.setOnClickListener(
                new Button.OnClickListener(){
                    public void onClick(View v) {
                        //get Weight
                        EditText weight = (EditText) findViewById(R.id.weight);
                        Integer mailWeight = Integer.parseInt(weight.getText().toString());

                        //get PackageType (0-2)
                        RadioGroup radioButtonGroup = (RadioGroup) findViewById(R.id.packageType);
                        int radioButtonID = radioButtonGroup.getCheckedRadioButtonId();
                        View radioButton = radioButtonGroup.findViewById(radioButtonID);
                        Integer choice = radioButtonGroup.indexOfChild(radioButton);

                        TextView price = (TextView) findViewById(R.id.price);

                        String total = "";

                        if (mailWeight > 13) {
                            price.setText("Weight Above Max");
                        } else {

                            //Letter
                            if (choice == 0) {
                                if (mailWeight <= 1) {
                                    total = "$0.49";
                                } else if (mailWeight == 2) {
                                    total = "$0.71";
                                } else if (mailWeight == 3) {
                                    total = "$0.93";
                                } else {
                                    total = "3oz letter max";
                                }
                            }


                            //Large Envelope
                            if (choice == 1) {

                                if(mailWeight<=1){
                                    total = "$0.98";
                                }else if(mailWeight==2){
                                    total = "$1.20";
                                }else if(mailWeight==3){
                                    total = "$1.42";
                                }else if(mailWeight==4){
                                    total = "$1.64";
                                }else if(mailWeight==5){
                                    total = "$1.86";
                                }else if(mailWeight==6){
                                    total = "$2.08";
                                }else if(mailWeight==7){
                                    total = "$2.30";
                                }else if(mailWeight==8){
                                    total = "$2.52";
                                }else if(mailWeight==9){
                                    total = "$2.74";
                                }else if(mailWeight==10){
                                    total = "$2.96";
                                }else if(mailWeight==11){
                                    total = "$3.18";
                                }else if(mailWeight==12){
                                    total = "$3.50";
                                }else{
                                    total = "$3.62";
                                }

                            }

                            //Package
                            if (choice == 2) {

                                if(mailWeight<=3){
                                    total = "$2.54";
                                }else if(mailWeight==4){
                                    total = "$2.74";
                                }else if(mailWeight==5){
                                    total = "$2.94";
                                }else if(mailWeight==6){
                                    total = "$3.14";
                                }else if(mailWeight==7){
                                    total = "$3.34";
                                }else if(mailWeight==8){
                                    total = "$3.54";
                                }else if(mailWeight==9){
                                    total = "$3.74";
                                }else if(mailWeight==10){
                                    total = "$3.94";
                                }else if(mailWeight==11){
                                    total = "$4.14";
                                }else if(mailWeight==12){
                                    total = "$4.34";
                                }else{
                                    total = "$4.54";
                                }

                            }

                            price.setText(total);
                        }
                    }
                }
        );
    }

}
