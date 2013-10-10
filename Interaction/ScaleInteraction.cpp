
#include <Interaction/ScaleInteraction.h>
#include <Model/ModelEditor.h>

namespace ftr {


ScaleInteraction::ScaleInteraction(ModelEditor& ModelEditor)
:mModelEditor(ModelEditor)
,mActive(false)
{}

void ScaleInteraction::Render()
{
    
}

#pragma mark Instance

void ScaleInteraction::setStart(glm::vec3 start)
{
    mStart = start;
}

void ScaleInteraction::setEnd(glm::vec3 end)
{
    mEnd = end;
    assert(mModelEditor.SelectedNode()->Type() == Node::kLine);
    glm::vec3 scale = mEnd - mStart;
    scale.x = std::min(std::max(scale.x, 1.0f), 2.0f);
    scale.y = std::min(std::max(scale.y, 1.0f), 2.0f);
    scale.z = std::min(std::max(scale.z, 1.0f), 2.0f);
    scale = glm::vec3(0.99f, 1.001f, 1.001f);
//    mModelEditor.SelectedNode()->Transform(Transformation::Scale(scale));
    mStart = end;
}
    
}

