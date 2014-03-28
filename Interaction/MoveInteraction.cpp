
#include <Interaction/MoveInteraction.h>
#include <Processing/ModelEditor.h>

namespace ftr {

MoveInteraction::MoveInteraction(ModelEditor& ModelEditor)
:mModelEditor(ModelEditor)
,mActive(false)
{}

void MoveInteraction::Render()
{
    
}

#pragma mark Instance

void MoveInteraction::setStart(glm::vec3 start)
{
    mStart = start;
}

void MoveInteraction::setEnd(glm::vec3 end)
{
    mEnd = end;
    assert(mModelEditor.SelectedNode()->Type() == Node::kLine);
//    mModelEditor.SelectedNode()->Transform(Transformation::Translate(mEnd - mStart));
    mStart = end;
}

}
