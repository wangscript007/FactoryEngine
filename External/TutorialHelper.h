

#pragma once

class TutorialHelper
{
public:
    static void crossProduct( float *a, float *b, float *res);
    static void normalize(float *a);
    static void setIdentityMatrix( float *mat, int size);
    static void multMatrix(float *a, float *b);
    static void setTranslationMatrix(float *mat, float x, float y, float z);
    static void buildProjectionMatrix(float *mat, float fov, float ratio, float nearP, float farP);
    static void setCamera(float *mat, float posX, float posY, float posZ,
                          float lookAtX, float lookAtY, float lookAtZ);
    
};

