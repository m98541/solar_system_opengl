#version 450 core
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout (location = 0)in vec4 aPos;
layout (location = 1)in vec4 aColor;
layout (location = 2)in vec4 norm;
//loc 3 은 의도적으로 생략 (책에서 생략)
layout (location = 4)in vec3 aTexCoord;
layout (location = 5)in int material_id;


out vec4 vColor;
out vec4 vNorm;
out vec3 vTexCoord;
out vec4 vGeometryPosition;

void main(void)
{
	gl_Position = aPos;

	vNorm = transpose(inverse(uModel))*vec4(normalize(aPos.xyz),1.F);
	vGeometryPosition = uModel*aPos;
	vColor = aColor;//vec4(1.F ,1.F ,1.F ,1.F);
	vTexCoord = aTexCoord;
}