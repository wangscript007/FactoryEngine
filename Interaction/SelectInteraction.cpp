
#include <Graph/PointNode.h>
#include <Processing/ModelEditor.h>
#include <Interaction/SelectInteraction.h>
#include <Scene/Picker.h>

namespace ftr {
    
SelectInteraction::SelectInteraction(ModelEditor& modelEditor, const Viewport& viewport)
    :mModelEditor(modelEditor),
    mSelectedNode(NULL)
{

}

SelectInteraction::~SelectInteraction()
{
 
}

#pragma mark Instance
    
void SelectInteraction::Select(const glm::vec2& point)
{
    Node* node = mModelEditor.picker()->Pick(point);
    if (node && node != mSelectedNode) {
        if (mSelectedNode) {
            mSelectedNode->setSelected(false);
        }
        mSelectedNode = node;
        mSelectedNode->setSelected(true);
    }
}
    
void SelectInteraction::TurnOn()
{
    mModelEditor.picker()->setOn(true);
}
    
void SelectInteraction::TurnOff()
{
    mModelEditor.picker()->setOn(false);
}
    
void SelectInteraction::Render(Layer& layer)
{
    Node::Render(layer);
}
    
}
