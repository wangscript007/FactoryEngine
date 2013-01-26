
#include <Model/FTLine.h>

FTLine::FTLine(FTPoint* pStartPoint, FTPoint* pEndPoint)
    :m_pStartPoint(pStartPoint)
    ,m_pEndPoint(pEndPoint)
{}

#pragma mark - Instance


void FTLine::Render()
{
    FTNode::Render();
    if (m_pStartPoint) {
        m_pStartPoint->Render();
    }
    if (m_pEndPoint) {
        m_pEndPoint->Render();
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);
    //
    // grind
    //
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    {
        O5Vec3 startVec = m_pStartPoint->m_vOrigin;
        O5Vec3 endVec = m_pEndPoint->m_vOrigin;
        glVertex3d(startVec.m_fX,
                   startVec.m_fY,
                   startVec.m_fZ);
        glVertex3d(endVec.m_fX,
                   endVec.m_fY,
                   endVec.m_fZ);
    }
    glEnd();
}



