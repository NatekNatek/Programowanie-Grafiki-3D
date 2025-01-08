#version 450

uniform sampler2D map_Kd; 


in vec3 vertex_color;
in vec2 texture_coordinates;
layout(location=0) out vec4 vFragColor;

layout(std140, binding=0) uniform KdMaterial {
    vec4 Kd;
    bool use_vertex_color; 
    bool use_map_Kd; 
};



void main() {

    vec4 base_color = Kd;

    if (use_vertex_color) {
        base_color *= vec4(vertex_color, 0.0);
    }
    
    vec4 texture_color = texture(map_Kd, texture_coordinates);
    if (use_map_Kd) {
        base_color *= texture_color;
    }

    vFragColor = base_color;
 
}