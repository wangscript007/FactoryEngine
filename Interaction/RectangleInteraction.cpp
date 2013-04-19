
#include <Interaction/RectangleInteraction.h>
#include <Managers/ModelManager.h>

namespace ftr {

RectangleInteraction::RectangleInteraction(ModelManager& rModelManager)
    :m_rModelManager(rModelManager)
    ,m_bActive(false)
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
        m_vOrigin.mX,                  m_vOrigin.mY,             m_vOrigin.mZ,
        m_vOrigin.mX + m_vSize.mX,   m_vOrigin.mY,             m_vOrigin.mZ,
        m_vOrigin.mX + m_vSize.mX ,  m_vOrigin.mY,             m_vOrigin.mZ + m_vSize.mZ,
        m_vOrigin.mX,                  m_vOrigin.mY,             m_vOrigin.mZ + m_vSize.mZ
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
    m_bActive = true;
    m_rModelManager.SelectedNode()->AddNode(this);
    m_sRect3.m_vA = Vec3();
}

void RectangleInteraction::End()
{
    if (m_bActive) {
        m_bActive = false;
        //m_rModelManager.CreateRectangle(m_vOrigin, m_vSize);
        m_rModelManager.SelectedNode()->RemoveNode(this);
    }
}

void RectangleInteraction::SetOrigin(const Vec3& vOrigin)
{
    m_sRect3.m_vOrigin = vOrigin;
}

void RectangleInteraction::SetCurrent(const Vec3& vCurrent)
{
    //
    //  If both origin and current are on the same face crade parralel to face
    //  else ignore minimum axis
    m_sRect3.m_vA = vCurrent;
    Vec3 vDiff = m_sRect3.m_vOrigin - m_sRect3.m_vA;
    const float x = abs(vDiff.mX);
    const float y = abs(vDiff.mY);
    const float z = abs(vDiff.mZ);
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

