
#include <Model/FTPoint.h>
#include <Main/FTLog.h>

const float FTPoint::c_fR = 5.0f;


FTPoint::FTPoint()
    :m_pOctreeLeaf(NULL)
    ,m_bIsActive(false)
{
    
}

FTPoint::FTPoint(O5Vec3 vOrigin)
:m_vOrigin(vOrigin)
{
    FTPoint();
}

void FTPoint::Transform(const O5Mat4& m4Transformation)
{
    m_vOrigin *= m4Transformation;
    FTLog(kFTLogModel, "[%f, %f, %f]", m_vOrigin.m_fX, m_vOrigin.m_fY, m_vOrigin.m_fZ);
}

#pragma mark - Instance

//
// Renders cicle at point position
//
void FTPoint::Render()
{
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(c_fR);
    
    glBegin(GL_POINTS);
    {
        if (m_bIsActive) {
            glColor3f(0.5f, 0.207, 0.031f);
        } else {
            glColor3f(0.95f, 0.207, 0.031f);
        }
        
        glVertex3f(m_vOrigin.m_fX, m_vOrigin.m_fY, m_vOrigin.m_fZ);
    }
    glEnd();
}

