

#pragma once

namespace ftr {

enum Axis { kAxisX, kAxisY, kAxisZ };

struct Box
{
    glm::vec3 mCenter;
    glm::vec3 mHalfDimention;
    
    Box() : mCenter(glm::vec3()), mHalfDimention(glm::vec3()) {};
    Box(glm::vec3 center, glm::vec3 halfDimension) : mCenter(center), mHalfDimention(halfDimension) {};
    bool Contains(const glm::vec3& vec) const;
    bool Intersects(const Box& other) const;
};

inline bool Box::Contains(const glm::vec3& vec) const
{
    if (vec.x <= mCenter.x - mHalfDimention.x) return false;
    if (vec.x > mCenter.x + mHalfDimention.x) return false;
    
    if (vec.y <= mCenter.y - mHalfDimention.y) return false;
    if (vec.y > mCenter.y + mHalfDimention.y) return false;
    
    if (vec.z <= mCenter.z - mHalfDimention.z) return false;
    if (vec.z > mCenter.z + mHalfDimention.z) return false;
        
    return true;
}

inline bool Box::Intersects(const Box& other) const
{
    if (mCenter.x + mHalfDimention.x <= other.mCenter.x - other.mHalfDimention.x) return false;
    if (mCenter.x - mHalfDimention.x > other.mCenter.x + other.mHalfDimention.x) return false;
    
    if (mCenter.y + mHalfDimention.y <= other.mCenter.y - other.mHalfDimention.y) return false;
    if (mCenter.y - mHalfDimention.y > other.mCenter.y + other.mHalfDimention.y) return false;
    
    if (mCenter.z + mHalfDimention.z <= other.mCenter.z - other.mHalfDimention.z) return false;
    if (mCenter.z - mHalfDimention.z > other.mCenter.z + other.mHalfDimention.z) return false;

    return true; // boxes overlap

}

struct Sphere
{
    glm::vec3 mCenter;
    float mRadius;
    Sphere(glm::vec3 center, float radius) : mCenter(center), mRadius(radius) {};
    bool Intersects(const Box& box) const;
    bool Containts(const glm::vec3& vec) const;
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
    return ftr::Box(mCenter, glm::vec3(mRadius, mRadius, mRadius));
}

inline bool Sphere::Containts(const glm::vec3& vec) const
{
    return  glm::length(mCenter - vec) < mRadius;
}


struct Rectangle3
{
    glm::vec3 mOrigin;
    glm::vec3 mA;
    glm::vec3 mB;
};
    
}


