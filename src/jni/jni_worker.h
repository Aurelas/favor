#ifndef favor_jni_reader_include
#define favor_jni_reader_include
#include <jni.h>
#include <reader.h>
#include "jni_exceptions.h"
#include "../worker.h"

namespace favor{
    namespace jni{

        JNIEXPORT jobject JNICALL createContact(JNIEnv* env, jobject callingObj, jstring address, jint type, jstring displayName, jboolean addressExistsHint){
            string addressString = env->GetStringUTFChars(address, NULL);
            string displaynameString = env->GetStringUTFChars(displayName, NULL);
            //Short circuiting saves us the method call if we know the address exists
            if (addressExistsHint || reader::addressExists(addressString, static_cast<MessageType>(type))){
                //We believe our reader or hint, make an address object and pass it in like it was from the database
                Address addrObj(addressString, -1, -1, static_cast<MessageType>(type));
                worker::createContactFromAddress(addrObj, displaynameString);
            } else {
                //There's no address already, so we make one
                worker::createContactWithAddress(addressString, static_cast<MessageType>(type), displaynameString);
            }
        //TODO: contacts probably have to be objects even at the java layer, so we should make one (once the java is written) and return it here
        }

    }
}



#endif