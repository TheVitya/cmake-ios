#include <jni.h>
#include "{{.ModuleName}}/{{.ModuleName}}.hpp"

extern "C"
JNIEXPORT void JNICALL
Java_org_{{.OrganizationName}}_{{.ModuleName}}Java_initialize(JNIEnv *env, jobject thiz) {
  {{.ModuleName}}::initialize();
}
