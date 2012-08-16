
#pragma once

//
// C++ standard library.
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
#include <list>
#include <utility>
#include <algorithm>
#include <queue>
//
// Platform macros.
//
#define O5_ALIGN(n) __attribute__((aligned(n)))

typedef unsigned char           O5Byte;             // 1 byte
typedef unsigned short int      O5Word;             // 2 bytes
typedef unsigned int            O5Doubleword;       // 4 bytes
typedef unsigned long long int  O5Quadrupleword;    // 8 bytes

#include "Util.h"
#include "Color.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat2.h"
#include "Mat3x2.h"
#include "Mat4.h"
#include "Frame.h"
