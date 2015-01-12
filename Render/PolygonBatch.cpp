
#include <Render/PolygonBatch.h>
#include <Shading/ShadingInterface.h>

namespace ftr {
 
PolygonBatch::PolygonBatch() :
    mTrianglesCount(0)
{

}
    
void PolygonBatch::CreateRenderData(ShadingInterface& shadingInterface)
{
    if (mRenderData) return;
    Validate();
    
    mTrianglesCount = 0;
    for (auto& it : mPrimitives) {
        PolygonPrimitive* poly = reinterpret_cast<PolygonPrimitive*>(it);
        poly->Triangulate();
        mTrianglesCount += poly->GetTriangles().size();
    }
    
    glm::vec4* data = reinterpret_cast<glm::vec4*>(new char[sizeof(glm::vec4)*3*mTrianglesCount*4]);
    
    glm::vec4* vertices         = data;
    glm::vec4* normals          = data + (3 * mTrianglesCount);
    glm::vec4* colors           = data + (3 * mTrianglesCount * 2);
    glm::vec4* pickingColors    = data + (3 * mTrianglesCount * 3);
    
    int ti = 0;
    for (auto& it : mPrimitives) {
        PolygonPrimitive* poly = reinterpret_cast<PolygonPrimitive*>(it);
        const std::vector<Triangle*>& triangles = poly->GetTriangles();
        glm::vec3 normal = triangles[0]->SurfaceNormal();
        for (int i = 0; i < triangles.size(); ++i) {
            for (int j = 0; j < 3; ++j) {
                *(vertices + (3*ti + j))         = glm::vec4(triangles[i]->GetPoints()[j], 1.0f);
                *(normals + (3*ti + j))          = glm::vec4(normal, 0.0f);
                *(colors + (3*ti + j))           = poly->mColor;
                *(pickingColors + (3*ti + j))    = poly->mPickingColor;
            }
            ti++;
        }
    }
    
    const GLuint vertexLoc = shadingInterface.vertexLocation();
    const GLuint normalLoc = shadingInterface.normalLocation();
    const GLuint colorLoc = ShadingInterface::kColorAttributeIndex;
    const GLuint pickingColorLoc = ShadingInterface::kPickingColorAttributeIndex;
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    mBuffersCount = 4;
    glGenBuffers(mBuffersCount, mBuffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*mTrianglesCount, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*mTrianglesCount, normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*mTrianglesCount, colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*mTrianglesCount, pickingColors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(pickingColorLoc);
    glVertexAttribPointer(pickingColorLoc, 4, GL_FLOAT, 0, 0, 0);
    
    mRenderData = reinterpret_cast<char*>(data);
    
}
    
    
}