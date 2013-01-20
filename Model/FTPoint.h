
#pragma once

#include <Model/FTModel.h>
#include <Managers/FTOctree.h>

class FTPoint : public FTModel
{
public:
    static const float c_fR;
    
    FTPoint();
    virtual ~FTPoint() {}
    
    O5Vec3 m_vOrigin;
    
    virtual void Render();
    virtual NodeType Type() const { return kPoint; }
    FTOctree::Leaf* OctreeLeaf() const { return m_pOctreeLeaf; }
    void SetOctreeLeaf(FTOctree::Leaf* pLeaf) { m_pOctreeLeaf = pLeaf; }
    void SetActive(bool bActive) { m_bIsActive = bActive; }
    bool Active() const { return m_bIsActive; }
    
    
private:
    FTOctree::Leaf* m_pOctreeLeaf;
    bool m_bIsActive;
};

