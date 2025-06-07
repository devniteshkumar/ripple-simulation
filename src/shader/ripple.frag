#version 450 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform float time;
uniform float heightScale;
uniform vec2 rippleCenter;
uniform sampler2D u_Texture;

void main()
{
    vec2 uv = v_TexCoord;
    vec2 pos = uv - rippleCenter;
    float r = length(pos);

    float intensity = 0.0;
    if (r > 0.001)
    {
        intensity = 0.5 * heightScale * exp(-0.675 * time) * (sin(100 * r - time)) / r;
    }

    vec4 baseColor = texture(u_Texture, uv);
    baseColor.rgb += intensity;
    FragColor = vec4(baseColor.rgb, 1.0);
}
