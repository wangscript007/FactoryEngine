
#include <Interaction/InteractionAssistant.h>
#include <Math/Geometry.h>
#include <Utils/Picker.h>

namespace ftr {

const float InteractionAssistant::kSensitivity = 20.0f;

Vec3 InteractionAssistant::AxisAlignedViewport(const Vec3& startScene, const Vec3& endViewport, const Camera::Parameters& cameraParameters) const
{
    Vec3 start = Picker::Viewport(startScene, cameraParameters);
    Vec3 current = endViewport - start;
    Vec3 axisX = Picker::Viewport(startScene, cameraParameters);
    Vec3 axisY = Picker::Viewport(startScene, cameraParameters);
    Vec3 axisZ = Picker::Viewport(startScene, cameraParameters);

    Vec3 perp;
    // Finding perpendiculars to axis aligned vectors
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
    return endViewport;
}

}