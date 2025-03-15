#include "camera.h"

camera::camera()
{
	//default set
	float defaultFovy = (3.141592F / 180.f) * 60.F;
	float defaultAspect = 1920.F / 1080.F;
	
	this->CamViewingLookAt(vec3(0.F, 0.F, -1.F), vec3(0.F, 0.F, 0.F), vec3(0.F, 1.F, 0.F));

	this->CamPerspective(defaultFovy,defaultAspect, 0.1F ,2.F,vec2(0.F ,0.F));
}

camera::~camera() 
{}

int cnt = 0;
void camera::CamViewingLookAt(vec3 eye, vec3 at, vec3 up)
{
	vec3 p = eye;
	vec3 n = -normalize(at - eye);
	vec3 u = normalize(cross(up, n));
	vec3 v = cross(n, u);

	mat4 m = {
		vec4(u.x, v.x , n.x , 0.F),
		vec4(u.y, v.y , n.y , 0.F),
		vec4(u.z, v.z , n.z , 0.F),
		vec4(-dot(u,p) , -dot(v,p) , -dot(n,p) , 1.F)
	};

	this->camPos = eye;
	this->camAt = at;
	this->camUp = up;

	this->matView = m;
}

void camera::CamFrustumShear(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat frustumNear, GLfloat frustumFar)
{
	mat4 m = {
		vec4((2 * frustumNear) / (right - left)  , 0.F , 0.F , 0.F),
		vec4(0.F , (2 * frustumNear) / (top - bottom) , 0.F , 0.F),
		vec4((right + left) / (right - left) , (top + bottom) / (top - bottom) , -(frustumFar + frustumNear) / (frustumFar - frustumNear) , -1.F),
		vec4(0.F , 0.F , -(2 * frustumFar * frustumNear) / (frustumFar - frustumNear) , 0.F)

	};
	this->matProj = m;
}

void camera::CamPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, vec2 tilt)
{
	GLfloat top = zNear * tanf(fovy / 2.F);
	GLfloat right = aspect * top;
	GLfloat bottom = -top;
	GLfloat left = -right;
	this->camFovy = fovy;
	this->camAspect = aspect;
	this->tilt = tilt;

	this->CamFrustumShear(left + tilt.x, right + tilt.x, bottom + tilt.y, top + tilt.y, zNear, zFar);
}

void camera::CamSelect(GLuint prog)
{
	
	this->viewLoc = glGetUniformLocation(prog , "uView");
	this->projLoc = glGetUniformLocation(prog , "uProj");
	this->camPosLoc = glGetUniformLocation(prog, "uCamPos");
	glUniformMatrix4fv(this->viewLoc,1,GL_FALSE,value_ptr(this->matView));
	glUniformMatrix4fv(this->projLoc,1,GL_FALSE,value_ptr(this->matProj));
	glUniform3fv(this->camPosLoc , 1 ,value_ptr(this->camPos));
}

void camera::CamUpdateView()
{
	this->CamViewingLookAt(this->camPos,this->camAt,this->camUp);
	glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, value_ptr(this->matView));
}

void camera::CamUpdateProj()
{	
	this->CamPerspective(this->camFovy,this->camAspect,this->camZNear,this->camZFar,this->tilt);
	glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, value_ptr(this->matProj));
}