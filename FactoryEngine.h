
#pragma once

//
// Macros
//

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <utility>
#include <algorithm>
#include <queue>
#include "OpenGL/glu.h"
#include "OpenGl/gl3.h"


#include "External/Box2D/Box2D.h"
//
// Platform macros.
//
#define _ALIGN(n) __attribute__((aligned(n)))

typedef unsigned char           Byte;             // 1 byte
typedef unsigned short int      Word;             // 2 bytes
typedef unsigned int            Doubleword;       // 4 bytes
typedef unsigned long long int  Quadrupleword;    // 8 bytes

#include "External/TutorialHelper.h"

//
// Main
//
#include "Main/GLError.h"
#include "Main/Log.h"
//
// Math
//
#include "Math/Util.h"
#include "Math/Color.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/Mat2.h"
#include "Math/Mat3x2.h"
#include "Math/Mat4.h"
#include "Math/Frame.h"
#include "Math/Utils.h"
#include "Math/Rect.h"

//
// Model
//
#include "Model/Node.h"
#include "Model/PointNode.h"
#include "Model/LineNode.h"
#include "Model/FaceNode.h"
#include "Model/BodyNode.h"
#include "Model/GroupNode.h"
#include "Model/ModelFactory.h"

//
// Surround
//
#include "Surround/Camera.h"
#include "Surround/Lights.h"
//
// Workspace
//
#include "Workspace/Pad.h"
#include "Workspace/HUD.h"
#include "Workspace/Workspace.h"
//
// Managers
//
#include "Model/ModelTreeManager.h"
#include "Model/ModelManager.h"
//
// Scene
//
#include "Scene/Scene.h"

