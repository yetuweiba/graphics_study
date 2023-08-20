#version 430

in vec3 varyingNormal; 
in vec3 varyingLightDir; 
in vec3 varyingVertPos;
out vec4 fragColor;

//  uniforms match those in the vertex shader,
//  but are not used directly in this fragment shader

struct PositionalLight
{	vec4 ambient;  
	vec4 diffuse;  
	vec4 specular;  
	vec3 position;
};

struct Material
{	vec4 ambient;  
	vec4 diffuse;  
	vec4 specular;  
	float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;	 
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;

//  interpolate lighted color
// (interpolation of gl_Position is automatic)

void main(void)
{
	// 正规化光照向量、法向量、视觉向量
	vec3 L = normalize(varyingLightDir); 
	vec3 N = normalize(varyingNormal); 
	vec3 V = normalize(-varyingVertPos);

	 // 计算光照向量基于 N 的反射向量
	vec3 R = normalize(reflect(-L, N)); 
	// 计算光照与平面法向量间的角度
	float cosTheta = dot(L,N); 
	// 计算视觉向量与反射光向量的角度
	float cosPhi = dot(V,R);

	 vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz; 
 		vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta,0.0); 
 		vec3 specular = 
 light.specular.xyz * material.specular.xyz * pow(max(cosPhi,0.0), material.shininess);

 fragColor = vec4((ambient + diffuse + specular), 1.0);
}
