

#pragma once

namespace Factory {

enum Axis { kAxisX, kAxisY, kAxisZ };

struct Box
{
    Vec3 m_vCenter;
    Vec3 m_vHalfDimention;
    
    Box() : m_vCenter(Vec3()), m_vHalfDimention(Vec3()) {};
    Box(Vec3 vCenter, Vec3 vHalfDimension) : m_vCenter(vCenter), m_vHalfDimention(vHalfDimension) {};
    bool Contains(const Vec3& vec) const;
    bool Intersects(const Box& other) const;
};

inline bool Box::Contains(const Vec3& vec) const
{
    if (vec.m_fX <= m_vCenter.m_fX - m_vHalfDimention.m_fX) return false;
    if (vec.m_fX > m_vCenter.m_fX + m_vHalfDimention.m_fX) return false;
    
    if (vec.m_fY <= m_vCenter.m_fY - m_vHalfDimention.m_fY) return false;
    if (vec.m_fY > m_vCenter.m_fY + m_vHalfDimention.m_fY) return false;
    
    if (vec.m_fZ <= m_vCenter.m_fZ - m_vHalfDimention.m_fZ) return false;
    if (vec.m_fZ > m_vCenter.m_fZ + m_vHalfDimention.m_fZ) return false;
        
    return true;
}

inline bool Box::Intersects(const Box& other) const
{
    if (m_vCenter.m_fX + m_vHalfDimention.m_fX <= other.m_vCenter.m_fX - other.m_vHalfDimention.m_fX) return false;
    if (m_vCenter.m_fX - m_vHalfDimention.m_fX > other.m_vCenter.m_fX + other.m_vHalfDimention.m_fX) return false;
    
    if (m_vCenter.m_fY + m_vHalfDimention.m_fY <= other.m_vCenter.m_fY - other.m_vHalfDimention.m_fY) return false;
    if (m_vCenter.m_fY - m_vHalfDimention.m_fY > other.m_vCenter.m_fY + other.m_vHalfDimention.m_fY) return false;
    
    if (m_vCenter.m_fZ + m_vHalfDimention.m_fZ <= other.m_vCenter.m_fZ - other.m_vHalfDimention.m_fZ) return false;
    if (m_vCenter.m_fZ - m_vHalfDimention.m_fZ > other.m_vCenter.m_fZ + other.m_vHalfDimention.m_fZ) return false;

    return true; // boxes overlap

}



struct Sphere
{
    Vec3 m_vCenter;
    float m_fRadius;
    Sphere(Vec3 vCenter, float fRadius) : m_vCenter(vCenter), m_fRadius(fRadius) {};
    bool Intersects(const Box& box) const;
    bool Containts(const Vec3& vec) const;
    Box Box() const;
};

inline bool Sphere::Intersects(const struct Box& box) const
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

inline Box Sphere::Box() const
{
    return Factory::Box(m_vCenter, Vec3(m_fRadius, m_fRadius, m_fRadius));
}

inline bool Sphere::Containts(const Vec3& vec) const
{
    return (m_vCenter - vec).Length() < m_fRadius;
}


struct Rectangle3
{
    Vec3 m_vOrigin;
    Vec3 m_vA;
    Vec3 m_vB;
};
    
}


