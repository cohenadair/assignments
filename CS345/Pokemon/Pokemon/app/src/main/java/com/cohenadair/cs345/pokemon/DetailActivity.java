package com.cohenadair.cs345.pokemon;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;

public class DetailActivity extends AppCompatActivity {

    public static final String EXTRA_NAME = "extra_name";
    public static final String EXTRA_CAUGHT = "extra_caught";

    private TextView mNameTextView;
    private CheckBox mCaughtCheckBox;

    private boolean mCaught;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        mCaught = getIntent().getBooleanExtra(EXTRA_CAUGHT, false);

        mNameTextView = (TextView)findViewById(R.id.name_text_view);
        mNameTextView.setText(getIntent().getStringExtra(EXTRA_NAME));

        mCaughtCheckBox = (CheckBox)findViewById(R.id.caught_check_box);
        mCaughtCheckBox.setChecked(mCaught);
        mCaughtCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mCaught = isChecked;
                setCaughtResult();
            }
        });
    }

    public static Intent newIntent(Context context, String name, boolean caught) {
        Intent intent = new Intent(context, DetailActivity.class);
        intent.putExtra(EXTRA_NAME, name);
        intent.putExtra(EXTRA_CAUGHT, caught);
        return intent;
    }

    public static boolean wasCaught(Intent result) {
        return result.getBooleanExtra(EXTRA_CAUGHT, false);
    }

    private void setCaughtResult() {
        Intent data = new Intent();
        data.putExtra(EXTRA_CAUGHT, mCaught);
        setResult(RESULT_OK, data);
    }
}
