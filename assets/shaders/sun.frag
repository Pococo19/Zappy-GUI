#version 330

/**
* @author:  Leorevoir
* @date:    2025-06-20
* @file:    sun.frag
* @brief:   fragment shader for rendering a stylized sun with animated flames and radial gradient coloring.
*/

/**
* types
*/

struct SunColorPalette {
    vec3    core;
    vec3    inner;
    vec3    middle;
    vec3    outer;
    vec3    corona;
};

struct Fragment {
    vec3    position;
    vec3    normal;
    vec2    texCoord;
};

/**
* input variables from vertex shader
*/

in Fragment     frag;

/**
* uniform variables
*/

uniform float   time;
uniform vec3    viewPos;

/**
* output fragment color
*/

out vec4        finalColor;

/**
* get default sun color palette
*/
SunColorPalette _get_default_palette()
{
    SunColorPalette palette;

    palette.core    = vec3(1.0, 0.9, 0.7);    //<< hot white-yellow
    palette.inner   = vec3(1.0, 0.75, 0.3);   //<< orange-yellow
    palette.middle  = vec3(1.0, 0.5, 0.15);   //<< orange
    palette.outer   = vec3(0.95, 0.25, 0.05); //<< red-orange
    palette.corona  = vec3(0.9, 0.2, 0.0);    //<< crimson red
    return palette;
}

void main()
{
    /** sphere coords for flames */
    float theta     = atan(frag.texCoord.y - 0.5, frag.texCoord.x - 0.5);
    float radius    = length(frag.texCoord - vec2(0.5));

    /** flame distortion animation */
    float flame1    = sin(theta * 6.0 + time * 2.0) * 0.1;
    float flame2    = sin(theta * 8.0 + time * 3.0) * 0.05;
    float flame3    = sin(theta * 12.0 + time * 4.0) * 0.03;
    float distortion= flame1 + flame2 + flame3;
    float surface   = smoothstep(0.4, 0.6, radius + distortion);

    SunColorPalette sun = _get_default_palette();

    /** gradient radial coloring orange/red transitions */
    float gradient1 = smoothstep(0.0, 0.25, radius);
    float gradient2 = smoothstep(0.25, 0.5, radius);
    float gradient3 = smoothstep(0.5, 0.8, radius);
    float gradient4 = smoothstep(0.7, 0.9, radius);

    vec3 sun_color  = mix(sun.core, sun.inner, gradient1);
    sun_color       = mix(sun_color, sun.middle, gradient2);
    sun_color       = mix(sun_color, sun.outer, gradient3);
    sun_color       = mix(sun_color, sun.corona, gradient4 * 0.6);

    /** orange/red in mid-range */
    float orange_red= smoothstep(0.2, 0.6, radius) * (1.0 - smoothstep(0.6, 0.8, radius));
    vec3 boost_color= vec3(1.0, 0.4, 0.1);
    sun_color       = mix(sun_color, boost_color, orange_red * 0.4);

    float corona_in = smoothstep(0.4, 0.7, radius) * (1.0 - smoothstep(0.7, 1.0, radius));
    sun_color       = mix(sun_color, sun.corona, corona_in * 0.5);

    /** pulsation */
    float pulse     = 0.8 + 0.2 * sin(time * 2.0);
    float temp_var  = 0.9 + 0.1 * sin(time * 1.5);
    sun_color *= pulse;
    sun_color.rg *= temp_var;

    /** fresnel/chip highlight near edge */
    float fresnel   = 1.0 - dot(normalize(frag.normal), normalize(viewPos - frag.position));
    fresnel         = pow(fresnel, 2.0);
    sun_color += vec3(0.4, 0.15, 0.0) * fresnel;

    /** sunspots (darker patches) */
    float spot1     = smoothstep(0.15, 0.25, length(frag.texCoord - vec2(0.3, 0.4)));
    float spot2     = smoothstep(0.1, 0.2, length(frag.texCoord - vec2(0.7, 0.6)));
    sun_color *= mix(0.6, 1.0, spot1 * spot2);

    finalColor      = vec4(sun_color, 1.0);
}
