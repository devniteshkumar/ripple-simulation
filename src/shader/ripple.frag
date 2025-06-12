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
    float r = length(pos);
    float acTime = time * timeSpeed;
    vec2 dir = (r > 1e-4) ? normalize(pos) : vec2(0.0);
    float ripple = sin(20.0 * r - 6.0 * acTime) * heightScale * exp(-decay * r) * exp(-0.4 * decay * acTime);
    vec2 displacedUV = uv + dir * ripple;
    vec4 baseColor = texture(u_Texture, displacedUV);
    FragColor = vec4(baseColor.rgb, 1.0);
}
