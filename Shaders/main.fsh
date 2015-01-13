
#define LIGHT0 0
#define LIGHT1 1
#define LIGHT2 2
#define LIGHT3 3
#define LIGHT4 4

struct Transform {
    MAT4 view;
    MAT4 projection;
};

struct Settings {
    int lightsCount;
};

struct Light {
    VEC4 ambient;
    VEC4 diffuse;
    VEC4 specular;
    VEC4 position;
    VEC4 halfVector;
    VEC3 spotDirection;
    float spotExponent;
    float spotCutoff;
    float spotCosCutoff;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    int useLocalCoordinates;
};

uniform Transform transformVar;
uniform Settings settingsVar;
uniform Light light0, light1, light2, light3, light4;
uniform VEC2 windowSize;

in VEC4 localNormal;
in VEC3 localNormal3;
in VEC4 localPosition;
in VEC3 localPosition3;
in VEC4 Color;
in VEC3 Eye;

out VEC4 outputF;

//--------------------------------------------------------------------------------------------------
VEC4 Local(in VEC4 coords)
{
    return transformVar.view * coords;
}

//--------------------------------------------------------------------------------------------------
void DirectionalLight(in Light light,
                      in VEC3 normal,
                      inout VEC4 ambient,
                      inout VEC4 diffuse,
                      inout VEC4 specular)
{
    float nDotVP;         // normal . light direction
    float nDotHV;         // normal . light half vector
    float pf;             // power factor
    
    VEC4 lightPosition = light.position;
    if (light.useLocalCoordinates > 0) {
        lightPosition = Local(light.position);
    } 
    nDotVP = max(0.0, dot(normal, normalize(vec3(lightPosition))));
    nDotHV = max(0.0, dot(normal, vec3(light.halfVector)));

    if (nDotVP == 0.0) {
        pf = 0.0;
    } else {
        pf = pow(nDotHV, 1.0f);
    }
    ambient  += light.ambient;
    diffuse  += light.diffuse * nDotVP;
    specular += light.specular * pf;
}

//--------------------------------------------------------------------------------------------------
void PointLight(in Light light,
                in VEC3 eye,
                in VEC3 ecPosition3,
                in VEC3 normal,
                inout VEC4 ambient,
                inout VEC4 diffuse,
                inout VEC4 specular)
{
    float nDotVP;         // normal . light direction
    float nDotHV;         // normal . light half vector
    float pf;             // power factor
    float attenuation;    // computed attenuation factor
    float d;              // distance from surface to light source
    VEC3  VP;             // direction from surface to light    position
    VEC3  halfVector;     // direction of maximum highlights

    if (light.useLocalCoordinates > 0) {
        VP = vec3(Local(light.position)) - ecPosition3;
    } else {
        VP = vec3(light.position) - ecPosition3;
    }
    
    // Compute vector from surface to light position
    

    // Compute distance between surface and light position
    d = length(VP);

    // Normalize the vector from surface to light position
    VP = normalize(VP);

    // Compute attenuation
    
    attenuation = 1.0 / (light.constantAttenuation +
                         light.linearAttenuation * d +
                         light.quadraticAttenuation * d * d);
    
    halfVector = normalize(VP + eye);

    nDotVP = max(0.0, dot(normal, VP));
    nDotHV = max(0.0, dot(normal, halfVector));

    if (nDotVP == 0.0) {
        pf = 0.0;
    } else {
        pf = pow(nDotHV, 1.0f);
    }

    ambient += light.ambient * attenuation;
    diffuse += light.diffuse * nDotVP * attenuation;
    specular += light.specular * pf * attenuation;
}

//--------------------------------------------------------------------------------------------------
void SpotLight(in Light light,
               in VEC3 eye,
               in VEC3 ecPosition3,
               in VEC3 normal,
               inout VEC4 ambient,
               inout VEC4 diffuse,
               inout VEC4 specular)
{
    float nDotVP;           // normal . light direction
    float nDotHV;           // normal . light half vector
    float pf;               // power factor
    float spotDot;          // cosine of angle between spotlight
    float spotAttenuation;  // spotlight attenuation factor
    float attenuation;      // computed attenuation factor
    float d;                // distance from surface to light source
    VEC3 VP;                // direction from surface to light position
    VEC3 halfVector;        // direction of maximum highlights
    VEC4 lightPosition;
    VEC3 spotDirection;
    
    spotDirection = light.spotDirection;
    if (light.useLocalCoordinates > 0) {
        lightPosition = Local(light.position);
        spotDirection = vec3(Local(vec4(light.spotDirection, 0)));
    } else {
        lightPosition = light.position;
    }
    VP = vec3(lightPosition) - ecPosition3;
    


    // Compute distance between surface and light position
    d = length(VP);

    // Normalize the vector from surface to light position
    VP = normalize(VP);

    // Compute attenuation

    attenuation = 1.0 / (light.constantAttenuation +
                         light.linearAttenuation * d +
                         light.quadraticAttenuation * d * d);

    // See if point on surface is inside cone of illumination
    spotDot = dot(-VP, normalize(spotDirection));

    if (spotDot < light.spotCosCutoff) {
        spotAttenuation = 0.0; // light adds no contribution
    } else {
        spotAttenuation = pow(spotDot, light.spotExponent);
        
    }

    // Combine the spotlight and distance attenuation.
    attenuation *= spotAttenuation;

    halfVector = normalize(VP + eye);

    nDotVP = max(0.0, dot(normal, VP));
    nDotHV = max(0.0, dot(normal, halfVector));

    if (nDotVP == 0.0)
        pf = 0.0;
    else
        pf = pow(nDotHV, 1.0);

    
    ambient  += light.ambient * attenuation;
    diffuse  += light.diffuse * nDotVP * attenuation;
    specular += light.specular * pf * attenuation;
}



//--------------------------------------------------------------------------------------------------
void main()
{
    if (settingsVar.lightsCount > 0) {
        VEC4 amb  = vec4(0.0);
        VEC4 diff = vec4(0.0);
        VEC4 spec = vec4(0.0);
        Light light;
        if (gl_FrontFacing) {

            for (int i = 0; i < settingsVar.lightsCount; i++)
            {
                if (i == LIGHT0) {
                    light = light0;
                } else if (i == LIGHT1) {
                    light = light1;
                } else if (i == LIGHT2) {
                    light = light2;
                } else if (i == LIGHT3) {
                    light = light3;
                } else if (i == LIGHT4) {
                    light = light4;
                }
                if (light.position.w == 0.0) {
                    DirectionalLight(light, localNormal3, amb, diff, spec);
                } else if (light.spotCutoff == 180.0) {
                    PointLight(light, Eye, localPosition3, localNormal3, amb, diff, spec);
                }
                else {
                    SpotLight(light, Eye, localPosition3, localNormal3, amb, diff, spec);
                }
            }
        }
        else {
            VEC3 backLocalNormal3 = -localNormal3;
            
            for (int i = 0; i < settingsVar.lightsCount; i++)
            {
                if (i == LIGHT0) {
                    light = light0;
                } else if (i == LIGHT1) {
                    light = light1;
                } else if (i == LIGHT2) {
                    light = light2;
                } else if (i == LIGHT3) {
                    light = light3;
                } else if (i == LIGHT4) {
                    light = light4;
                }
                if (light.position.w == 0.0) {
                    DirectionalLight(light, backLocalNormal3, amb, diff, spec);
                } else if (light.spotCutoff == 180.0) {
                    PointLight(light, Eye, localPosition3, backLocalNormal3, amb, diff, spec);
                }
                else {
                    SpotLight(light, Eye, localPosition3, backLocalNormal3, amb, diff, spec);
                }
            }   
        }
        outputF = Color + amb * 0.33 + diff * 0.33 + spec * 0.33;
    } else {
        outputF = Color;
    }
}