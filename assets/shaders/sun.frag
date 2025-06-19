#version 330

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform float time;
uniform vec3 viewPos;

out vec4 finalColor;

void main()
{
    /** sphere coords for flames */
    float theta = atan(fragTexCoord.y - 0.5, fragTexCoord.x - 0.5);
    float radius = length(fragTexCoord - vec2(0.5));

    /** flames animation */
    float flame1 = sin(theta * 6.0 + time * 2.0) * 0.1;
    float flame2 = sin(theta * 8.0 + time * 3.0) * 0.05;
    float flame3 = sin(theta * 12.0 + time * 4.0) * 0.03;

    /** surface disturbance */
    float distortion = flame1 + flame2 + flame3;
    float surface = smoothstep(0.4, 0.6, radius + distortion);

    /** sun color */
    vec3 coreColor = vec3(1.0, 0.9, 0.3);    //<< hot yellow
    vec3 middleColor = vec3(1.0, 0.6, 0.1);  //<< orange
    vec3 outerColor = vec3(1.0, 0.2, 0.0);   //<< red

    /** gradient radial */
    float gradientFactor = smoothstep(0.0, 0.8, radius);
    vec3 sunColor = mix(coreColor, middleColor, gradientFactor);
    sunColor = mix(sunColor, outerColor, smoothstep(0.5, 1.0, radius));

    /** pulsation */
    float pulse = 0.8 + 0.2 * sin(time * 2.0);
    sunColor *= pulse;

    /** chips at the edge */
    float fresnel = 1.0 - dot(normalize(fragNormal), normalize(viewPos - fragPosition));
    fresnel = pow(fresnel, 2.0);
    sunColor += vec3(0.3, 0.2, 0.0) * fresnel;

    /** sunspots (darker areas) */
    float spot1 = smoothstep(0.15, 0.25, length(fragTexCoord - vec2(0.3, 0.4)));
    float spot2 = smoothstep(0.1, 0.2, length(fragTexCoord - vec2(0.7, 0.6)));
    sunColor *= mix(0.6, 1.0, spot1 * spot2);

    finalColor = vec4(sunColor, 1.0);
}
