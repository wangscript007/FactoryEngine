
#include <FactoryEngine.h>

void FTLights::TurnOn(int index)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    switch (index) {
        case 0: {
            glEnable(GL_LIGHT0);
            GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 0.5 };
            GLfloat mat_shininess[] = { 20.0 };
            GLfloat light_position[] = { 0.5, 0.5, 0.5, 0.5 };
            GLfloat white_light[] = { 0.5, 0.5, 0.5, 0.5 };
            GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        } break;
            
        case 1: {
            glEnable(GL_LIGHT1);
            //
            // Define the ambient component of the first light
            //
            const GLfloat light0Ambient[] = {0.1, 0.1, 0.1, 1.0};
            glLightfv(GL_LIGHT1, GL_AMBIENT, light0Ambient);
            // Define the diffuse component of the first light
            const GLfloat light0Diffuse[] = {0.7, 0.7, 0.7, 1.0};
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light0Diffuse);
            //
            // Define the specular component and shininess of the first light
            //
            const GLfloat light0Specular[] = {0.7, 0.7, 0.7, 1.0};
            glLightfv(GL_LIGHT1, GL_SPECULAR, light0Specular);
            //
            // Define the position of the first light
            //
            const GLfloat light0Position[] = {0.0, 10.0, 10.0, 0.0}; 
            glLightfv(GL_LIGHT1, GL_POSITION, light0Position); 
            //
            // Define a direction vector for the light, this one points right down the Z axis
            //
            const GLfloat light0Direction[] = {0.0, 0.0, -1.0};
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light0Direction);
            //
            // Define a cutoff angle. This defines a 90° field of vision, since the cutoff
            // is number of degrees to each side of an imaginary line drawn from the light's
            // position along the vector supplied in GL_SPOT_DIRECTION above
            //
            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
        } break;
    }
}

void FTLights::TurnOff(int index)
{
    switch (index) {
        case 0:
            glDisable(GL_LIGHT0);
            break;
        case 1:
            glDisable(GL_LIGHT1);
            break;
        default:
            glDisable(GL_COLOR_MATERIAL);
            glDisable(GL_LIGHTING);
            break;
    }
}