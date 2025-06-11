#version 450 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform float time;
uniform float timeSpeed;
uniform float heightScale;
uniform vec2 rippleCenter;
uniform sampler2D u_Texture;
uniform float decay;

void main()
{
    vec2 uv = v_TexCoord;
    vec2 pos = uv - rippleCenter;
    float acTime = time * timeSpeed;
    float r = length(pos);
    vec2 dir = normalize(pos);

    float ripple = sin(12.0 * r - 4.0 * acTime) * heightScale * exp(-decay * acTime);
    vec2 displacedUV = uv + dir * ripple;
    vec4 baseColor = texture(u_Texture, displacedUV);
    FragColor = vec4(baseColor.rgb, 1.0);
}
