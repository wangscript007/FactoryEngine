// 
//  Copyright (c) 2012 Dimension. All rights reserved.
//

#include <Workspace/Pad.h>

namespace ftr {

void Pad::Render(Layer& layer)
{
    int linesCount = mfA * mfScale;
    int i;
    int index = 0;
    GLfloat a2 = mfA/2;
    
    GLfloat offset = 0.00f;
    //
    // along x axis
    //
    GLfloat x = -a2;
    for(i = 0; i <= linesCount; i++) {
        if ((i%((int)mfA/2) != 0)  || (i == 0) || (i == mfA)) {
            linePrimitive[index].mBegin = glm::vec3(x, offset, -a2);
            linePrimitive[index].mEnd = glm::vec3(x, 0, a2);
            linePrimitive[index].mColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0);
            linePrimitive[index].setOption(Primitive::kUseDepth, false);
            linePrimitive[index].setOption(Primitive::kUseLighting, false);
            layer.AddPrimitive(linePrimitive[index++]);
        }
		x += mfScale;
    }
    //
    // along z axis
    //
	GLfloat z = -a2;
    for(i = 0; i <= linesCount; i++) {
        if ((i%((int)mfA/2) != 0) || (i == 0) || (i == mfA)) {
            linePrimitive[index].mBegin = glm::vec3(-a2, offset, z);
            linePrimitive[index].mEnd = glm::vec3(a2, offset, z);
            linePrimitive[index].mColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0);
            linePrimitive[index].setOption(Primitive::kUseDepth, false);
            linePrimitive[index].setOption(Primitive::kUseLighting, false);
            layer.AddPrimitive(linePrimitive[index++]);
        }
		z += mfScale;
	}
    //
    // Axes
    //
    float a = mfA;
	// x
    linePrimitive[index].mBegin = glm::vec3(-a/2, offset, 0);
    linePrimitive[index].mEnd = glm::vec3(a/2+1, offset, 0);
    linePrimitive[index].mColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0);
    linePrimitive[index].setOption(Primitive::kUseDepth, false);
    linePrimitive[index].setOption(Primitive::kUseLighting, false);
    layer.AddPrimitive(linePrimitive[index++]);
//    // y
//    linePrimitive[index].mBegin = glm::vec3(0, 0, 0);
//    linePrimitive[index].mEnd = glm::vec3(0, a/2, 0);
//    linePrimitive[index].mColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0);
//    linePrimitive[index].setOption(Primitive::kUseDepth, false);
//    linePrimitive[index].setOption(Primitive::kUseLighting, false);
//    layer.AddPrimitive(linePrimitive[index++]);
    // z
    linePrimitive[index].mBegin = glm::vec3(0, offset, -a/2);
    linePrimitive[index].mEnd = glm::vec3(0, offset, a/2+1);
    linePrimitive[index].mColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0);
    linePrimitive[index].setOption(Primitive::kUseDepth, false);
    linePrimitive[index].setOption(Primitive::kUseLighting, false);
    layer.AddPrimitive(linePrimitive[index++]);
    
    static const glm::vec4 color = glm::vec4(0.1f, 0.3f, 0.1f, 0.1f);
    float k = 2000;
    if (mInvalid) {
        mPolygonPrimitive.Clear();
        mPolygonPrimitive.AddPoint(glm::vec3(k,0,k));
        mPolygonPrimitive.AddPoint(glm::vec3(k,0,-k));
        mPolygonPrimitive.AddPoint(glm::vec3(-k,0,-k));
        mPolygonPrimitive.AddPoint(glm::vec3(-k,0,k));
        mPolygonPrimitive.mColor = color;
        mPolygonPrimitive.setOption(Primitive::kUseDepth, false);
//        mPolygonPrimitive.setOption(Primitive::kUseBlend, true);
    }
    layer.AddPrimitive(mPolygonPrimitive);
}

}