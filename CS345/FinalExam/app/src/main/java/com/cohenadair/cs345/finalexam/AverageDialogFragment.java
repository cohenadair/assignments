package com.cohenadair.cs345.finalexam;

import android.app.Dialog;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;

public class AverageDialogFragment extends DialogFragment {

    private double mAverage = 0.0;

    public AverageDialogFragment() {

    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        return new AlertDialog.Builder(getActivity())
                .setMessage(getResources().getString(R.string.msg_average) + " " + mAverage + ".")
                .setPositiveButton(R.string.okay, null)
                .create();
    }

    public void setAverage(double average) {
        mAverage = average;
    }
}
