#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform mat4 mvp;
uniform mat4 matModel;
uniform float time;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

void main()
{
    /** subtle vertex displacement for surface movement */
    vec3 pos = vertexPosition;
    
    /** using sine functions to create a wave-like effect */
    float wave1 = sin(pos.x * 8.0 + time * 2.0) * 0.02;
    float wave2 = sin(pos.y * 6.0 + time * 1.5) * 0.015;
    float wave3 = sin(pos.z * 10.0 + time * 2.5) * 0.01;
    
    pos += normalize(pos) * (wave1 + wave2 + wave3);
    
    fragPosition = vec3(matModel * vec4(pos, 1.0));
    fragNormal = normalize(vec3(matModel * vec4(vertexNormal, 0.0)));
    fragTexCoord = vertexTexCoord;
    
    gl_Position = mvp * vec4(pos, 1.0);
}
