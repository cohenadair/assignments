package com.cohenadair.cs345.count;

import android.app.Activity;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.Date;

public class MainActivity extends Activity {

    private final String KEY_PRESSES = "key_presses";
    private final String KEY_DATE = "key_date";

    Button mCountButton;
    TextView mPressesTextView;
    TextView mDateTextView;

    int mPresses = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        retrieveCount();

        mCountButton = (Button)findViewById(R.id.button_count);
        mCountButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mPresses++;
                updatePressesText();
                saveCount();
            }
        });

        mPressesTextView = (TextView)findViewById(R.id.presses_text_view);
        updatePressesText();

        mDateTextView = (TextView)findViewById(R.id.date_text_view);
        mDateTextView.setText(getResources().getString(R.string.text_view_started) + " " + new Date().toString());

        if (savedInstanceState != null)
            mDateTextView.setText(savedInstanceState.getString(KEY_DATE, new Date().toString()));
    }

    private void updatePressesText() {
        mPressesTextView.setText(getResources().getString(R.string.text_view_count) + " " + mPresses);
    }

    private void saveCount() {
        SharedPreferences prefs = getPreferences(MODE_PRIVATE);
        prefs.edit().putInt(KEY_PRESSES, mPresses).apply();
    }

    private void retrieveCount() {
        SharedPreferences prefs = getPreferences(MODE_PRIVATE);
        mPresses = prefs.getInt(KEY_PRESSES, 0);
    }

    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState) {
        savedInstanceState.putString(KEY_DATE, mDateTextView.getText().toString());
    }
}
