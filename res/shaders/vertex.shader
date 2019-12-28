#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

out vec4 v_Color;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    mat4 u_MVP = u_Projection * u_View * u_Model;
    gl_Position = u_MVP * vec4(position, 1.0);

    v_Color = color;

    // non-uniform scaling
    v_Normal = mat3(transpose(inverse(u_Model))) * normal;

    v_FragPos = (u_Model * vec4(position, 1.0)).xyz;
}