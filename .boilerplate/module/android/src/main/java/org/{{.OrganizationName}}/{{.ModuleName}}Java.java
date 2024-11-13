package org.{{.OrganizationName}};

public class {{.ModuleName}}Java {
    static {
        System.loadLibrary("{{.ModuleName}}");
    }

    public native void test();
}
