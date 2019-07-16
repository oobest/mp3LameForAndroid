#include <jni.h>
#include <string>
#include "libmp3lame/lame.h"


static lame_global_flags *lame = NULL;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_albert_study_myapplication_LameUtil_getLameVersion(JNIEnv *env, jclass type) {
    return env->NewStringUTF(get_lame_version());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_albert_study_myapplication_LameUtil_init(JNIEnv *env, jclass type, jint inSamplerate, jint inChannel,
                                                  jint outSamplerate, jint outBitrate, jint quality) {

    if (lame != NULL) {
        lame_close(lame);
        lame = NULL;
    }
    lame = lame_init();
    lame_set_in_samplerate(lame, inSamplerate);
    lame_set_num_channels(lame, inChannel);//输入流的声道
    lame_set_out_samplerate(lame, outSamplerate);
    lame_set_brate(lame, outBitrate);
    lame_set_quality(lame, quality);
    lame_init_params(lame);

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_albert_study_myapplication_LameUtil_encode(JNIEnv *env, jclass type, jshortArray bufferLeft_,
                                                    jshortArray bufferRight_, jint samples, jbyteArray mp3buf_) {
    jshort *bufferLeft = env->GetShortArrayElements(bufferLeft_, NULL);
    jshort *bufferRight = env->GetShortArrayElements(bufferRight_, NULL);
    jbyte *mp3buf = env->GetByteArrayElements(mp3buf_, NULL);
    const jsize mp3bufSize = env->GetArrayLength(mp3buf_);

    int result = lame_encode_buffer(lame, bufferLeft, bufferRight,
                                    samples, reinterpret_cast<unsigned char *>(mp3buf), mp3bufSize);

    env->ReleaseShortArrayElements(bufferLeft_, bufferLeft, 0);
    env->ReleaseShortArrayElements(bufferRight_, bufferRight, 0);
    env->ReleaseByteArrayElements(mp3buf_, mp3buf, 0);
    return result;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_albert_study_myapplication_LameUtil_flush(JNIEnv *env, jclass type, jbyteArray mp3buf_) {
    jbyte *mp3buf = env->GetByteArrayElements(mp3buf_, NULL);
    const jsize mp3bufSize = env->GetArrayLength(mp3buf_);

    int result = lame_encode_flush(lame, reinterpret_cast<unsigned char *>(mp3buf), mp3bufSize);

    env->ReleaseByteArrayElements(mp3buf_, mp3buf, 0);
    return result;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_albert_study_myapplication_LameUtil_close(JNIEnv *env, jclass type) {
    lame_close(lame);
    lame = NULL;
}

