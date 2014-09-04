
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


jobjectArray Java_com_invisibi_tess_Util_nativeGetEmailCandidates(JNIEnv *env, jclass clazz,
    jint nativeResultIterator) {

    ResultIterator *resultIterator = (ResultIterator *) nativeResultIterator;

    std::vector< TextConfidence > candidateList;
    GetEmailCandidates( resultIterator, candidateList, 75);

    int size = candidateList.size();
    if (size < 0 )
    {
        return NULL;
    }

    const int TMP_SIZE = 64;
    char tmp[TMP_SIZE];
    for (int i=0; i<size; i++)
    {
        snprintf(tmp, TMP_SIZE, " %.3f %d %d %d %d", candidateList[i].confidence,
            candidateList[i].pos[0], candidateList[i].pos[1],
            candidateList[i].pos[2], candidateList[i].pos[3]);
        candidateList[i].text = candidateList[i].text + tmp;
    }

    jobjectArray ret;
    ret= (jobjectArray)env->NewObjectArray(size,env->FindClass("java/lang/String"),env->NewStringUTF(""));
    for(int i=0;i<size;i++)
    {
        env->SetObjectArrayElement(ret,i,env->NewStringUTF(candidateList[i].text.c_str()));
    }
    return(ret);
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
