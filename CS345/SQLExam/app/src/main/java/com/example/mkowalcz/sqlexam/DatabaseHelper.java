package com.example.mkowalcz.sqlexam;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import static com.example.mkowalcz.sqlexam.DatabaseSchema.*;

public class DatabaseHelper extends SQLiteOpenHelper {

    public static final String DATABASE_NAME = "Library";
    public static final int VERSION = 1;

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE " + LibraryTable.NAME + "(" +
            LibraryTable.Columns.TITLE + " TEXT NOT NULL, " +
            LibraryTable.Columns.ISBN + " INTEGER NOT NULL UNIQUE" +
            ")"
        );
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
