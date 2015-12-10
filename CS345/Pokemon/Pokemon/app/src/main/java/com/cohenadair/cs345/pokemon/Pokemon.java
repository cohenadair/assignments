package com.cohenadair.cs345.pokemon;

public class Pokemon {

    private String mName;
    private boolean mCaught = false;

    public Pokemon(String name) {
        mName = name;
    }

    public String getName() {
        return mName;
    }

    public void setName(String name) {
        mName = name;
    }

    public boolean isCaught() {
        return mCaught;
    }

    public void setCaught(boolean caught) {
        mCaught = caught;
    }
}
