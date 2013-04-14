
#include <Interaction/InteractionAssistant.h>
#include <Math/Utils.h>
#include <Math/Geometry.h>

namespace Factory {

const float InteractionAssistant::c_fSensitivity = 20.0f;

O5Vec3 InteractionAssistant::AxisAlignedViewport(const O5Vec3& vStartScene,
                                                   const O5Vec3& vEndViewport) const
{
    O5Vec3 vStart = Utils::Viewport(vStartScene);
    O5Vec3 vCurrent = vEndViewport - vStart;
    O5Vec3 vAxisX = Utils::Viewport(O5Vec3::X);
    O5Vec3 vAxisY = Utils::Viewport(O5Vec3::Y);
    O5Vec3 vAxisZ = Utils::Viewport(O5Vec3::Z);
    O5Vec3 vPerp;
    //
    // Finding perpendiculars to axis aligned vectors
    //
    float fLength = vCurrent.Length();
    vPerp.m_fX = tanf(vAxisX.Angle(vCurrent)) * fLength;
    vPerp.m_fY = tanf(vAxisY.Angle(vCurrent)) * fLength;
    vPerp.m_fZ = tanf(vAxisZ.Angle(vCurrent)) * fLength;
    
    float fMin = vPerp.Min();
    
    if (fMin < c_fSensitivity) {
        O5Vec3 vProjection;
        if      (fMin == vPerp.m_fX) vProjection = O5Vec3::X * vCurrent.ProjectionIn(vAxisX);
        else if (fMin == vPerp.m_fY) vProjection = O5Vec3::X * vCurrent.ProjectionIn(vAxisY);
        else if (fMin == vPerp.m_fZ) vProjection = O5Vec3::X * vCurrent.ProjectionIn(vAxisZ);
        return vStart + vProjection;
    }
    //
    // Unchanged
    //
    return vEndViewport;
}

}