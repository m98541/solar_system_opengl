#version 450 core

struct LIGHT{
	vec4 pos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 att;
	bool activeLight;
};

struct LIGHT_ELEMENT
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct material{
	 vec4 ambient;
	 vec4 diffuse;
	 vec4 specular;
	 float shineness;
};



uniform LIGHT uLightVal;
uniform material uMaterialVal;

uniform LIGHT lightBuf[10];

uniform uint lightCount;

uniform vec3 uCamPos;

uniform samplerCube uTexSamplerCube;
uniform sampler2D uTexSampler2D;

uniform int uTexMode;

in vec4 vGeometryPosition;
in vec4 vColor;
in vec4 vNorm;
in vec3 vTexCoord;

in vec4 vTessGeometryPosition;
in vec3 vTessTexCoord;
in vec2 vTessTexCoord2D;
in vec4 vTessNorm;

out vec4 FragColor;

LIGHT_ELEMENT lightSum = {
		vec4(0.F , 0.F ,0.F ,0.F),
		vec4(0.F , 0.F ,0.F ,0.F),
		vec4(0.F , 0.F ,0.F ,0.F)
};

LIGHT_ELEMENT LightFunc(vec3 norm,LIGHT light)
{
	LIGHT_ELEMENT reLight = {
		vec4(0.F , 0.F ,0.F ,0.F),
		vec4(0.F , 0.F ,0.F ,0.F),
		vec4(0.F , 0.F ,0.F ,0.F),
	};
	if(!light.activeLight) return reLight;
	
	vec3 N = normalize(norm);
	vec3 L = normalize(light.pos.xyz - vTessGeometryPosition.xyz) ;
	vec3 V = normalize(uCamPos- vTessGeometryPosition.xyz );
	vec3 R = normalize(2*N*dot(N,L)-L);



	reLight.ambient = light.ambient * uMaterialVal.ambient;

	float d = length(light.pos.xyz  - vTessGeometryPosition.xyz);

	float denom = light.att.x + light.att.y*d + light.att.z*d*d;

	reLight.diffuse = max(dot(L,N), 0.F)*light.diffuse*uMaterialVal.diffuse/denom;

	reLight.specular = max(dot(L,V),0.F)*pow(max(dot(R,V), 0.F) , uMaterialVal.shineness )*light.specular*uMaterialVal.specular/denom;

	return  reLight;

}


void main(void)
{
	for(int i = 0; i < 10; i++)
	{
		lightSum.ambient += LightFunc(vTessNorm.xyz,lightBuf[i]).ambient;
		lightSum.specular += LightFunc(vTessNorm.xyz,lightBuf[i]).specular;
		lightSum.diffuse += LightFunc(vTessNorm.xyz,lightBuf[i]).diffuse;
	}
	lightSum.ambient.xyz = lightSum.ambient.xyz;
	lightSum.diffuse.xyz = min(lightSum.diffuse.xyz , vec3(1.F ,1.F ,1.F));
	lightSum.ambient.w = 1.F;
	lightSum.specular.w = 1.F;
	lightSum.diffuse.w = 1.F;



	vec4 lightColor = lightSum.ambient + lightSum.diffuse + lightSum.specular;

	
	vec4 texColor = vec4(1.F ,1.F ,1.F ,1.F);
	


	if(uTexMode == 0)
	{
		texColor = texture(uTexSamplerCube , vTessTexCoord);
	}
	else if(uTexMode == 1)
	{
		texColor = texture(uTexSampler2D , vTessTexCoord2D);
	}

	
	FragColor =  texColor * lightColor;//vec4(1.F ,1.F ,1.F ,1.F);
	
}