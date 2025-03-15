#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include "ext_header.h"
#include "type.h"

constexpr int LIGHT_ID_0 = '0';
constexpr int LIGHT_ID_1 = '1';
constexpr int LIGHT_ID_2 = '2';
constexpr int LIGHT_ID_3 = '3';
constexpr int LIGHT_ID_4 = '4';
constexpr int LIGHT_ID_5 = '5';
constexpr int LIGHT_ID_6 = '6';
constexpr int LIGHT_ID_7 = '7';
constexpr int LIGHT_ID_8 = '8';
constexpr int LIGHT_ID_9 = '9';


class light
{
public:
	light();
	~light();
	void SetElement(LIGHT element);
	LIGHT GetElement();

	void UpdatePos(vec4 pos);
	void UpdateAmbient(vec4 ambient);
	void UpdateSpecular(vec4 specular);
	void UpdateAtt(vec4 att);

	void BindingLight(GLuint prog,char LIGHT_ID);
	void AttachLight();
private:
	char lightBufUniformNamePs[30] = "lightBuf[0].pos";
	char lightBufUniformNameAb[30] = "lightBuf[0].ambient";
	char lightBufUniformNameDf[30] = "lightBuf[0].diffuse";
	char lightBufUniformNameSc[30] = "lightBuf[0].specular";
	char lightBufUniformNameAt[30] = "lightBuf[0].att";
	char lightBufUniformNameActive[30] = "lightBuf[0].activeLight";
	LIGHT element;
	LIGHTLOC lightLoc;
	char light_id;

};

void ClearLightBuf(GLuint prog);


#endif // !LIGHT_H
