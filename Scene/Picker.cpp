
#include <Scene/Picker.h>
#include <Graph/Node.h>
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
}
    
Picker::~Picker()
{
     FT_DELETE(mColorPickingMapper);
}

Node* Picker::Pick(const glm::vec2& atPoint)
{
    mSceneRenderer.RenderMarkingContent(mLayer);
    const glm::vec4 color = mSceneRenderer.colorMarkingFramebuffer()->ColorAtPoint(atPoint);
    return mColorPickingMapper->NodeForColor(glm::vec3(color.x, color.y, color.z));
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