#version 450

layout(std140, binding = 0) uniform Mixer {
    float strength;
    vec3 mix_color;
};

in vec3 vertex_color;
layout(location=0) out vec4 vFragColor;

void main() {
    vFragColor = vec4(vertex_color, 1.0);

    vec3 mixedColor = mix(vFragColor.rgb, mix_color, strength);
    vFragColor = vec4(mixedColor, vFragColor.a);
}