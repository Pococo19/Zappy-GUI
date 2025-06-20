#version 330

/**
* @author:  Leorevoir
* @date:    2025-06-20
* @file:    planet.vert
* @brief:   vertex shader for rendering planets in a space scene
*/

/**
* custom types for fragment data to send to fragment shader
*/

struct Fragment {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
    vec4 color;
};

/**
* input variables for vertex shader
*/

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec4 vertexColor;

/**
* uniform variables for transformation matrices and time
*/

uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
uniform float time;

/**
* output fragment data 
*/

out Fragment frag;

/**
* get fragment data from vertex attributes and transformation matrices
*/
Fragment _get_fragment_data(vec4 world_pos)
{
    Fragment f;

    f.position = world_pos.xyz;
    f.normal = normalize(mat3(matNormal) * vertexNormal);
    f.texCoord = vertexTexCoord;
    f.color = vertexColor;
    return f;
}

void main()
{
    vec4 world_pos = matModel * vec4(vertexPosition, 1.0);
    frag = _get_fragment_data(world_pos);

    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
