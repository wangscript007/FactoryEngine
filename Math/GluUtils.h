
#pragma once

class GluUtils
{
public:
    static int glhProjectf(float objx, float objy, float objz,
                           const float *modelview, const float *projection, const float *viewport,
                           float *windowCoordinate);
    static int glhUnProjectf(float winx, float winy, float winz,
                             const float *modelview, const float *projection, const float *viewport,
                             float *objectCoordinate);
    static int glhInvertMatrixf2(const float *m, float *out);

private:
    static void MultiplyMatrices4by4OpenGL_FLOAT(float *result, const float *matrix1,const float *matrix2);
    static void MultiplyMatrixByVector4by4OpenGL_FLOAT(float *resultvector, const float *matrix, const float *pvector);




};

