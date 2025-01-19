#version 450

#define INV_PI 0.31830988618 // 1 / π

uniform sampler2D map_Kd; 

in vec 4 Ka;
in vec3 vertex_color;
in vec2 texture_coordinates;
in vec3 vertex_normal_vs
in vec3 vertex_position_vs;

layout(location=0) out vec4 vFragColor;

layout(std140, binding=0) uniform KdMaterial {
    vec4 Kd;
    bool use_vertex_color; 
    bool use_map_Kd; 
};

const int MAX_POINT_LIGHTS = 16;

layout (std140, binding = 2) uniform Lights {
  vec3 ambient;
  int n_lights;
  PointLight lights[MAX_POINT_LIGHTS];
};

struct PointLight {
  vec3 position;
  float radius;
  vec3 color;
  float intensity;
 };


void main() {

   vec3 normal = normalize(vertex_normal_vs);
   if (!gl_FrontFacing) {
    normal = -normal;
  }
   vec3 fragColor = Ka.rgb * vec3(0.25, 0.25, 0.25);

    for (int i = 0; i < num_lights; ++i) {

        vec3 light_direction = normalize(lights[i].position - vertex_position_vs)
        float light_distance = length(light_direction);
        light_direction = normalize(light_direction);

        float diffuse = max(dot(normal, light_direction), 0.0);

        float r = max(lights[i].radius, light_distance);
        float attenuation = 1.0 / (r * r);
       
        fragColor += INV_PI * color.rgb * lights[i].color * lights[i].intensity * diffuse * attenuation;
    }

    vFragColor = vec4(fragColor, Kd.a);
 
}