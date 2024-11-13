package org.AppCore;

public class AppCoreJava {
    static {
        System.loadLibrary("AppCore");
    }

    public native void test();
}
