#include <jni.h>
#include "AppCore/AppCore.hpp"
#include <sys/syslog.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_AppCore_AppCoreJava_test(JNIEnv *env, jobject thiz, jstring path) {
    const char *c_path = env->GetStringUTFChars(path, nullptr);

    AppCore(c_path).initialize();

    env->ReleaseStringUTFChars(path, c_path);

    // AppCore().isAppRunning();
    // syslog(LOG_CRIT, "Vitya %s is running", AppCore().isAppRunning());
    // syslog(LOG_CRIT, "Vitya RNPierreMQTT is NULL");
}

extern "C"
JNIEXPORT void JNICALL
Java_org_AppCore_AppCoreJava_getVersion(JNIEnv *env, jobject thiz) {
//    AppCore().initialize();
    // AppCore().isAppRunning();
    // syslog(LOG_CRIT, "Vitya %s is running", AppCore().getVersion().c_str());
    syslog(LOG_CRIT, "Vitya RNPierreMQTT is NULL");
}