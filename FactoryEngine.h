
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

#include <glm/glm.hpp>
//
// Platform macros.
//
#define _ALIGN(n) __attribute__((aligned(n)))

typedef unsigned char           Byte;             // 1 byte
typedef unsigned short int      Word;             // 2 bytes
typedef unsigned int            Doubleword;       // 4 bytes
typedef unsigned long long int  Quadrupleword;    // 8 bytes

//
// Main
//
#include "Main/GLError.h"
#include "Main/Log.h"
#include "Main/Macros.h"
//
// Math
//l
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
// Workspace
//
#include "Workspace/Pad.h"
#include "Workspace/HUD.h"
#include "Workspace/Workspace.h"
//
// Managers
//
#include "Model/ModelTree.h"
#include "Model/ModelEditor.h"
//
// Scene
//
#include "Scene/Scene.h"
#include "Scene/Camera.h"

