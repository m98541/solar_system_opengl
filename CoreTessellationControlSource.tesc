#version 450 core

uniform float tessellationLevel;


layout (vertices = 3) out;

void main(void)
{

	gl_TessLevelInner[0] = 1.F * tessellationLevel;
	gl_TessLevelOuter[0] = 1.F * tessellationLevel;
	gl_TessLevelOuter[1] = 1.F * tessellationLevel;
	gl_TessLevelOuter[2] = 1.F * tessellationLevel;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

}