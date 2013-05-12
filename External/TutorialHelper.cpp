
#include "TutorialHelper.h"


// res = a cross b;
void TutorialHelper::crossProduct( float *a, float *b, float *res) {
    
    res[0] = a[1] * b[2]  -  b[1] * a[2];
    res[1] = a[2] * b[0]  -  b[2] * a[0];
    res[2] = a[0] * b[1]  -  b[0] * a[1];
}

// Normalize a vec3
void TutorialHelper::normalize(float *a) {
    
    float mag = sqrt(a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2]);
    
    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}

// ----------------------------------------------------
// MATRIX STUFF
//

// sets the square matrix mat to the identity matrix,
// size refers to the number of rows (or columns)
void TutorialHelper::setIdentityMatrix( float *mat, int size) {
    
    // fill matrix with 0s
    for (int i = 0; i < size * size; ++i)
        mat[i] = 0.0f;
    
    // fill diagonal with 1s
    for (int i = 0; i < size; ++i)
        mat[i + i * size] = 1.0f;
}

//
// a = a * b;
//
void TutorialHelper::multMatrix(float *a, float *b) {
    
    float res[16];
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[j*4 + i] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                res[j*4 + i] += a[k*4 + i] * b[j*4 + k];
            }
        }
    }
    memcpy(a, res, 16 * sizeof(float));
    
}

// Defines a transformation matrix mat with a translation
void TutorialHelper::setTranslationMatrix(float *mat, float x, float y, float z) {
    
    setIdentityMatrix(mat,4);
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

// ----------------------------------------------------
// Projection Matrix
//

void TutorialHelper::buildProjectionMatrix(float *mat, float fov, float ratio, float nearP, float farP) {
    
    float f = 1.0f / tan (fov * (M_PI / 360.0));
    
    setIdentityMatrix(mat,4);
    
    mat[0] = f / ratio;
    mat[1 * 4 + 1] = f;
    mat[2 * 4 + 2] = (farP + nearP) / (nearP - farP);
    mat[3 * 4 + 2] = (2.0f * farP * nearP) / (nearP - farP);
    mat[2 * 4 + 3] = -1.0f;
    mat[3 * 4 + 3] = 0.0f;
}

// ----------------------------------------------------
// View Matrix
//
// note: it assumes the camera is not tilted,
// i.e. a vertical up vector (remmeber gluLookAt?)
//

void TutorialHelper::setCamera(float *mat, float posX, float posY, float posZ,
               float lookAtX, float lookAtY, float lookAtZ) {
    
    float dir[3], right[3], up[3];
    
    up[0] = 0.0f;   up[1] = 1.0f;   up[2] = 0.0f;
    
    dir[0] =  (lookAtX - posX);
    dir[1] =  (lookAtY - posY);
    dir[2] =  (lookAtZ - posZ);
    normalize(dir);
    
    crossProduct(dir,up,right);
    normalize(right);
    
    crossProduct(right,dir,up);
    normalize(up);
    
    float aux[16];
    
    mat[0]  = right[0];
    mat[4]  = right[1];
    mat[8]  = right[2];
    mat[12] = 0.0f;
    
    mat[1]  = up[0];
    mat[5]  = up[1];
    mat[9]  = up[2];
    mat[13] = 0.0f;
    
    mat[2]  = -dir[0];
    mat[6]  = -dir[1];
    mat[10] = -dir[2];
    mat[14] =  0.0f;
    
    mat[3]  = 0.0f;
    mat[7]  = 0.0f;
    mat[11] = 0.0f;
    mat[15] = 1.0f;
    printf("\n---------\n");
    for (int i = 0; i < 16; ++i)
    {
        if (i%4==0) {
            printf("\n");
        }
        printf("%d: [%f] \n",i, mat[i]);
        
    }
    setTranslationMatrix(aux, -posX, -posY, -posZ);
    printf("\n---------\n");
    for (int i = 0; i < 16; ++i)
    {
        if (i%4==0) {
            printf("\n");
        }
        printf("%d: [%f] \n",i, aux[i]);
        
    }

    printf("\n---------\n");
    multMatrix(mat, aux);
    for (int i = 0; i < 16; ++i)
    {
        if (i%4==0) {
            printf("\n");
        }
        printf("%d: [%f] \n",i, mat[i]);
        
    }
    
    
}
