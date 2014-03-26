
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
    glm::vec3 SurfaceNormal() const;
    
    void RotateToSurfaceNormal(const glm::vec3& targedNormal);
    void DebugPrint() const;
    void DebugPrintTriangles() const;
    
private:
    glm::mat4 RotationToSurfaceNormal(const glm::vec3& targedNormal);
    void TransformTriangles(const glm::mat4& tranformation);
    
    
    
    std::vector<Triangle*> mTriangles;
    
    
    glm::vec3 XYZClosestNormal() const;
    
    Polyline mPolyline;
};

}