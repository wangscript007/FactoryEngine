

#pragma once

struct FTBox
{
    O5Vec3 m_vCenter;
    O5Vec3 m_vHalfDimention;
    
    FTBox() : m_vCenter(O5Vec3()), m_vHalfDimention(O5Vec3()) {};
    FTBox(O5Vec3 vCenter, O5Vec3 vHalfDimension) : m_vCenter(vCenter), m_vHalfDimention(vHalfDimension) {};
    bool Containts(O5Vec3& vec);
    bool Intersects(FTBox& other);
};

inline bool FTBox::Containts(O5Vec3 &vec)
{
    if (vec.m_fX < m_vCenter.m_fX - m_vHalfDimention.m_fX) return false;
    if (vec.m_fX > m_vCenter.m_fX + m_vHalfDimention.m_fX) return false;
    
    if (vec.m_fY < m_vCenter.m_fY - m_vHalfDimention.m_fY) return false;
    if (vec.m_fY > m_vCenter.m_fY + m_vHalfDimention.m_fY) return false;
    
    if (vec.m_fZ < m_vCenter.m_fZ - m_vHalfDimention.m_fZ) return false;
    if (vec.m_fZ > m_vCenter.m_fZ + m_vHalfDimention.m_fZ) return false;
        
    return true;
}

inline bool FTBox::Intersects(FTBox& other)
{
    if (m_vCenter.m_fX + m_vHalfDimention.m_fX > other.m_vCenter.m_fX - other.m_vHalfDimention.m_fX) return false;
    if (m_vCenter.m_fX - m_vHalfDimention.m_fX > other.m_vCenter.m_fX + other.m_vHalfDimention.m_fX) return false;
    
    if (m_vCenter.m_fY + m_vHalfDimention.m_fY > other.m_vCenter.m_fY - other.m_vHalfDimention.m_fY) return false;
    if (m_vCenter.m_fY - m_vHalfDimention.m_fY > other.m_vCenter.m_fY + other.m_vHalfDimention.m_fY) return false;
    
    if (m_vCenter.m_fZ + m_vHalfDimention.m_fZ > other.m_vCenter.m_fZ - other.m_vHalfDimention.m_fZ) return false;
    if (m_vCenter.m_fZ - m_vHalfDimention.m_fZ > other.m_vCenter.m_fZ + other.m_vHalfDimention.m_fZ) return false;

    return true; // boxes overlap

}


