package com.example.mkowalcz.sqlexam;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import static com.example.mkowalcz.sqlexam.DatabaseSchema.LibraryTable;

public class MainActivity extends AppCompatActivity {
    private SQLiteDatabase mDatabase;
    private TextView mList;
    private EditText mTitleEdit, mIsbnEdit;
    private Button mInsertButton, mUpdateButton, mDeleteButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mDatabase = new DatabaseHelper(this).getWritableDatabase();

        mList = (TextView)findViewById(R.id.text_view);

        mTitleEdit = (EditText)findViewById(R.id.title_edit);
        mIsbnEdit = (EditText)findViewById(R.id.isbn_edit);

        mInsertButton = (Button)findViewById(R.id.insert_button);
        mInsertButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                insertBook();
                updateList();
            }
        });

        mUpdateButton = (Button)findViewById(R.id.update_button);
        mUpdateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateBook();
                updateList();
            }
        });

        mDeleteButton = (Button)findViewById(R.id.delete_button);
        mDeleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                deleteBook();
                updateList();
            }
        });

        updateList();
    }

    private void updateList() {
        String list = "";

        Cursor cursor = mDatabase.query(LibraryTable.NAME, null, null, null, null, null, null);

        if (cursor.moveToFirst())
            while (!cursor.isAfterLast()) {
                String title = cursor.getString(cursor.getColumnIndex(LibraryTable.Columns.TITLE));
                int isbn = cursor.getInt(cursor.getColumnIndex(LibraryTable.Columns.ISBN));
                list += title + " " + isbn + "\n";
                cursor.moveToNext();
            }

        cursor.close();
        mList.setText(list);
    }

    private boolean inputIsEmpty() {
        return (mTitleEdit.getText().toString().equals("") || mIsbnEdit.getText().toString().equals(""));
    }

    private void clearInput() {
        mTitleEdit.setText("");
        mIsbnEdit.setText("");
    }

    private ContentValues getContentValues() {
        ContentValues values = new ContentValues();
        values.put(LibraryTable.Columns.TITLE, mTitleEdit.getText().toString());
        values.put(LibraryTable.Columns.ISBN, mIsbnEdit.getText().toString());
        return values;
    }

    private void insertBook() {
        if (inputIsEmpty())
            return;

        mDatabase.insert(LibraryTable.NAME, null, getContentValues());
        clearInput();
    }

    private void updateBook() {
        if (inputIsEmpty())
            return;

        mDatabase.update(LibraryTable.NAME, getContentValues(), LibraryTable.Columns.ISBN + " = ?", new String[] { mIsbnEdit.getText().toString() });
        clearInput();
    }

    private void deleteBook() {
        if (mIsbnEdit.getText().toString().equals(""))
            return;

        mDatabase.delete(LibraryTable.NAME, LibraryTable.Columns.ISBN + " = ?", new String[] { mIsbnEdit.getText().toString() });
        clearInput();
    }
}
