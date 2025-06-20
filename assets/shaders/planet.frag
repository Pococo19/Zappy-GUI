#version 330

/**
* @author:  Leorevoir
* @date:    2025-06-20
* @file:    planet.frag
* @brief:   fragment shader for rendering planets in a space scene
*/

/**
* macros for planet shader
*/

#define ATTEN_LINEAR       0.005
#define ATTEN_QUADRATIC    0.0001
#define DIFFUSE_WEIGHT     0.7
#define SUBSURF_WEIGHT     0.3
#define SUBSURF_POWER      1.2
#define RIM_POWER          2.0
#define ATMOS_STRENGTH     0.4
#define AMBIENT_COLOR      vec3(0.02, 0.02, 0.05)

/**
* input variables from vertex shader
*/

struct Fragment {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
    vec4 color;
};

in Fragment frag;

/**
* uniform variables
*/

uniform float   time;
uniform vec3    viewPos;

uniform vec3    lightPos;
uniform vec3    lightColor;
uniform float   lightIntensity;
uniform vec3    planetBaseColor;

/**
* output fragment color
*/

out vec4 finalColor;

/**
* calculate diffuse lighting with subsurface scattering
*/
vec3 _diffuse_lighting(vec3 lightPos, vec3 lightColor, float lightIntensity, vec3 fragPos, vec3 normal)
{
    vec3 light_dir      = normalize(lightPos - fragPos);
    float distance      = length(lightPos - fragPos);
    float attenuation   = lightIntensity / (1.0 + ATTEN_LINEAR * distance + ATTEN_QUADRATIC * distance * distance);
    float diffuse       = max(dot(normal, light_dir), 0.0);
    float subsurface    = max(0.0, dot(normal, light_dir) * 0.4 + 0.6);

    subsurface          = pow(subsurface, SUBSURF_POWER);

    float lighting      = diffuse * DIFFUSE_WEIGHT + subsurface * SUBSURF_WEIGHT;

    return lightColor * lighting * attenuation;
}

/**
* calculate the atmospheric glow effect
* this simulates the scattering of light in the atmosphere
*/
vec3 _atmosphere_glow(vec3 lightPos, vec3 fragPos, vec3 normal, vec3 viewDir)
{
    vec3 light_dir      = normalize(lightPos - fragPos);
    float rim           = 1.0 - max(0.0, dot(normal, viewDir));

    rim                 = pow(rim, RIM_POWER);

    float sunFacing     = max(0.0, dot(normal, light_dir));
    vec3 atmo_day       = vec3(0.3, 0.5, 0.8);
    vec3 atmo_night     = vec3(0.2, 0.1, 0.3);
    vec3 atmo_color     = mix(atmo_night, atmo_day, sunFacing);

    return atmo_color * rim * ATMOS_STRENGTH;
}

/**
* calculate ambient lighting for the planet
* space is dark but not completely black
*/
vec3 _ambient_lighting()
{
    return AMBIENT_COLOR;
}

/**
* simulate a gradient for day/night transition
*/
float _day_night_gradient(vec3 lightPos, vec3 fragPos, vec3 normal)
{
    vec3 light_dir      = normalize(lightPos - fragPos);
    float sun_angle     = dot(normal, light_dir);

    return smoothstep(-0.2, 0.2, sun_angle);
}

void main()
{
    vec3 normal         = normalize(frag.normal);
    vec3 viewDir        = normalize(viewPos - frag.position);
    vec3 baseColor      = planetBaseColor * frag.color.rgb;

    vec3 diffuse_light  = _diffuse_lighting(lightPos, lightColor, lightIntensity, frag.position, normal);
    vec3 ambient_light  = _ambient_lighting();
    vec3 atmo_glow      = _atmosphere_glow(lightPos, frag.position, normal, viewDir);

    float dn_factor     = _day_night_gradient(lightPos, frag.position, normal);

    vec3 total_light    = diffuse_light + ambient_light;

    vec3 day_color      = baseColor * total_light;
    vec3 night_color    = baseColor * ambient_light * 0.3;
    
    vec3 planet_color   = mix(night_color, day_color, dn_factor);
    planet_color += atmo_glow;


    vec3 light_dir      = normalize(lightPos - frag.position);
    float sun_angle     = dot(normal, light_dir);
    
    if (sun_angle > 0.0) {
        planet_color *= mix(vec3(1.0), vec3(1.0, 0.95, 0.85), sun_angle * 0.3);
    } else {
        planet_color *= vec3(0.7, 0.8, 1.0);
    }

    if (frag.color.b > frag.color.r && frag.color.b > frag.color.g) {

        vec3 reflect_dir= reflect(-light_dir, normal);
        float spec      = pow(max(dot(viewDir, reflect_dir), 0.0), 32.0);

        planet_color += lightColor * spec * 0.5 * dn_factor;
    }

    finalColor          = vec4(planet_color, 1.0);
}
