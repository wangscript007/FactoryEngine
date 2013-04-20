
#include <Interaction/InteractionAssistant.h>
#include <Math/Utils.h>
#include <Math/Geometry.h>

namespace ftr {

const float InteractionAssistant::kSensitivity = 20.0f;

Vec3 InteractionAssistant::AxisAlignedViewport(const Vec3& startScene, const Vec3& endViewport) const
{
    Vec3 start = Utils::Viewport(startScene);
    Vec3 current = endViewport - start;
    Vec3 axisX = Utils::Viewport(Vec3::X);
    Vec3 axisY = Utils::Viewport(Vec3::Y);
    Vec3 axisZ = Utils::Viewport(Vec3::Z);
    Vec3 perp;
    //
    // Finding perpendiculars to axis aligned vectors
    //
    float fLength = current.Length();
    perp.mX = tanf(axisX.Angle(current)) * fLength;
    perp.mY = tanf(axisY.Angle(current)) * fLength;
    perp.mZ = tanf(axisZ.Angle(current)) * fLength;
    
    float min = perp.Min();
    
    if (min < kSensitivity) {
        Vec3 projection;
        if      (min == perp.mX) projection = Vec3::X * current.ProjectionIn(axisX);
        else if (min == perp.mY) projection = Vec3::X * current.ProjectionIn(axisY);
        else if (min == perp.mZ) projection = Vec3::X * current.ProjectionIn(axisZ);
        return start + projection;
    }
    //
    // Unchanged
    //
    return endViewport;
}

}