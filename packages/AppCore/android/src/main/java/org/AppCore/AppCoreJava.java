package org.AppCore;

public class AppCoreJava {
    static {
        System.loadLibrary("AppCore");
    }

    public native void initialize(String path);

    // Native methods
    public native float setFloat(String key, float value);
    public native float getFloat(String key, float defaultValue);

    public native boolean setBool(String key, boolean value);
    public native boolean getBool(String key, boolean defaultValue);

    public native int setInt32(String key, int value);
    public native int getInt32(String key, int defaultValue);

    public native long setInt64(String key, long value);
    public native long getInt64(String key, long defaultValue);

    public native int setUInt32(String key, int value);
    public native int getUInt32(String key, int defaultValue);

    public native long setUInt64(String key, long value);
    public native long getUInt64(String key, long defaultValue);

    public native double setDouble(String key, double value);
    public native double getDouble(String key, double defaultValue);
}
