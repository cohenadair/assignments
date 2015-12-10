package com.cohenadair.cs345.finalexam;

import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import static com.cohenadair.cs345.finalexam.DatabaseSchema.NumberTable;

public class MainActivity extends AppCompatActivity {

    private SQLiteDatabase mDatabase;

    private EditText mInputEditText;
    private Button mAddButton;
    private Button mAverageButton;
    private Button mEducatButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mDatabase = new DatabaseHelper(this).getWritableDatabase();

        mInputEditText = (EditText)findViewById(R.id.input_edit_text);

        mAddButton = (Button)findViewById(R.id.add_button);
        mAddButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mInputEditText.getText().toString().equals(""))
                    return;

                mDatabase.insert(NumberTable.NAME, null, getInputContentValues());
                mInputEditText.setText("");
            }
        });

        mAverageButton = (Button)findViewById(R.id.average_button);
        mAverageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AverageDialogFragment dialog = new AverageDialogFragment();
                dialog.setAverage(getAverage());
                dialog.show(getSupportFragmentManager(), null);
            }
        });

        mEducatButton = (Button)findViewById(R.id.educat_button);
        mEducatButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openEducat();
            }
        });
    }

    private ContentValues getInputContentValues() {
        ContentValues values = new ContentValues();

        double input = Double.parseDouble(mInputEditText.getText().toString());
        values.put(NumberTable.Columns.VALUE, input);

        return values;
    }

    private double getAverage() {
        Cursor cursor = mDatabase.rawQuery("SELECT AVG(" + NumberTable.Columns.VALUE + ") FROM " + NumberTable.NAME, null);

        if (cursor.moveToFirst())
            return cursor.getDouble(0);

        cursor.close();
        return -1;
    }

    private void openEducat() {
        startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://educat.nmu.edu/")));
    }
}
