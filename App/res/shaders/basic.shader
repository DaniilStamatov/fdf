#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 FragPos;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;
void main() {
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
    FragPos = position; 
};

#shader fragment
#version 330 core

in vec3 FragPos;
out vec4 color;

uniform float u_MaxY; 
void main() {
    float normalizedY = FragPos.y / u_MaxY; 
    normalizedY = clamp(normalizedY, 0.0, 1.0); 

    color = vec4(1.0, normalizedY, 1.0, 1.0);
}