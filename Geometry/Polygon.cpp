
#include <Geometry/Polygon.h>
#include <Geometry/Vector.h>
#include <Utils/Description.h>
#include <Geometry/Constants.h>

namespace ftr {
    
Polygon::~Polygon()
{
    FT_DELETE_VECTOR(mTriangles);
}
    
void Polygon::Triangulate()
{
    FT_DELETE_VECTOR(mTriangles);
    
    glm::vec3 closestNormal = XYZClosestNormal();
    bool isXYZAlligned = Vector::IsParallel(SurfaceNormal(), closestNormal);
    
    Polygon rotatedPolygon = *this;
    glm::mat4 rotationMatrix;
    
    if (!isXYZAlligned) {
        rotationMatrix = RotationToSurfaceNormal(closestNormal);
        rotatedPolygon.Transform(rotationMatrix);
    }
    
    float xyzOffset = 0.0f;
    int dimensionsToUse[2];
    int dim = 0;
    for (int i = 0; i < kDimensionsCount; i++) {
        if (closestNormal[i] == 0) {
            dimensionsToUse[dim] = i;
            dim++;
        } else {
            xyzOffset = rotatedPolygon.mPoints[0][i];
        }
    }
    
    std::vector<p2t::Point*> polyline;
    for (auto &polygonPoint : mPoints) {
        float x = polygonPoint[dimensionsToUse[0]];
        float y = polygonPoint[dimensionsToUse[1]];
        std::cout << "x: " << x << " y: " << y << std::endl;
        polyline.push_back(new p2t::Point(x, y));
    }
    
    p2t::CDT cdt(polyline);
    cdt.Triangulate();
    std::vector<p2t::Triangle*> triangles = cdt.GetTriangles();
    
    for (auto &triangle : triangles)
    {
        glm::vec3 points[3];
        
        for(int pi = 0; pi < kDimensionsCount; pi++)
        {
            int dim = 0;
            for (int di = 0; di < kDimensionsCount; ++di)
            {
                if (closestNormal[di] == 0) {
                    if (dim == 0) {
                        points[pi][di] = triangle->GetPoint(pi)->x;
                    } else {
                        points[pi][di] = triangle->GetPoint(pi)->y;
                    }
                    dim++;
                } else {
                    points[pi][di] = xyzOffset;
                }
            }
        }
        mTriangles.push_back(new Triangle(points[0], points[1], points[2]));
    }
    
    if (!isXYZAlligned) {
        TransformTriangles(glm::inverse(rotationMatrix));
    }
    
    FT_DELETE_VECTOR(polyline);
}
    
    
void Polygon::TransformTriangles(const glm::mat4& tranformation)
{
    for (int i = 0; i < mTriangles.size(); ++i) {
        mTriangles[i]->Transform(tranformation);
    }
}
    
    
void Polygon::RotateToSurfaceNormal(const glm::vec3& targedNormal)
{
    Transform(RotationToSurfaceNormal(targedNormal));
}
    
    
glm::mat4 Polygon::RotationToSurfaceNormal(const glm::vec3& targedNormal)
{
    glm::vec3 surfaceNormal = SurfaceNormal();
    glm::vec3 rotationAxis  = glm::normalize(glm::cross(targedNormal, surfaceNormal));
    float rotationAngle     = glm::angle(targedNormal, surfaceNormal);
    
    return glm::rotate(rotationAngle, rotationAxis);
}
    
    
glm::vec3 Polygon::XYZClosestNormal() const
{
    return Vector::XYZClosestAxis(SurfaceNormal());
}
    
    
glm::vec3 Polygon::SurfaceNormal() const
{
    assert(mPoints.size() > 2);
    Triangle triangle(mPoints[0],
                      mPoints[1],
                      mPoints[2]);
    glm::vec3 normal = triangle.SurfaceNormal();
    return normal;
}
    
    
void Polygon::DebugPrint() const
{
    std::cout << "Polygon \n";
    for (int i = 0; i < mPoints.size(); ++i) {
        std::cout << Description::Described(mPoints[i]) << " ";
    }
}
    
void Polygon::DebugPrintTriangles() const
{
    std::cout << "Triangles of polygon \n";
    std::vector<Triangle*> triangles = GetTriangles();
    for (int i = 0; i < triangles.size(); ++i) {
        std::cout << triangles[i]->Description();
    }
}
    
}
