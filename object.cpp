#include "fileio.h"
#include "object.h"

object::object() {

	vertexDataSrc = NULL;
	indicesDataSrc = NULL;
	vertBufferSize = NULL;
	indicesBufferSize = NULL;
	vboBuffer = NULL;
	iboBuffer = NULL;
	vertLoc = { NULL, };

	scaleMat = mat4(1.F);
	rotMat = mat4(1.F);
	transMat = mat4(1.F);
	modelMat = mat4(1.F);
	addModelMat = mat4(1.F);
	modelLoc = NULL;

	texObj = NULL;

	tessellationLevel = 1.F;
	surfaceNormDir = 1.F;
};
object::~object()
{
	GLuint id = this->vboBuffer;
	glDeleteBuffers(1 , &this->vboBuffer);
	printf("vbo%d has been released\n",id);

	id = this->iboBuffer;
	glDeleteBuffers(1 , &this->iboBuffer);
	printf("ibo%d has been released\n", id);

	id = this->texObj;
	glDeleteBuffers(1 , &this->texObj);
	printf("vbo%d has been released\n", id);

}

void object::ObjectLoading(const char* path)
{
	OBJECTFILE obfp;
	LoadObjectFile(path ,&obfp);
	this->vertBufferSize = obfp.vertexBufferSize;
	this->indicesBufferSize = obfp.indicesBufferSize;
	this->vertexDataSrc = obfp.vertexBuffer;
	this->indicesDataSrc = obfp.indicesBuffer;

	for (int i = 0; i < vertBufferSize; i++)
	{
		this->vertexDataSrc[i].tex_coord.s = vec3(this->vertexDataSrc[i].pos).x;
		this->vertexDataSrc[i].tex_coord.t = -vec3(this->vertexDataSrc[i].pos).y;
		this->vertexDataSrc[i].tex_coord.p = vec3(this->vertexDataSrc[i].pos).z;
	}

	glGenBuffers(1 , &this->vboBuffer);
	glBindBuffer(GL_ARRAY_BUFFER , this->vboBuffer);
	glBufferData(GL_ARRAY_BUFFER , this->vertBufferSize,this->vertexDataSrc,GL_STATIC_DRAW);

	glGenBuffers(1 , &this->iboBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , this->iboBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER , this->indicesBufferSize , this->indicesDataSrc,GL_STATIC_DRAW);
}

void object::ObjectLoading(vertex_t* vertexDataSrc, GLushort* indicesDataSrc, GLuint vertBufferSize, GLuint indicesBufferSize)
{
	this->vertBufferSize = vertBufferSize;
	this->indicesBufferSize = indicesBufferSize;
	this->vertexDataSrc = vertexDataSrc;
	this->indicesDataSrc = indicesDataSrc;
	
	for (int i = 0; i < vertBufferSize; i++)
	{
		this->vertexDataSrc[i].tex_coord.s = vec3(this->vertexDataSrc[i].pos).x;
		this->vertexDataSrc[i].tex_coord.t = -vec3(this->vertexDataSrc[i].pos).y;
		this->vertexDataSrc[i].tex_coord.p = vec3(this->vertexDataSrc[i].pos).z;
	}

	glGenBuffers(1 , &this->vboBuffer);
	glBindBuffer(GL_ARRAY_BUFFER , this->vboBuffer);
	glBufferData(GL_ARRAY_BUFFER , this->vertBufferSize,this->vertexDataSrc,GL_STATIC_DRAW);

	glGenBuffers(1 , &this->iboBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , this->iboBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER , this->indicesBufferSize , this->indicesDataSrc,GL_STATIC_DRAW);

}

void object::ObjectAttach(GLuint prog,VERTEXATTRIBNAME vertAttribName)
{
	//texture
	this->texCoordModeLoc = glGetUniformLocation(prog, "uTexMode");
	if (this->texCoordMode == 0)
	{
		this->locTexSampler = glGetUniformLocation(prog, "uTexSamplerCube");
	}
	else if (this->texCoordMode == 1)
	{
		this->locTexSampler = glGetUniformLocation(prog, "uTexSampler2D");
	}
	
	//uniform
	this->tessellationLevelLoc = glGetUniformLocation(prog , "tessellationLevel");
	this->modelLoc = glGetUniformLocation(prog,"uModel");
	this->surfaceNormDirLoc = glGetUniformLocation(prog, "uSurfaceNormDir");


	this->materialLoc.ambient = glGetUniformLocation(prog, "uMaterialVal.ambient");
	this->materialLoc.diffuse = glGetUniformLocation(prog, "uMaterialVal.diffuse");
	this->materialLoc.specular = glGetUniformLocation(prog, "uMaterialVal.specular");
	this->materialLoc.shineness = glGetUniformLocation(prog, "uMaterialVal.shineness");
	//attrib
	this->vertLoc.locPos = glGetAttribLocation(prog , vertAttribName.locPos);
	this->vertLoc.locColor = glGetAttribLocation(prog, vertAttribName.locColor);
	this->vertLoc.locNorm = glGetAttribLocation(prog, vertAttribName.locNorm);
	this->vertLoc.locTexCoord = glGetAttribLocation(prog, vertAttribName.locTexCoord);
	this->vertLoc.locMaterialID = glGetAttribLocation(prog, vertAttribName.locMaterialID);
	

	glVertexAttribFormat(this->vertLoc.locPos,4,GL_FLOAT,GL_FALSE,offsetof(vertex_t,pos));
	glVertexAttribFormat(this->vertLoc.locColor, 4, GL_FLOAT, GL_FALSE, offsetof(vertex_t,color));
	glVertexAttribFormat(this->vertLoc.locNorm, 4, GL_FLOAT, GL_FALSE, offsetof(vertex_t,norm));
	glVertexAttribFormat(this->vertLoc.locTexCoord, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t,tex_coord));
	glVertexAttribIFormat(this->vertLoc.locMaterialID, 1, GL_INT, offsetof(vertex_t,material_id));
	
	glEnableVertexAttribArray(this->vertLoc.locPos);
	glEnableVertexAttribArray(this->vertLoc.locColor);
	glEnableVertexAttribArray(this->vertLoc.locNorm);
	glEnableVertexAttribArray(this->vertLoc.locTexCoord);
	glEnableVertexAttribArray(this->vertLoc.locMaterialID);

	glVertexAttribBinding(this->vertLoc.locPos,this->vboBuffer);
	glVertexAttribBinding(this->vertLoc.locColor, this->vboBuffer);
	glVertexAttribBinding(this->vertLoc.locNorm, this->vboBuffer);
	glVertexAttribBinding(this->vertLoc.locTexCoord, this->vboBuffer);
	glVertexAttribBinding(this->vertLoc.locMaterialID, this->vboBuffer);

}

void object::ObjectUploadBMPTexture(const char* path,int idx)
{
	this->bmpTextureSrc[idx] = (GLubyte*)LoadBmp(path, &this->bmpTextureWidth, &this->bmpTextureHeight);
	cout << "load bmp " << path << "(w,h) => (" << this->bmpTextureWidth << "," << this->bmpTextureHeight << ")" << endl;
}

void object::ObjectBindTexture()
{

	glGenTextures(1, &this->texObj);
	glActiveTexture(GL_TEXTURE0);
	
	if (this->texCoordMode == 0)
	{
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		glBindTexture(GL_TEXTURE_CUBE_MAP, this->texObj);

		glTextureStorage2D(this->texObj, 1, GL_RGBA8, this->bmpTextureWidth, this->bmpTextureHeight);
		glTextureSubImage3D(this->texObj, 0, 0, 0, 0, this->bmpTextureWidth, this->bmpTextureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, this->bmpTextureSrc[0]);
		glTextureSubImage3D(this->texObj, 0, 0, 0, 1, this->bmpTextureWidth, this->bmpTextureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, this->bmpTextureSrc[1]);
		glTextureSubImage3D(this->texObj, 0, 0, 0, 2, this->bmpTextureWidth, this->bmpTextureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, this->bmpTextureSrc[2]);
		glTextureSubImage3D(this->texObj, 0, 0, 0, 3, this->bmpTextureWidth, this->bmpTextureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, this->bmpTextureSrc[3]);
		glTextureSubImage3D(this->texObj, 0, 0, 0, 4, this->bmpTextureWidth, this->bmpTextureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, this->bmpTextureSrc[4]);
		glTextureSubImage3D(this->texObj, 0, 0, 0, 5, this->bmpTextureWidth, this->bmpTextureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, this->bmpTextureSrc[5]);

	}
	else if (this->texCoordMode == 1)
	{
		
		glBindTexture(GL_TEXTURE_2D , this->texObj);
		glTextureStorage2D(this->texObj, 1, GL_RGBA8, this->bmpTextureWidth, this->bmpTextureHeight);
		glTextureSubImage2D(this->texObj ,0 ,0 ,0 ,this->bmpTextureWidth, this->bmpTextureHeight ,GL_BGR ,GL_UNSIGNED_BYTE ,this->bmpTextureSrc[0]);
		
	}
	
	glGenerateTextureMipmap(this->texObj);
	glTextureParameterf(this->texObj , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
	glTextureParameterf(this->texObj , GL_TEXTURE_MAG_FILTER , GL_NEAREST);
}

void object::ObjectDraw()
{
	this->modelMat = mat4(1.F);
	this->modelMat *= this->transMat;
	this->modelMat *= this->rotMat;
	this->modelMat *= this->scaleMat;
	this->modelMat = this->addModelMat * this->modelMat;
	glUniform4fv(this->materialLoc.ambient , 1 ,value_ptr(this->material.ambient));
	glUniform4fv(this->materialLoc.diffuse, 1, value_ptr(this->material.diffuse));
	glUniform4fv(this->materialLoc.specular, 1, value_ptr(this->material.specular));
	glUniform1fv(this->materialLoc.shineness, 1, &this->material.shineness);
	glUniform1i(this->locTexSampler, 0);

	glUniformMatrix4fv(this->modelLoc,1,NULL,value_ptr(this->modelMat));
	glBindVertexBuffer(this->vboBuffer,this->vboBuffer,0,sizeof(vertex_t));
	glUniform1f(this->tessellationLevelLoc, this->tessellationLevel);
	glUniform1f(this->surfaceNormDirLoc , this->surfaceNormDir);


	glUniform1i(this->texCoordModeLoc, this->texCoordMode);
	if (this->texCoordMode == 0)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->texObj);
	}
	else if(this->texCoordMode == 1)
	{
		glBindTexture(GL_TEXTURE_2D, this->texObj);
	}

	
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawElements(GL_PATCHES , this->indicesBufferSize, GL_UNSIGNED_SHORT, 0);
}

void object::ObjectSetMaterial(MATERIAL material)
{
	this->material = material;
}

void object::ObjectScale(vec3 v)
{
	this->scaleMat = scale(this->scaleMat,v);
}

void object::ObjectRotate(float angle, vec3 v)
{
	this->rotMat = rotate(this->rotMat, angle, v);
}

void object::ObjectTranslate(vec3 v)
{
	this->transMat = translate(this->transMat, v);
}

void object::ObjectAddModelProductFront(mat4 m)
{
	this->addModelMat = m * this->addModelMat;
}

void object::ObjectAddModelProductBack(mat4 m)
{
	this->addModelMat = this->addModelMat * m;
}

void object::ObjectSetTessellationLevel(GLfloat level)
{
	this->tessellationLevel = level;
	glUniform1f(this->tessellationLevelLoc , this->tessellationLevel);
}

void object::ObjectSetSurfaceNormDir(GLfloat surfaceNormDir)
{
	this->surfaceNormDir = surfaceNormDir;

}

void object::ObjectSetTexCoordMode(GLint texCoordMode)
{
	this->texCoordMode = texCoordMode;
	glUniform1i(this->texCoordModeLoc , this->texCoordMode);
}