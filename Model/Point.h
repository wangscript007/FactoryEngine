
#pragma once

#include <Model/Model.h>
#include <Managers/Octree.h>

namespace ftr {

class Point : public Model
{
public:
    static const float c_fR;
    Point();
    Point(Vec3 vOrigin);
    virtual ~Point() {}
    
    Vec3 m_vOrigin;
    
    virtual void Render();
    virtual NodeType Type() const { return kPoint; }
    virtual void Transform(const Mat4& m4Transformation);
    Octree::Leaf* OctreeLeaf() const { return m_pOctreeLeaf; }
    void SetOctreeLeaf(Octree::Leaf* pLeaf) { m_pOctreeLeaf = pLeaf; }
    void SetActive(bool bActive) { m_bIsActive = bActive; }
    bool Active() const { return m_bIsActive; }
    
    
private:
    Octree::Leaf* m_pOctreeLeaf;
    bool m_bIsActive;
};
    
}

