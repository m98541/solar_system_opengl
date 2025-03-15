#ifndef TYPE_H
#define TYPE_H
#include "ext_header.h"

typedef struct _vertex_t
{	
	vec4 pos;
	vec4 color;
	vec4 norm;
	vec3 tex_coord;
	int material_id;
}vertex_t;


typedef struct _vertex_attrib_loc_t
{
	GLuint locPos;
	GLuint locColor;
	GLuint locNorm;
	GLuint locTexCoord;
	GLuint locMaterialID;

}VERTEXATTRIBLOC;

typedef struct _vertex_attrib_name_t
{
	const char* locPos;
	const char* locColor;
	const char* locNorm;
	const char* locTexCoord;
	const char* locMaterialID;
}VERTEXATTRIBNAME;


typedef struct _object_file_t
{
	GLuint vertexBufferSize;
	GLuint indicesBufferSize;
	vertex_t* vertexBuffer;
	GLushort* indicesBuffer;
	

}OBJECTFILE;


typedef struct light_t
{
	vec4 pos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 att;
	bool active;
}LIGHT;


typedef struct material_t
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shineness;
}MATERIAL;

typedef struct light_loc_t
{
	GLuint pos;
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
	GLuint att;
	GLuint active;
}LIGHTLOC;


typedef struct material_loc_t
{
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
	GLuint shineness;
}MATERIALLOC;

#endif // !TYPE_H