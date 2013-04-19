
#include <Interaction/InteractionAssistant.h>
#include <Math/Utils.h>
#include <Math/Geometry.h>

namespace ftr {

const float InteractionAssistant::c_fSensitivity = 20.0f;

Vec3 InteractionAssistant::AxisAlignedViewport(const Vec3& vStartScene,
                                                   const Vec3& vEndViewport) const
{
    Vec3 vStart = Utils::Viewport(vStartScene);
    Vec3 vCurrent = vEndViewport - vStart;
    Vec3 vAxisX = Utils::Viewport(Vec3::X);
    Vec3 vAxisY = Utils::Viewport(Vec3::Y);
    Vec3 vAxisZ = Utils::Viewport(Vec3::Z);
    Vec3 vPerp;
    //
    // Finding perpendiculars to axis aligned vectors
    //
    float fLength = vCurrent.Length();
    vPerp.mX = tanf(vAxisX.Angle(vCurrent)) * fLength;
    vPerp.mY = tanf(vAxisY.Angle(vCurrent)) * fLength;
    vPerp.mZ = tanf(vAxisZ.Angle(vCurrent)) * fLength;
    
    float fMin = vPerp.Min();
    
    if (fMin < c_fSensitivity) {
        Vec3 vProjection;
        if      (fMin == vPerp.mX) vProjection = Vec3::X * vCurrent.ProjectionIn(vAxisX);
        else if (fMin == vPerp.mY) vProjection = Vec3::X * vCurrent.ProjectionIn(vAxisY);
        else if (fMin == vPerp.mZ) vProjection = Vec3::X * vCurrent.ProjectionIn(vAxisZ);
        return vStart + vProjection;
    }
    //
    // Unchanged
    //
    return vEndViewport;
}

}