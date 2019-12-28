#version 330

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_FragPos;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

struct Material {
    float specularIntensity;
    float shininess;
};

uniform DirectionalLight u_DirectionalLight;
uniform Material u_Material;
uniform vec3 u_EyePosition;

void main() {
    vec4 ambientColor = u_DirectionalLight.ambientIntensity * vec4(u_DirectionalLight.color, 1.0f);

    float diffuseFactor = max(dot(normalize(v_Normal), normalize(u_DirectionalLight.direction)), 0.0f);
    vec4 diffuseColor =  vec4(u_DirectionalLight.color, 1.0f) * u_DirectionalLight.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    if (diffuseFactor > 0.0f) {
        vec3 fragToEye = normalize(u_EyePosition - v_FragPos);
        vec3 reflectedVertex = normalize(reflect(u_DirectionalLight.direction, normalize(v_Normal)));

        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor > 0.0f) {
            specularFactor = pow(specularFactor, u_Material.shininess);
            specularColor = vec4(u_DirectionalLight.color * u_Material.specularIntensity * specularFactor, 1.0f);
        }
    }

    color = v_Color * (ambientColor + diffuseColor + specularColor);
}