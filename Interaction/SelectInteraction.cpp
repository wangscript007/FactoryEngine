
#include <Graph/PointNode.h>
#include <Processing/ModelEditor.h>
#include <Interaction/SelectInteraction.h>

namespace ftr {
    
SelectInteraction::SelectInteraction(ModelEditor& modelEditor, const Viewport& viewport)
:mModelEditor(modelEditor)
,mActive(false)
{
}

SelectInteraction::~SelectInteraction()
{
 
}

#pragma mark Instance

void SelectInteraction::Render(Layer& layer)
{
    Node::Render(layer);
}

void SelectInteraction::Begin()
{
    if (!mActive) {
        mActive = true;
        mEnd = glm::vec3();
        mStart = glm::vec3();
    }
    mModelEditor.StartSelecting(ftr::Node::kGroup);
}

void SelectInteraction::Step()
{
}

void SelectInteraction::Finish()
{
    mActive = false;
}



}
