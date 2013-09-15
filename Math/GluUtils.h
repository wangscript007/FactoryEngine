
#pragma once

class GluUtils
{
public:
    static int glhProjectf(float objx, float objy, float objz, float *modelview, float *projection, int *viewport, float *windowCoordinate);
    static int glhUnProjectf(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate);
    static int glhInvertMatrixf2(const float *m, float *out);

private:
    static void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2);
    static void MultiplyMatrixByVector4by4OpenGL_FLOAT(float *resultvector, const float *matrix, const float *pvector);




};

