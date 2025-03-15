#ifndef OBJECT_H
#define OBJECT_H

#include "ext_header.h"
#include "type.h"


class object
{
public:
	object();
	~object();
	void ObjectLoading(const char* path);
	void ObjectLoading(vertex_t* vertexDataSrc, GLushort* indicesDataSrc, GLuint vertBufferSize, GLuint indicesBufferSize);
	void ObjectAttach(GLuint prog,VERTEXATTRIBNAME vertAttribName);
	void ObjectUploadBMPTexture(const char* path,int idx);
	
	void ObjectSetSurfaceNormDir(GLfloat surfaceNormDir);
	void ObjectBindTexture();
	void ObjectDraw();
	

	void ObjectScale(vec3 v);
	void ObjectRotate(float angle,vec3 v);
	void ObjectTranslate(vec3 v);
	void ObjectAddModelProductFront(mat4 m);
	void ObjectAddModelProductBack(mat4 m);

	void ObjectSetMaterial(MATERIAL material);

	void ObjectSetTessellationLevel(GLfloat level);

	void ObjectSetTexCoordMode(GLint texCoordMode);


private:
	vertex_t* vertexDataSrc;
	GLushort* indicesDataSrc;

	GLuint vertBufferSize;
	GLuint indicesBufferSize;
	
	GLuint texObj;
	GLuint vboBuffer;
	GLuint iboBuffer;
	
	GLuint locTexSampler;
	GLubyte* bmpTextureSrc[6];
	GLuint bmpTextureWidth;
	GLuint bmpTextureHeight;

	
	VERTEXATTRIBLOC vertLoc;
	MATERIAL material;
	MATERIALLOC materialLoc;
	GLuint tessellationLevelLoc;

	mat4 scaleMat;
	mat4 rotMat;
	mat4 transMat;

	mat4 addModelMat;
	mat4 modelMat;
	GLuint modelLoc;

	GLfloat tessellationLevel;
	GLfloat surfaceNormDir;
	GLuint surfaceNormDirLoc;

	GLuint texCoordModeLoc;
	GLint texCoordMode;


};

#endif // !OBJECT_H
