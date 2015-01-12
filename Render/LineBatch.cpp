
#include <Render/LineBatch.h>
#include <Shading/ShadingInterface.h>

namespace ftr {

void LineBatch::CreateRenderData(ShadingInterface& shadingInterface)
{
    if (mRenderData) return;
    Validate();
    
    glm::vec4* data = reinterpret_cast<glm::vec4*>(new char[sizeof(glm::vec4)*2*size()*2]);
    
    glm::vec4* vertices         = data;
    glm::vec4* colors           = data + (2 * size());
    
    for (int i = 0; i < size(); ++i) {
        LinePrimitive* line = reinterpret_cast<LinePrimitive*>(mPrimitives[i]);
        
        *(vertices + (2*i))         = glm::vec4(line->mBegin, 1.0f);
        *(vertices + (2*i) + 1)     = glm::vec4(line->mEnd, 1.0f);
        
        *(colors + (2*i))       = line->mColor;
        *(colors + (2*i) + 1)   = line->mColor;

    }
    
    const GLuint colorLoc = shadingInterface.colorLocation();
    const GLuint vertexLoc = shadingInterface.vertexLocation();
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    mBuffersCount = 2;
    glGenBuffers(mBuffersCount, mBuffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*2*size(), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*2*size(), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
    
    mRenderData = reinterpret_cast<char*>(data);
}
    
}
