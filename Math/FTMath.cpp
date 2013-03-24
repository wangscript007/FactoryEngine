
#include <Math/FTMath.h>

float FTMath::DotProduct(O5Vec3 v1, O5Vec3 v2)
{
    return v1.m_fX*v2.m_fX + v1.m_fY*v2.m_fY + v1.m_fZ*v2.m_fZ;
}

float FTMath::VectorLength(O5Vec3 v)
{
    return sqrtf(v.m_fX*v.m_fX + v.m_fY*v.m_fY + v.m_fZ*v.m_fZ);
}

float FTMath::AngleBetweenVectors(O5Vec3 v1, O5Vec3 v2)
{
    return acosf( DotProduct(v1, v2) / (VectorLength(v1)+VectorLength(v2)) );
}

float FTMath::ProjectionInVector(O5Vec3 v1, O5Vec3 v2)
{
    return VectorLength(v1)*cosf(AngleBetweenVectors(v1, v2));
}

