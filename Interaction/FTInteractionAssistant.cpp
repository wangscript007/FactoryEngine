
#include "FTInteractionAssistant.h"
#include <Math/FTMath.h>
#include <Math/FTUtils.h>
#include "FTGeometry.h"

const float FTInteractionAssistant::c_fSensitivity = 20.0f;

O5Vec3 FTInteractionAssistant::AxisAlignedViewport(const O5Vec3& vStartScene, const O5Vec3& vEndViewport) const
{
    O5Vec3 vStartViewport = FTUtils::WindowFromScene(vStartScene);
    O5Vec3 vCurrentViewport = vEndViewport - vStartViewport;
    float fLength = FTMath::VectorLength(vCurrentViewport);
    
    O5Vec3 vAxisViewportX, vAxisViewportY, vAxisViewportZ;
    float fAngle, x, y, z;
    vAxisViewportX = FTUtils::WindowFromScene(O5Vec3(1.0f ,0.0f, 0.0f));
    fAngle = FTMath::AngleBetweenVectors(vAxisViewportX, vCurrentViewport);
    x = tanf(fAngle)*fLength;
    
    vAxisViewportY = FTUtils::WindowFromScene(O5Vec3(0.0f ,1.0f, 0.0f));
    fAngle = FTMath::AngleBetweenVectors(vAxisViewportY, vCurrentViewport);
    y = tanf(fAngle)*fLength;
    
    vAxisViewportZ = FTUtils::WindowFromScene(O5Vec3(0.0f ,0.0f, 1.0f));
    fAngle = FTMath::AngleBetweenVectors(vAxisViewportZ, vCurrentViewport);
    z = tanf(fAngle)*fLength;
    
    FTAxis eAxis = x < y ? (x < z ? kAxisX : (y < z ? kAxisY : kAxisZ)) : (y < z ? kAxisY : (x < z ? kAxisX : kAxisZ));
    
    switch (eAxis) {
        case kAxisX : {
            if (x <= c_fSensitivity) {
                return vStartViewport + O5Vec3(FTMath::ProjectionInVector(vCurrentViewport, vAxisViewportX), 0.0f, 0.0f);
            }
        } break;
        case kAxisY : {
            if (y <= c_fSensitivity) {
                return vStartViewport + O5Vec3(0.0f, FTMath::ProjectionInVector(vCurrentViewport, vAxisViewportY), 0.0f);
            }
        } break;
        case kAxisZ : {
            if (z <= c_fSensitivity) {
                return vStartViewport + O5Vec3(0.0f, 0.0f, FTMath::ProjectionInVector(vCurrentViewport, vAxisViewportX));
            }
        } break;
    }
    return vEndViewport;
}