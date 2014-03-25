
#pragma once

#include <Geometry/GeometryPrimitives.h>
#include <External/poly2tri/poly2tri.h>
#include <Geometry/Polyline.h>
#include <Geometry/Triangle.h>


namespace ftr {

class Polygon : public Polyline
{
public:
    Polygon() {};
    ~Polygon() {};
    const std::vector<Triangle*>& GetTriangles() const { return mTriangles; }
    
    void Triangulate();
    
    
private:
    glm::mat4 RotationToSurfaceNormal(const glm::vec3& targedNormal);
    void Transform(const glm::mat4& tranformation);
    void TransformTriangles(const glm::mat4& tranformation);
    
    std::vector<Triangle*> mTriangles;
    
    glm::vec3 SurfaceNormal() const;
    glm::vec3 XYZClosestNormal() const;
    
    Polyline mPolyline;
};

}