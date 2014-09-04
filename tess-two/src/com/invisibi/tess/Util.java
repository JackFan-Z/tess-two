package com.invisibi.tess;

import com.googlecode.tesseract.android.ResultIterator;

/**
 * Created by jackf on 2014/8/20.
 */
public class Util {

    public static String [] GetEmailCandidates(ResultIterator resultIterator) {
        return nativeGetEmailCandidates(resultIterator.GetNativeResultIterator());
    }

    private native static String [] nativeGetEmailCandidates(int mNativeResultIterator);
}
