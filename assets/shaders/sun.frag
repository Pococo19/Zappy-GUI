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

    vec3 core_color = vec3(1.0, 0.95, 0.8);      //<< hot white-yellow
    vec3 inner_color = vec3(1.0, 0.85, 0.4);     //<< bright yellow
    vec3 middle_color = vec3(1.0, 0.6, 0.2);     //<< orange
    vec3 outer_color = vec3(1.0, 0.3, 0.1);      //<< red-orange
    vec3 corona_color = vec3(1.0, 0.4, 0.0);     //<< deep red

    /** gradient radial */
    float gradient_factor1 = smoothstep(0.0, 0.3, radius);
    float gradient_factor2 = smoothstep(0.3, 0.6, radius);
    float gradient_factor3 = smoothstep(0.6, 0.9, radius);
    
    vec3 sun_color = mix(core_color, inner_color, gradient_factor1);
    sun_color = mix(sun_color, middle_color, gradient_factor2);
    sun_color = mix(sun_color, outer_color, gradient_factor3);

    float corona_intensity = smoothstep(0.4, 0.7, radius) * (1.0 - smoothstep(0.7, 1.0, radius));
    sun_color = mix(sun_color, corona_color, corona_intensity * 0.3);


    /** pulsation */
    float pulse = 0.8 + 0.2 * sin(time * 2.0);
    sun_color *= pulse;

    /** chips at the edge */
    float fresnel = 1.0 - dot(normalize(fragNormal), normalize(viewPos - fragPosition));
    fresnel = pow(fresnel, 2.0);
    sun_color += vec3(0.3, 0.2, 0.0) * fresnel;

    /** sunspots (darker areas) */
    float spot1 = smoothstep(0.15, 0.25, length(fragTexCoord - vec2(0.3, 0.4)));
    float spot2 = smoothstep(0.1, 0.2, length(fragTexCoord - vec2(0.7, 0.6)));
    sun_color *= mix(0.6, 1.0, spot1 * spot2);

    finalColor = vec4(sun_color, 1.0);
}
