#version 330

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec4 v_color;

void main() {
    color = v_color;
}