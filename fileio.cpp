#define _CRT_SECURE_NO_WARNINGS
#include "fileio.h"


const char* FileLoad(const char* fileName)
{
	
	FILE* fp = fopen(fileName, "r");
	
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		size_t len = ftell(fp);
		char* buf = (char*)malloc(sizeof(char) * (len + 4));
		rewind(fp);

		if (buf != NULL)
		{
			len = fread(buf, 1, len, fp);

			buf[len] = '\0';
			fclose(fp);
			return buf;
		}
		else
			return (const char*)0;
	}
	else
		return (const char*)0;
	
	
	
}

void SaveObjectFile(const char* fileName, OBJECTFILE* objectFile)
{
	FILE* fp = fopen(fileName, "wb");
	if (fp == NULL)
	{
		puts("파일 생성불가");
		return;
	}
	fwrite(&objectFile->vertexBufferSize,sizeof(GLuint),1,fp);
	fwrite(&objectFile->indicesBufferSize, sizeof(GLuint),1,fp);
	fwrite(objectFile->vertexBuffer, sizeof(vertex_t), objectFile->vertexBufferSize, fp);
	fwrite(objectFile->indicesBuffer, sizeof(GLushort), objectFile->indicesBufferSize, fp);
	fclose(fp);
}


void LoadObjectFile(const char* fileName, OBJECTFILE* objectFile)
{
	FILE* fp = fopen(fileName , "rb");
	fread(&objectFile->vertexBufferSize, sizeof(GLuint), 1, fp);
	fread(&objectFile->indicesBufferSize, sizeof(GLuint), 1, fp);

	objectFile->vertexBuffer = (vertex_t*)malloc(sizeof(vertex_t) * objectFile->vertexBufferSize);
	objectFile->indicesBuffer = (GLushort*)malloc(sizeof(vertex_t) * objectFile->indicesBufferSize);
	fread(objectFile->vertexBuffer, sizeof(vertex_t), objectFile->vertexBufferSize, fp);
	fread(objectFile->indicesBuffer, sizeof(GLushort), objectFile->indicesBufferSize, fp);
	fclose(fp);
}



const unsigned char* LoadBmp(const char* path,unsigned int* width,unsigned int* height)
{
	HANDLE hFile;
	DWORD fileSize, dwRead;

	BITMAPFILEHEADER* fh = NULL;
	BITMAPINFOHEADER* ih = NULL;

	unsigned char* pRaster;

	hFile = CreateFileA(path ,GENERIC_READ ,0 ,NULL ,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL);

	if (hFile == INVALID_HANDLE_VALUE)return NULL;
	
	fileSize = GetFileSize(hFile , NULL);
	fh = (BITMAPFILEHEADER*)malloc(fileSize);
	ReadFile(hFile ,fh ,fileSize ,&dwRead ,NULL);
	CloseHandle(hFile);

	unsigned int len = fileSize - (fh->bfOffBits);
	pRaster = (unsigned char*)malloc(len);
	memcpy(pRaster, (BYTE*)fh + fh->bfOffBits, len);



	ih = (BITMAPINFOHEADER*)((PBYTE)fh + sizeof(BITMAPFILEHEADER));
	*width = ih->biWidth;
	*height = ih->biHeight;

	free(fh);
	return pRaster;

}