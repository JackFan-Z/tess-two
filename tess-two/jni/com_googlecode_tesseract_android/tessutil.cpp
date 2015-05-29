
//
//  tessutil.cpp
//  CvDetectCard
//
//  Created by YUAN CHANG FAN on 2014/8/20.
//  Copyright (c) 2014年 Invisibi. All rights reserved.
//


#include <stdio.h>
#include "tessmain.h"
#include "resultiterator.h"
#include "allheaders.h"
#include "pageres.h"
#include "tesseractclass.h"

using namespace tesseract;

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


jobjectArray TCListToStringArray(JNIEnv *env, const std::vector< TextConfidence >& tcList)
{
    int size = tcList.size();
    if (size < 0 )
    {
        return NULL;
    }

    const int TMP_SIZE = 64;
    char tmp[TMP_SIZE];
    for (int i=0; i<size; i++)
    {
        snprintf(tmp, TMP_SIZE, "|%.3f %d %d %d %d", tcList[i].confidence,
            tcList[i].pos[0], tcList[i].pos[1],
            tcList[i].pos[2], tcList[i].pos[3]);
        tcList[i].text = tcList[i].text + tmp;
    }

    jobjectArray ret;
    ret= (jobjectArray)env->NewObjectArray(size,env->FindClass("java/lang/String"),env->NewStringUTF(""));
    for(int i=0;i<size;i++)
    {
        env->SetObjectArrayElement(ret,i,env->NewStringUTF(tcList[i].text.c_str()));
    }
    return ret;
}

jobjectArray Java_com_invisibi_tess_Util_nativeGetEmailCandidates(JNIEnv *env, jclass clazz,
    jlong nativeResultIterator) {

    ResultIterator *resultIterator = (ResultIterator *) nativeResultIterator;

    std::vector< TextConfidence > candidateList;
    GetEmailCandidates( resultIterator, candidateList, 75);

    return TCListToStringArray(env, candidateList);
}


jobjectArray Java_com_invisibi_tess_Util_nativeGetFullnameCandidates(JNIEnv *env, jclass clazz,
    jlong nativeResultIterator) {

    ResultIterator *resultIterator = (ResultIterator *) nativeResultIterator;

    std::vector< TextConfidence > candidateList;
    GetFullnameCandidates( resultIterator, candidateList, 65);

    return TCListToStringArray(env, candidateList);
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
