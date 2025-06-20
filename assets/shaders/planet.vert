#version 330

struct Fragment {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
    vec4 color;
};

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
uniform float time;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;
out vec4 fragColor;
out vec3 worldPos;

void main()
{
    vec4 world_position = matModel * vec4(vertexPosition, 1.0);
    fragPosition = world_position.xyz;
    worldPos = world_position.xyz;

    fragNormal = normalize(mat3(matNormal) * vertexNormal);
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
