

#pragma once

namespace ftr {

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
    if (vec.mX <= m_vCenter.mX - m_vHalfDimention.mX) return false;
    if (vec.mX > m_vCenter.mX + m_vHalfDimention.mX) return false;
    
    if (vec.mY <= m_vCenter.mY - m_vHalfDimention.mY) return false;
    if (vec.mY > m_vCenter.mY + m_vHalfDimention.mY) return false;
    
    if (vec.mZ <= m_vCenter.mZ - m_vHalfDimention.mZ) return false;
    if (vec.mZ > m_vCenter.mZ + m_vHalfDimention.mZ) return false;
        
    return true;
}

inline bool Box::Intersects(const Box& other) const
{
    if (m_vCenter.mX + m_vHalfDimention.mX <= other.m_vCenter.mX - other.m_vHalfDimention.mX) return false;
    if (m_vCenter.mX - m_vHalfDimention.mX > other.m_vCenter.mX + other.m_vHalfDimention.mX) return false;
    
    if (m_vCenter.mY + m_vHalfDimention.mY <= other.m_vCenter.mY - other.m_vHalfDimention.mY) return false;
    if (m_vCenter.mY - m_vHalfDimention.mY > other.m_vCenter.mY + other.m_vHalfDimention.mY) return false;
    
    if (m_vCenter.mZ + m_vHalfDimention.mZ <= other.m_vCenter.mZ - other.m_vHalfDimention.mZ) return false;
    if (m_vCenter.mZ - m_vHalfDimention.mZ > other.m_vCenter.mZ + other.m_vHalfDimention.mZ) return false;

    return true; // boxes overlap

}



struct Sphere
{
    Vec3 m_vCenter;
    float mRadius;
    Sphere(Vec3 vCenter, float fRadius) : m_vCenter(vCenter), mRadius(fRadius) {};
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
    return ftr::Box(m_vCenter, Vec3(mRadius, mRadius, mRadius));
}

inline bool Sphere::Containts(const Vec3& vec) const
{
    return (m_vCenter - vec).Length() < mRadius;
}


struct Rectangle3
{
    Vec3 m_vOrigin;
    Vec3 m_vA;
    Vec3 m_vB;
};
    
}


