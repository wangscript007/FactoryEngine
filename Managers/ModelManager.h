
#pragma once

#include <Model/ModelFactory.h>
#include <Model/Group.h>
#include <Managers/ModelTreeManager.h>

namespace Factory {

class ModelManager
{
public:
                            ModelManager();
                            ~ModelManager();
    
    ModelFactory*         ModelFactory() const { return m_pModelFactory; }
    ModelTreeManager*     ModelTreeManager() const { return  m_pModelTreeManager; }
    Point*                NearestPointToCenterInSphere(const Sphere& sSphere) const;
    void                    UpdateNode(Node* pNode) { m_pModelTreeManager->UpdateNode(pNode); }
    void                    RemoveNode(Node* pNode) { m_pModelTreeManager->RemoveNode(pNode); }
    void                    Select(Node* pNode);
    Node*                 SelectedNode() const { return m_pSelectedNode; }
    unsigned long           Size() { return m_pModelTreeManager->Size(); }
    //
    // Creating
    //
    Face*                 CreateRectangle(const O5Vec3& vOrigin, const O5Vec3& vSize) const;
    Face*                 CreateFace(O5Vec3 vOrigin, Face::FaceType eType);
    Point*                CreatePoint(O5Vec3 vOrigin);
    Line*                 CreateLine(Point* pStartPoint, Point* pEndPoint);
    
private:
    ModelFactory*         m_pModelFactory;
    ModelTreeManager*     m_pModelTreeManager;
    Group*                m_pRootGroup;
    Node*                 m_pSelectedNode;
};
    
}

