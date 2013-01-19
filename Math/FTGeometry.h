

#pragma once

struct FTBox
{
    O5Vec3 m_vCenter;
    O5Vec3 m_vHalfDimention;
    
    FTBox() : m_vCenter(O5Vec3()), m_vHalfDimention(O5Vec3()) {};
    FTBox(O5Vec3 vCenter, O5Vec3 vHalfDimension) : m_vCenter(vCenter), m_vHalfDimention(vHalfDimension) {};
    bool Contains(const O5Vec3& vec) const;
    bool Intersects(const FTBox& other) const;
};

inline bool FTBox::Contains(const O5Vec3& vec) const
{
    if (vec.m_fX <= m_vCenter.m_fX - m_vHalfDimention.m_fX) return false;
    if (vec.m_fX > m_vCenter.m_fX + m_vHalfDimention.m_fX) return false;
    
    if (vec.m_fY <= m_vCenter.m_fY - m_vHalfDimention.m_fY) return false;
    if (vec.m_fY > m_vCenter.m_fY + m_vHalfDimention.m_fY) return false;
    
    if (vec.m_fZ <= m_vCenter.m_fZ - m_vHalfDimention.m_fZ) return false;
    if (vec.m_fZ > m_vCenter.m_fZ + m_vHalfDimention.m_fZ) return false;
        
    return true;
}

inline bool FTBox::Intersects(const FTBox& other) const
{
    if (m_vCenter.m_fX + m_vHalfDimention.m_fX <= other.m_vCenter.m_fX - other.m_vHalfDimention.m_fX) return false;
    if (m_vCenter.m_fX - m_vHalfDimention.m_fX > other.m_vCenter.m_fX + other.m_vHalfDimention.m_fX) return false;
    
    if (m_vCenter.m_fY + m_vHalfDimention.m_fY <= other.m_vCenter.m_fY - other.m_vHalfDimention.m_fY) return false;
    if (m_vCenter.m_fY - m_vHalfDimention.m_fY > other.m_vCenter.m_fY + other.m_vHalfDimention.m_fY) return false;
    
    if (m_vCenter.m_fZ + m_vHalfDimention.m_fZ <= other.m_vCenter.m_fZ - other.m_vHalfDimention.m_fZ) return false;
    if (m_vCenter.m_fZ - m_vHalfDimention.m_fZ > other.m_vCenter.m_fZ + other.m_vHalfDimention.m_fZ) return false;

    return true; // boxes overlap

}



struct FTSphere
{
    O5Vec3 m_vCenter;
    float m_fRadius;
    FTSphere(O5Vec3 vCenter, float fRadius) : m_vCenter(vCenter), m_fRadius(fRadius) {};
    bool Intersects(const FTBox& box) const;
    bool Containts(const O5Vec3& vec) const;
    FTBox Box() const;
};

inline bool FTSphere::Intersects(const FTBox& box) const
{
    /*
    closest.x = box.leftx;
    elseif(sphere.center.x > box.rightx)
    closest.x = box.rightx;
    else
        closest.x = sphere.center.x;
    */
    return false;
}

inline FTBox FTSphere::Box() const
{
    return FTBox(m_vCenter, O5Vec3(m_fRadius, m_fRadius, m_fRadius));
}

inline bool FTSphere::Containts(const O5Vec3& vec) const
{
    return (m_vCenter - vec).Length() < m_fRadius;
}


