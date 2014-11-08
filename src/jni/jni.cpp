#include <jni.h>
#include <sys/stat.h>

#include "jni_reader.h"
#include "jni_worker.h"
#include "jni_accountmanager.h"
#include "jni_globals.h"
#include "../logger.h"
#include "../managers/androidtextmanager.h"

extern "C" {

//Java, then package name, then class name, then method name, separated by underscores (also underscores per "." in the package name)
//Basically if you get an error calling this stuff, the solution is replacing every . in the error with an underscore

JNIEXPORT jstring JNICALL helloWorld(JNIEnv* env, jobject obj){
    return env->NewStringUTF("Hello from Favor's native interface!");
}

JNIEXPORT void JNICALL init(JNIEnv* env, jobject obj, jstring path, jboolean first){
    favor::dbPath = env->GetStringUTFChars(path, 0);

    if (first){
        struct stat sb;
        int res = stat(favor::dbPath, &sb);
        if (res == 0 && sb.st_mode && S_IFDIR){
            favor::logger::info("Database already exists");
        }
        else if (ENOENT == errno){
            res = mkdir(favor::dbPath, 0770);
        }
    }
    //TODO: check results, make sure they're good
    favor::initialize();
    if (first) favor::worker::buildDatabase();
    favor::reader::refreshAll();

}

JNIEXPORT void JNICALL cleanup(JNIEnv* env, jobject obj){
    favor::cleanup();
}

static JNINativeMethod coreMethodTable[] = {
        {"helloWorld", "()Ljava/lang/String;", (void*) helloWorld},
        {"init", "(Ljava/lang/String;Z)V", (void*) init},
        {"cleanup", "()V", (void*) cleanup}
};

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    jclass core = env->FindClass(favor::jni::coreClassPath);
    jclass reader = env->FindClass(favor::jni::readerClassPath);
    jclass writer = env->FindClass(favor::jni::writerClassPath);

    favor::jni::account_manager = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass(favor::jni::accountManagerClassPath)));
    favor::jni::account_manager_constructor = env->GetMethodID(favor::jni::account_manager, "<init>", "(Ljava/lang/String;I)V");

    favor::jni::android_text_manager = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass(favor::jni::androidTextManagerClassPath)));
    favor::jni::android_text_manager_constructor = env->GetMethodID(favor::jni::android_text_manager, "<init>", "(Ljava/lang/String;)V");

    favor::jni::java_string = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/lang/String")));



    //It's weird this can happen before init, but init may end up called in this method eventually and this is crucial in any case
    favor::AndroidTextManager::setVM(vm);

    env->RegisterNatives(core, coreMethodTable, sizeof(coreMethodTable) / sizeof(coreMethodTable[0]));
    env->RegisterNatives(reader, favor::jni::readerMethodTable, sizeof(favor::jni::readerMethodTable) / sizeof (favor::jni::readerMethodTable[0]));
    env->RegisterNatives(favor::jni::account_manager, favor::jni::accountManagerMethodTable, sizeof(favor::jni::accountManagerMethodTable) / sizeof(favor::jni::accountManagerMethodTable[0]));

    return JNI_VERSION_1_6;
}

}
