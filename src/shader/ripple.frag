#version 450 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform float time;
uniform float timeSpeed;
uniform float heightScale;
uniform vec2 rippleCenter;
uniform sampler2D u_Texture;

void main()
{
    vec2 uv = v_TexCoord;
    vec2 pos = uv - rippleCenter;
    float acTime = time * timeSpeed;
    float r = length(pos);
    float rippleRadius = 0.5 * acTime;

    float intensity = 0.0;
    if (r < rippleRadius)
    {
        intensity = 0.5 * heightScale * exp(-0.675 * acTime) * (sin(100 * r - acTime)) / r;
    }

    vec4 baseColor = texture(u_Texture, uv);
    baseColor.rgb += intensity;
    FragColor = vec4(baseColor.rgb, 1.0);
}
