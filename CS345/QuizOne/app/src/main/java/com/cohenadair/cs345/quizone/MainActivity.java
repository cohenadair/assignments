package com.cohenadair.cs345.quizone;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

    TextView moodTextView;
    Button sadButton;
    Button madButton;
    Button happyButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.moodTextView = (TextView)findViewById(R.id.mood_text_view);

        View.OnClickListener listener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Button button = (Button)v;
                MainActivity.this.moodTextView.setText(button.getText());
            }
        };

        this.madButton = (Button)findViewById(R.id.mad_button);
        this.madButton.setOnClickListener(listener);

        this.sadButton = (Button)findViewById(R.id.sad_button);
        this.sadButton.setOnClickListener(listener);

        this.happyButton = (Button)findViewById(R.id.happy_button);
        this.happyButton.setOnClickListener(listener);
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
