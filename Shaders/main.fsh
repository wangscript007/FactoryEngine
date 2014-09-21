
#define LIGHT0 0
#define LIGHT1 1
#define LIGHT2 2
#define LIGHT3 3
#define LIGHT4 4

struct Transform {
    mat4 view;
    mat4 projection;
};

struct Settings {
    int lightsCount;
    int debugLineWidth;
    int debugOn;
    float debugFloatScale;
};

struct Light {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    vec4 halfVector;
    vec3 spotDirection;
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
uniform vec2 windowSize;

in vec4 localNormal;
in vec3 localNormal3;
in vec4 localPosition;
in vec3 localPosition3;
in vec4 Color;
in vec3 Eye;

float debugFloat = 0.0f;

out vec4 outputF;

//--------------------------------------------------------------------------------------------------
vec4 Local(in vec4 coords)
{
    return transformVar.view * coords;
}

//--------------------------------------------------------------------------------------------------
void DirectionalLight(in Light light,
in vec3 normal,
inout vec4 ambient,
inout vec4 diffuse,
inout vec4 specular)
{
    float nDotVP;         // normal . light direction
    float nDotHV;         // normal . light half vector
    float pf;             // power factor
    
    vec4 lightPosition = light.position;
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
                in vec3 eye,
                in vec3 ecPosition3,
                in vec3 normal,
                inout vec4 ambient,
                inout vec4 diffuse,
                inout vec4 specular)
{
    float nDotVP;         // normal . light direction
    float nDotHV;         // normal . light half vector
    float pf;             // power factor
    float attenuation;    // computed attenuation factor
    float d;              // distance from surface to light source
    vec3  VP;             // direction from surface to light    position
    vec3  halfVector;     // direction of maximum highlights

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
               in vec3 eye,
               in vec3 ecPosition3,
               in vec3 normal,
               inout vec4 ambient,
               inout vec4 diffuse,
               inout vec4 specular)
{
    float nDotVP;           // normal . light direction
    float nDotHV;           // normal . light half vector
    float pf;               // power factor
    float spotDot;          // cosine of angle between spotlight
    float spotAttenuation;  // spotlight attenuation factor
    float attenuation;      // computed attenuation factor
    float d;                // distance from surface to light source
    vec3 VP;                // direction from surface to light position
    vec3 halfVector;        // direction of maximum highlights
    vec4 lightPosition;
    vec3 spotDirection;
    
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
    vec4 amb  = vec4(0.0);
    vec4 diff = vec4(0.0);
    vec4 spec = vec4(0.0);
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
        vec3 backLocalNormal3 = -localNormal3;
        
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
    
    outputF = Color + amb * 0.3 + diff * 0.3 + spec * 0.3;
    
    

    
}