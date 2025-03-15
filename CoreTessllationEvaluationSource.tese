#version 450 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
uniform float uSurfaceNormDir;
uniform int uTexMode;

out vec4 vTessGeometryPosition;
out vec3 vTessTexCoord;
out vec2 vTessTexCoord2D;
out vec4 vTessNorm;


layout (triangles) in;

void Init()
{
	vTessGeometryPosition = vec4(1.F);
	vTessTexCoord = vec3(1.F);
	vTessTexCoord2D = vec2(1.F);
	vTessNorm = vec4(1.F);
}

vec2 SphericalCoordnate(vec4 in_pos)
{

	vec4 pos = vec4(normalize(in_pos.xyz) , in_pos.w);	
	if(pos.z < 0.F)
		return vec2( (atan(-pos.x , -pos.z) + 3.141592F)/(3.1415924F)/2.F , 0.5F - asin(pos.y)/(3.141592F) );
	else
		return vec2( atan(pos.x , pos.z)/(3.141592F)/2.F , 0.5F - asin(pos.y )/(3.141592F) );
}

vec3 NormalCoordnadte(vec4 pos)
{
	return normalize(pos.xyz) * vec3(1.F , -1.F ,1.F);
}



void main(void)
{
	Init();

	vec4 pos =  (gl_TessCoord.x * gl_in[0].gl_Position) +
				(gl_TessCoord.y * gl_in[1].gl_Position) +
				(gl_TessCoord.z * gl_in[2].gl_Position);
			
	
	if(uTexMode == 0)
	{
		vTessTexCoord = NormalCoordnadte(pos);

	}
	else if(uTexMode == 1)
	{
		vTessTexCoord2D = SphericalCoordnate(pos);
	}
	
	gl_Position =uProj*uView*uModel*vec4( normalize(pos.xyz) , 1.F);
	vTessNorm = transpose(inverse(uModel))*vec4(normalize(pos.xyz*uSurfaceNormDir),1.F);
	vTessGeometryPosition = uModel* vec4(normalize(pos.xyz) , pos.w);
	 

}