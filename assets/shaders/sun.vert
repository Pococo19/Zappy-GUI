#version 330

/**
* @author:  Leorevoir
* @date:    2025-06-20
* @file:    sun.vert
* @brief:   vertex shader for the sun model (with deformations and instable disturbances)
*/

/**
* custom types for fragment data to send to fragment shader
*/

struct Fragment {
    vec3    position;
    vec3    normal;
    vec2    texCoord;
};

/**
* input variables for vertex shader
*/

in vec3     vertexPosition;
in vec3     vertexNormal;
in vec2     vertexTexCoord;

/**
* uniform variables for transformation matrices and time
*/

uniform mat4    mvp;
uniform mat4    matModel;
uniform float   time;

/**
* output fragment data 
*/

out Fragment    frag;

/**
* get fragment data from vertex attributes and transformation matrices
*/
Fragment _get_fragment_data(vec3 pos)
{
    Fragment f;

    f.position  = vec3(matModel * vec4(pos, 1.0));
    f.normal    = normalize(vec3(matModel * vec4(vertexNormal, 0.0)));
    f.texCoord  = vertexTexCoord;
    return f;
}

void main()
{
    /** subtle vertex displacement for surface movement */
    vec3 pos    = vertexPosition;
    
    /** using sine functions to create a wave-like effect */
    float wave1 = sin(pos.x * 8.0 + time * 2.0) * 0.02;
    float wave2 = sin(pos.y * 6.0 + time * 1.5) * 0.015;
    float wave3 = sin(pos.z * 10.0 + time * 2.5) * 0.01;
    
    pos += normalize(pos) * (wave1 + wave2 + wave3);
    frag = _get_fragment_data(pos);

    gl_Position = mvp * vec4(pos, 1.0);
}
