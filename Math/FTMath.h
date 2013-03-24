
#pragma once

class FTMath
{
public:
    static float DotProduct(O5Vec3 v1, O5Vec3 v2);
    static float ProjectionInVector(O5Vec3 v1, O5Vec3 v2);
    static float AngleBetweenVectors(O5Vec3 v1, O5Vec3 v2);
    static float VectorLength(O5Vec3 v);
};

