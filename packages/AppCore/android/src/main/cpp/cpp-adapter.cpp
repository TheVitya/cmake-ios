#include <jni.h>
#include "AppCore/AppCore.hpp"
#include <sys/syslog.h>

std::string jstringToString(JNIEnv *env, jstring jstr) {
    const char* chars = env->GetStringUTFChars(jstr, nullptr);
    std::string result(chars);
    env->ReleaseStringUTFChars(jstr, chars);
    return result;
}

#define CREATE_JNI_GET_SET_FUNC(TYPE, TYPE_NAME, JTYPE, CONVERT_TO_JAVA)                                    \
extern "C" JNIEXPORT JTYPE JNICALL                                                                          \
Java_org_AppCore_AppCoreJava_set##TYPE_NAME(JNIEnv *env, jobject thiz, jstring key, JTYPE value) {          \
    auto instance = AppCore::instance();                                                                    \
    const std::string cppKey = jstringToString(env, key);                                                   \
    const auto result = instance.set_##TYPE(cppKey.c_str(), value);                                         \
    return CONVERT_TO_JAVA(env, result);                                                                    \
}                                                                                                           \
                                                                                                            \
extern "C" JNIEXPORT JTYPE JNICALL                                                                          \
Java_org_AppCore_AppCoreJava_get##TYPE_NAME(JNIEnv *env, jobject thiz, jstring key, JTYPE default_value) {  \
    auto instance = AppCore::instance();                                                                    \
    const std::string cppKey = jstringToString(env, key);                                                   \
    const auto result = instance.get_##TYPE(cppKey.c_str(), default_value);                                 \
    return CONVERT_TO_JAVA(env, result);                                                                    \
}

extern "C"
JNIEXPORT void JNICALL
Java_org_AppCore_AppCoreJava_initialize(JNIEnv *env, jobject thiz, jstring path) {
    const char *c_path = env->GetStringUTFChars(path, nullptr);

    AppCore::initialize(AppCoreConfig({ .system_path = c_path }));

    env->ReleaseStringUTFChars(path, c_path);
}

CREATE_JNI_GET_SET_FUNC(float, Float, jfloat, [](JNIEnv*, float val) { return val; })
CREATE_JNI_GET_SET_FUNC(bool, Bool, jboolean, [](JNIEnv*, bool val) { return val; })
CREATE_JNI_GET_SET_FUNC(int32_t, Int32, jint, [](JNIEnv*, int32_t val) { return val; })
CREATE_JNI_GET_SET_FUNC(int64_t, Int64, jlong, [](JNIEnv*, int64_t val) { return val; })
CREATE_JNI_GET_SET_FUNC(uint32_t, UInt32, jint, [](JNIEnv*, uint32_t val) { return static_cast<jint>(val); })
CREATE_JNI_GET_SET_FUNC(uint64_t, UInt64, jlong, [](JNIEnv*, uint64_t val) { return static_cast<jlong>(val); })
CREATE_JNI_GET_SET_FUNC(double, Double, jdouble, [](JNIEnv*, double val) { return val; })
