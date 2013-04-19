
#include <Interaction/InteractionAssistant.h>
#include <Math/Utils.h>
#include <Math/Geometry.h>

namespace ftr {

const float InteractionAssistant::c_fSensitivity = 20.0f;

Vec3 InteractionAssistant::AxisAlignedViewport(const Vec3& startScene,
                                                   const Vec3& endViewport) const
{
    Vec3 start = Utils::Viewport(startScene);
    Vec3 vCurrent = endViewport - start;
    Vec3 axisX = Utils::Viewport(Vec3::X);
    Vec3 axisY = Utils::Viewport(Vec3::Y);
    Vec3 axisZ = Utils::Viewport(Vec3::Z);
    Vec3 perp;
    //
    // Finding perpendiculars to axis aligned vectors
    //
    float fLength = vCurrent.Length();
    perp.mX = tanf(axisX.Angle(vCurrent)) * fLength;
    perp.mY = tanf(axisY.Angle(vCurrent)) * fLength;
    perp.mZ = tanf(axisZ.Angle(vCurrent)) * fLength;
    
    float min = perp.Min();
    
    if (min < c_fSensitivity) {
        Vec3 projection;
        if      (min == perp.mX) projection = Vec3::X * vCurrent.ProjectionIn(axisX);
        else if (min == perp.mY) projection = Vec3::X * vCurrent.ProjectionIn(axisY);
        else if (min == perp.mZ) projection = Vec3::X * vCurrent.ProjectionIn(axisZ);
        return start + projection;
    }
    //
    // Unchanged
    //
    return endViewport;
}

}