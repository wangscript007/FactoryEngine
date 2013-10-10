
#include <Interaction/RectangleInteraction.h>
#include <Model/ModelEditor.h>

namespace ftr {

RectangleInteraction::RectangleInteraction(ModelEditor& ModelEditor)
    :mModelEditor(ModelEditor)
    ,mActive(false)
{}

void RectangleInteraction::Render()
{
    return;
    /*
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    GLfloat vertices[] =
    {
        mOrigin.x,                  mOrigin.y,             mOrigin.z,
        mOrigin.x + mSize.x,   mOrigin.y,             mOrigin.z,
        mOrigin.x + mSize.x ,  mOrigin.y,             mOrigin.z + mSize.z,
        mOrigin.x,                  mOrigin.y,             mOrigin.z + mSize.z
    };
    static GLfloat normals[] = {0,1,0,  0,1,0,  0,1,0,  0,1,0};            
    static GLfloat colors[] = {1,0,0,  0.5,0,0,  1,0,0,  0.5,0,0};
    static GLubyte indices[] = {3,2,1,0};
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    */
}

#pragma mark Instance

void RectangleInteraction::Begin()
{
    mActive = true;
    mModelEditor.SelectedNode()->AddNode(this);
    mRect3.mA = glm::vec3();
}

void RectangleInteraction::End()
{
    if (mActive) {
        mActive = false;
        //mModelEditor.CreateRectangle(mOrigin, mSize);
        mModelEditor.SelectedNode()->RemoveNode(this);
    }
}

void RectangleInteraction::setOrigin(const glm::vec3& origin)
{
    mRect3.mOrigin = origin;
}

void RectangleInteraction::setCurrent(const glm::vec3& current)
{
    //
    //  If both origin and current are on the same face crade parralel to face
    //  else ignore minimum axis
    mRect3.mA = current;
    glm::vec3 vDiff = mRect3.mOrigin - mRect3.mA;
    const float x = abs(vDiff.x);
    const float y = abs(vDiff.y);
    const float z = abs(vDiff.z);
    Axis eAxis = x < y ? (x < z ? kAxisX : (y < z ? kAxisY : kAxisZ)) : (y < z ? kAxisY : (x < z ? kAxisX : kAxisZ));
    switch (eAxis) {
        case kAxisX : {
            
        } break;
        case kAxisY : {
            
        } break;
        case kAxisZ : {
            
        } break;
    }
}
    
}

