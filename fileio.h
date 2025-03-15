#ifndef FILEIO_H
#define FILEIO_H
#include "ext_header.h"
#include "type.h"

const char* FileLoad(const char* fileName);

void SaveObjectFile(const char* fileName, OBJECTFILE* objectFile);

void LoadObjectFile(const char* fileName,OBJECTFILE* objectFile);

const unsigned char* LoadBmp(const char* path, unsigned int* width, unsigned int* height);


#endif // !FILEIO_H
