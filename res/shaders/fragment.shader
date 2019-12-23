#version 330

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_TexCoord;

void main() {
    vec4 tex_Color = texture(u_Texture, v_TexCoord);
    color = tex_Color;
}