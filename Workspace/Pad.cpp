// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/Pad.h>
#include <Main/Log.h>

namespace ftr {

void Pad::Render(Layer& layer)
{
    int linesCount = mfA * mfScale;
    int i;
    int index = 0;
    GLfloat a2 = mfA/2;
    //
    // along x axis
    //
    GLfloat x = -a2;
    for(i = 0; i <= linesCount; i++) {
        if ((i%((int)mfA/2) != 0)  || (i == 0) || (i == mfA)) {
            linePrimitive[index].mBegin.set(x, 0, -a2);
            linePrimitive[index].mEnd.set(x, 0, a2);
            linePrimitive[index].color.set(1.0f, 1.0f, 1.0f);
            linePrimitive[index].setOption(Primitive::kUseDepth, true);
            linePrimitive[index].setOption(Primitive::kUseLighting, false);
            layer.AddPrimitive(linePrimitive[index++]);
            ;
        }
		x += mfScale;
    }
    //
    // along z axis
    //
	GLfloat z = -a2;
    for(i = 0; i <= linesCount; i++) {
        if ((i%((int)mfA/2) != 0) || (i == 0) || (i == mfA)) {
            linePrimitive[index].mBegin.set(-a2, 0, z);
            linePrimitive[index].mEnd.set(a2, 0, z);
            linePrimitive[index].color.set(1.0f, 1.0f, 1.0f);
            linePrimitive[index].setOption(Primitive::kUseDepth, true);
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
    linePrimitive[index].mBegin.set(-a/2, 0, 0);
    linePrimitive[index].mEnd.set(a/2+1, 0, 0);
    linePrimitive[index].color.set(1.0f, 0.0f, 0.0f);
    linePrimitive[index].setOption(Primitive::kUseDepth, true);
    linePrimitive[index].setOption(Primitive::kUseLighting, false);
    layer.AddPrimitive(linePrimitive[index++]);
    // y
    linePrimitive[index].mBegin.set(0, 0, 0);
    linePrimitive[index].mEnd.set(0, a/2, 0);
    linePrimitive[index].color.set(0.0f, 1.0f, 0.0f);
    linePrimitive[index].setOption(Primitive::kUseDepth, true);
    linePrimitive[index].setOption(Primitive::kUseLighting, false);
    layer.AddPrimitive(linePrimitive[index++]);
    // z
    linePrimitive[index].mBegin.set(0, 0, -a/2);
    linePrimitive[index].mEnd.set(0, 0, a/2+1);
    linePrimitive[index].color.set(0.0f, 0.0f, 1.0f);
    linePrimitive[index].setOption(Primitive::kUseDepth, true);
    linePrimitive[index].setOption(Primitive::kUseLighting, false);
    layer.AddPrimitive(linePrimitive[index++]);
}

}