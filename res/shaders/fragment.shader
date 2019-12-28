#version 330

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

in vec4 v_Color;
in vec3 v_Normal;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

uniform DirectionalLight u_DirectionalLight;

void main() {
    vec4 ambientColor = u_DirectionalLight.ambientIntensity * vec4(u_DirectionalLight.color, 1.0f);

    float diffuseFactor = max(dot(normalize(v_Normal), normalize(u_DirectionalLight.direction)), 0.0f);
    vec4 diffuseColor =  vec4(u_DirectionalLight.color, 1.0f) * u_DirectionalLight.diffuseIntensity * diffuseFactor;

    color = v_Color * (ambientColor + diffuseColor);
}