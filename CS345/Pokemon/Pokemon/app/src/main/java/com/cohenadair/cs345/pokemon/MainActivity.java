package com.cohenadair.cs345.pokemon;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_CODE_DETAIL = 0;
    private static final String KEY_CURRENT = "key_current";

    private ListView mListView;

    private Pokemon[] mPokedex = new Pokemon[] {
            new Pokemon("Weedle"),
            new Pokemon("Pidgey"),
            new Pokemon("Caterpie"),
            new Pokemon("Rattata"),
            new Pokemon("Spearow"),
            new Pokemon("Ekans"),
            new Pokemon("Sandshrew"),
            new Pokemon("Nidoran"),
            new Pokemon("Nidorina"),
            new Pokemon("Clefairy"),
            new Pokemon("Vulpix"),
            new Pokemon("Jigglypuff"),
    };

    private int mCurrentIndex;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (savedInstanceState != null)
            mCurrentIndex = savedInstanceState.getInt(KEY_CURRENT, 0);

        load();

        mListView = (ListView)findViewById(R.id.list_view);

        mListView.setAdapter(new ArrayAdapter<Pokemon>(this, android.R.layout.simple_list_item_2, android.R.id.text1, mPokedex) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                View view = super.getView(position, convertView, parent);

                TextView name = (TextView)view.findViewById(android.R.id.text1);
                TextView caught = (TextView)view.findViewById(android.R.id.text2);

                name.setText(mPokedex[position].getName());
                caught.setText(mPokedex[position].isCaught() ? "Caught" : "Not caught");

                return view;
            }
        });

        mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                mCurrentIndex = position;

                Intent intent = DetailActivity.newIntent(MainActivity.this, mPokedex[position].getName(), mPokedex[position].isCaught());
                startActivityForResult(intent, REQUEST_CODE_DETAIL);
            }
        });
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putInt(KEY_CURRENT, mCurrentIndex);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode != RESULT_OK)
            return;

        if (requestCode == REQUEST_CODE_DETAIL) {
            if (data == null)
                return;

            mPokedex[mCurrentIndex].setCaught(DetailActivity.wasCaught(data));

            // update "caught" labels
            ArrayAdapter adapter = (ArrayAdapter)mListView.getAdapter();
            adapter.notifyDataSetChanged();

            save();
        }
    }

    private void save() {
        SharedPreferences prefs = getPreferences(MODE_PRIVATE);
        SharedPreferences.Editor editor = prefs.edit();

        for (int i = 0; i < mPokedex.length; i++)
            editor.putBoolean(Integer.toString(i), mPokedex[i].isCaught());

        editor.apply();
    }

    private void load() {
        SharedPreferences prefs = getPreferences(MODE_PRIVATE);

        for (int i = 0; i < mPokedex.length; i++)
            mPokedex[i].setCaught(prefs.getBoolean(Integer.toString(i), false));
    }
}
