#version 430

layout (location=0) in vec3 vertPos;
layout (location=1) in vec3 vertNormal;

out vec4 varyingColor;

struct PositionalLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec4 globalAmbient; 
uniform PositionalLight light; 
uniform Material material; 
uniform mat4 mv_matrix; 
uniform mat4 proj_matrix; 
uniform mat4 norm_matrix; // 用来变换法向量

void main(void)
{
    vec4 color;

    vec4 P = mv_matrix * vec4(vertPos, 1.0);
    vec3 N = normalize((norm_matrix * vec4(vertNormal, 1.0)).xyz);
    vec3 L = normalize(light.position - P.xyz);

    vec3 V = normalize(-P.xyz);
    vec3 R = reflect(-L, N);

    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz; 
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L), 0.0); 
    vec3 specular = pow(max(dot(R,V), 0.0f), material.shininess)
		* material.specular.xyz * light.specular.xyz;

    varyingColor = vec4((ambient + diffuse + specular), 1.0);
    gl_Position = proj_matrix * mv_matrix * vec4(vertPos, 1.0);
}