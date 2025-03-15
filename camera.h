#ifndef CAMERA_H
#define CAMERA_H
#include "ext_header.h"
#include "type.h"
class camera
{
public:
	vec3 camPos;
	vec3 camAt;
	vec3 camUp;

	float camFovy;
	float camAspect;
	float camZNear;
	float camZFar;
	vec2 tilt;

	camera();
	~camera();
	void CamUpdateView();
	void CamUpdateProj();
	//카메라 선택
	void CamSelect(GLuint prog);
private:
	//Set matView lookat
	void CamViewingLookAt(vec3 eye, vec3 at, vec3 up);
	//Set matProj projection
	void CamFrustumShear(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat frustumNear, GLfloat frustumFar);
	void CamPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, vec2 tilt);

	mat4 matView;
	mat4 matProj;
	
	bool camActive;
	GLuint camPosLoc;
	GLuint viewLoc;
	GLuint projLoc;
};

#endif // !CAMERA_H
