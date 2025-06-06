#version 330 core
out vec4 FragColor;

in vec2 v_TexCoord;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, v_TexCoord);
    FragColor = texColor;
}
