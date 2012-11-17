
#pragma once

//
// Macros
//
#define FTDEBUG

//
// System
//
#include "OpenGL/glu.h"
#include "OpenGl/gl.h"
#include <math.h>
#include "stdio.h"
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
//
// External
//
#include "External/Box2D/Box2D.h"
#include "External/On5/Manifest.h"
//
// Main
//
#include "Main/FTGLError.h"
#include "Main/FTLog.h"
//
// Math
//
#include "Math/FTVec.h"
#include "Math/FTUtils.h"
//
// Model
//
#include "Model/FTNode.h"
#include "Model/FTModel.h"
#include "Model/FTPoint.h"
#include "Model/FTLine.h"
#include "Model/FTPolygon.h"
#include "Model/FTFace.h"
#include "Model/FTBody.h"
#include "Model/FTGroup.h"
#include "Model/FTModelFactory.h"
//
// Surround
//
#include "Surround/FTCamera.h"
#include "Surround/FTLights.h"
//
// Workspace
//
#include "Workspace/FTPad.h"
#include "Workspace/FTHUD.h"
#include "Workspace/FTWorkspace.h"
//
// Managers
//
#include "Managers/FTModelTreeManager.h"
#include "Managers/FTModelManager.h"
//
// Scene
//
#include "Scene/FTScene.h"

