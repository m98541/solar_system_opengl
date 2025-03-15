#include "light.h"

light::light()
{
	this->element ={
		vec4(0.F),
		vec4(0.F),
		vec4(0.F),
		vec4(0.F),
		vec4(0.F),
		false
	};

	this->lightLoc = {0,0,0,0};

}

light::~light()
{
	this->element = {
		vec4(0.F),
		vec4(0.F),
		vec4(0.F),
		vec4(0.F),
		vec4(0.F),
		false
	};

	this->AttachLight();

	cout << this->light_id << "is being eliminated" << endl;
}

void light::SetElement(LIGHT element)
{
	this->element = element;
}
LIGHT light::GetElement()
{
	return this->element;
}

void light::UpdatePos(vec4 pos)
{
	this->element.pos = pos;
}
void light::UpdateAmbient(vec4 ambient)
{
	this->element.ambient = ambient;
}
void light::UpdateSpecular(vec4 specular)
{
	this->element.specular = specular;
}
void light::UpdateAtt(vec4 att)
{
	this->element.att = att;
}

void light::BindingLight(GLuint prog,char LIGHT_ID)
{
	this->light_id = LIGHT_ID;
	lightBufUniformNamePs[9] = LIGHT_ID;
	lightBufUniformNameAb[9] = LIGHT_ID;
	lightBufUniformNameDf[9] = LIGHT_ID;
	lightBufUniformNameSc[9] = LIGHT_ID;
	lightBufUniformNameAt[9] = LIGHT_ID;
	lightBufUniformNameActive[9] = LIGHT_ID;

	this->lightLoc.pos = glGetUniformLocation(prog , lightBufUniformNamePs);
	this->lightLoc.ambient = glGetUniformLocation(prog, lightBufUniformNameAb);
	this->lightLoc.diffuse = glGetUniformLocation(prog, lightBufUniformNameDf);
	this->lightLoc.specular = glGetUniformLocation(prog, lightBufUniformNameSc);
	this->lightLoc.att = glGetUniformLocation(prog, lightBufUniformNameAt);
	this->lightLoc.active = glGetUniformLocation(prog, lightBufUniformNameActive);
}
void light::AttachLight()
{
	glUniform4fv(this->lightLoc.pos, 1, value_ptr(this->element.pos));
	glUniform4fv(this->lightLoc.ambient, 1, value_ptr(this->element.ambient));
	glUniform4fv(this->lightLoc.diffuse, 1, value_ptr(this->element.diffuse));
	glUniform4fv(this->lightLoc.specular, 1, value_ptr(this->element.specular));
	glUniform4fv(this->lightLoc.att, 1, value_ptr(this->element.att));
	glUniform1i(this->lightLoc.active,this->element.active);
}

void ClearLightBuf(GLuint prog)
{
	light initLight;
	for (int i = 0; i < 10; i++) {
		initLight.BindingLight(prog, '0' + i);
		initLight.AttachLight();
	}
	initLight.~light();
}