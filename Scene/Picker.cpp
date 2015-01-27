
#include <Scene/Picker.h>
#include <Graph/Node.h>
#include <Graph/FaceNode.h>
#include <Processing/ModelTree.h>
#include <Processing/ColorPickingMapper.h>
#include <Scene/SceneRenderer.h>
#include <Render/Layer.h>


namespace ftr {
    
Picker::Picker(ModelTree& modelTree, SceneRenderer& sceneRenderer, Layer& layer)
    : mModelTree(modelTree),
    mSceneRenderer(sceneRenderer),
    mLayer(layer),
    mIsOn(false)
    
{
    mColorPickingMapper = new ColorPickingMapper(mModelTree);
    
    float k = 10000;
    mPadPolygon.AddPoint(glm::vec3(k,0,k));
    mPadPolygon.AddPoint(glm::vec3(k,0,-k));
    mPadPolygon.AddPoint(glm::vec3(-k,0,-k));
    mPadPolygon.AddPoint(glm::vec3(-k,0,k));
    mPadPolygon.Triangulate();

}
    
Picker::~Picker()
{
    FT_DELETE(mColorPickingMapper);
}

    
Node* Picker::PickNode(const glm::vec2& atPoint) const
{
    mLayer.Cleanup();
    mSceneRenderer.RenderMarkingContent(mLayer);
    const glm::vec4 color = mSceneRenderer.colorMarkingFramebuffer()->ColorAtPoint(atPoint);
    return mColorPickingMapper->NodeForColor(glm::vec3(color.x, color.y, color.z));
}
    
glm::vec3 Picker::PickSceneCoordinates(const glm::vec2& atPoint) const
{
    Node* node = PickNode(atPoint);
    glm::vec3 point;
    const Viewport& viewport = mSceneRenderer.camera().viewport();
    Segment ray = viewport.RayAtPoint(atPoint);
    if (node) {
        assert(node->Type() == Node::kFace);
        FaceNode* face = reinterpret_cast<FaceNode*>(node);
        point = face->IntersectionPoint(ray);
    } else {
        point = mPadPolygon.IntersectionPoint(ray);
    }
    return point;
}
    
void Picker::setOn(bool on)
{
    if (mIsOn == on) return;
    mIsOn = on;
    if (mIsOn) {
        mColorPickingMapper->MapPickingColors(Node::kFace);
    }
    
}

    
}