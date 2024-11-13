#include <jni.h>
#include "AppCore/AppCore.hpp"
#include <sys/syslog.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_AppCore_AppCoreJava_test(JNIEnv *env, jobject thiz) {
    AppCore().initialize();
    AppCore().isAppRunning();
    syslog(LOG_CRIT, "Vitya %s is running", AppCore().isAppRunning());
    syslog(LOG_CRIT, "Vitya RNPierreMQTT is NULL");
}
