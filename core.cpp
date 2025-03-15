#include "core.h"

void DurTime(const char* message)
{
	system_clock::time_point lastTime = curTime;
	cout << endl << message;
	curTime = system_clock::now();
	durTime = duration_cast<milliseconds>(curTime-lastTime);
	cout << endl << "check time:" << durTime.count()<<"ms"<< endl << endl;
	lastTime = system_clock::now();
}

void DataInit()
{
	//init map
	mapBox.ObjectLoading("cubeSrc.object");
	mapBox.ObjectUploadBMPTexture("texture/mapbox_0.bmp", 0);
	mapBox.ObjectUploadBMPTexture("texture/mapbox_1.bmp", 1);
	mapBox.ObjectUploadBMPTexture("texture/mapbox_2.bmp", 2);
	mapBox.ObjectUploadBMPTexture("texture/mapbox_3.bmp", 3);
	mapBox.ObjectUploadBMPTexture("texture/mapbox_4.bmp", 4);
	mapBox.ObjectUploadBMPTexture("texture/mapbox_5.bmp", 5);
	mapBox.ObjectSetSurfaceNormDir(-1.F);
	mapBox.ObjectSetTexCoordMode(TEXCOORD_MODE_NORMAL);
	mapBox.ObjectBindTexture();


	mapBox.ObjectSetMaterial(cube_material);
	mapBox.ObjectAttach(coreProgID, coreVertAttribName);
	mapBox.ObjectScale(vec3(1.F, 1.F, 1.F));
	mapBox.ObjectTranslate(vec3(0.F, 0.F, 0.F));

	//init sun
	sun.ObjectLoading("cubeSrc.object");
	sun.ObjectUploadBMPTexture("texture/sunmap_0.bmp", 0);
	sun.ObjectUploadBMPTexture("texture/sunmap_1.bmp", 1);
	sun.ObjectUploadBMPTexture("texture/sunmap_3.bmp", 2);
	sun.ObjectUploadBMPTexture("texture/sunmap_2.bmp", 3);
	sun.ObjectUploadBMPTexture("texture/sunmap_4.bmp", 4);
	sun.ObjectUploadBMPTexture("texture/sunmap_5.bmp", 5);
	sun.ObjectSetSurfaceNormDir(-1.F);
	sun.ObjectSetTexCoordMode(TEXCOORD_MODE_NORMAL);
	sun.ObjectBindTexture();


	sun.ObjectSetMaterial(sun_material);
	sun.ObjectAttach(coreProgID, coreVertAttribName);
	sun.ObjectScale(vec3(0.18F, 0.18F, 0.18F));
	sun.ObjectRotate((PI / 180) * 45, vec3(1.F, 1.F, 0.F));
	sun.ObjectTranslate(vec3(0.F, 0.F, 0.F));


	//init planet
	
	for (int i = 0; i < 8; i++)
	{
		
		if ( i < 2 || i > 2)
		{
			char textureSrcName[34] = "texture/solar_system_planet_1.bmp";
			textureSrcName[28] = textureSrcName[28] + i;
			planet[i].ObjectLoading("cubeSrc.object");
			planet[i].ObjectUploadBMPTexture(textureSrcName, 0);
			planet[i].ObjectSetSurfaceNormDir(1.F);
			planet[i].ObjectSetTexCoordMode(TEXCOORD_MODE_SPHERIAL);
		}
		else 
		{
			planet[i].ObjectLoading("cubeSrc.object");
			planet[i].ObjectUploadBMPTexture("texture/defaultplanetmap.bmp", 0);
			planet[i].ObjectUploadBMPTexture("texture/defaultplanetmap.bmp", 1);
			planet[i].ObjectUploadBMPTexture("texture/defaultplanetmap.bmp", 2);
			planet[i].ObjectUploadBMPTexture("texture/defaultplanetmap.bmp", 3);
			planet[i].ObjectUploadBMPTexture("texture/defaultplanetmap.bmp", 4);
			planet[i].ObjectUploadBMPTexture("texture/defaultplanetmap.bmp", 5);
			planet[i].ObjectSetSurfaceNormDir(1.F);
			planet[i].ObjectSetTexCoordMode(TEXCOORD_MODE_NORMAL);
		}
		
		planet[i].ObjectBindTexture();

	
		GLfloat size = planetsSizeData[i];
		planet[i].ObjectSetMaterial(cube_material);
		planet[i].ObjectAttach(coreProgID, coreVertAttribName);
		planet[i].ObjectScale(vec3(0.01F, 0.01F, 0.01F) + vec3(0.008F * size , 0.008F * size , 0.008F * size));
		planet[i].ObjectRotate((PI / 180) * 45, vec3(1.F, 1.F, 0.F));
		planet[i].ObjectTranslate(earthPos + vec3(0.1 * i , 0.F  , 0.F));
	}
	planet[2].ObjectUploadBMPTexture("texture/earthmap_1.bmp", 0);
	planet[2].ObjectUploadBMPTexture("texture/earthmap_1.bmp", 1);
	planet[2].ObjectUploadBMPTexture("texture/earthmap_2.bmp", 2);
	planet[2].ObjectUploadBMPTexture("texture/earthmap_3.bmp", 3);
	planet[2].ObjectUploadBMPTexture("texture/earthmap_4.bmp", 4);
	planet[2].ObjectUploadBMPTexture("texture/earthmap_5.bmp", 5);
	planet[2].ObjectSetSurfaceNormDir(1.F);
	planet[2].ObjectBindTexture();

	

	camMove.camPos = vec3(0.F, 0.125F, -0.9F);
	cam0.CamUpdateView();

	cam0.camPos = vec3(0.F, 0.125F, -0.99F);
	cam0.CamUpdateView();
	cam1.camPos = vec3(0.99F, 0.125F, 0.F);
	cam1.CamUpdateView();
	cam2.camPos = vec3(0.F, 0.125F, 0.99F);
	cam2.CamUpdateView();
	cam3.camPos = vec3(-0.99F, 0.125F, 0.F);
	cam3.CamUpdateView();

	cam0.CamSelect(coreProgID);

	ClearLightBuf(coreProgID);

	
	l1.SetElement(global_light1);
	l1.BindingLight(coreProgID, LIGHT_ID_0);
	l1.AttachLight();


}

void ObjectALLRelease()
{
	for (int i = 0; i < 8; i++)
	{
		planet[i].~object();
		printf("planet[%d] has been released\n\n" , i);
	}
		
	sun.~object();
	printf("sun has been released\n\n");

	mapBox.~object();
	printf("mapbox has been released\n\n");
}


int main(void)
{
	lastTime = system_clock::now();
	curTime = system_clock::now();

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(mainWindowSizeW*2 ,mainWindowSizeH*2,"opengl" , NULL,NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window,CoreKeyCall);
	glewInit();
	DurTime("glfwInit");
	CoreGLSLInit();
	DurTime("CoreGLSLInit");
	
	
	OBJECTFILE newOBJECT = {
		sizeof(cube),
		sizeof(cube_indices),
		cube,
		cube_indices
	};

	SaveObjectFile("cubeSrc.object",&newOBJECT);
	
	DataInit();

	microseconds loopDurTime;
	while (!glfwWindowShouldClose(window))
	{
		lastTime = curTime;
		curTime = system_clock::now();
		CoreClearBuffer();

		mapBox.ObjectSetTessellationLevel(16.F);
		mapBox.ObjectDraw();


		sun.ObjectSetTessellationLevel(16.F);
		sun.ObjectRotate((PI / 180) * 0.1F * loopDurTime.count() / 10000.F, vec3(0.1F, 1.F, 0.F));
		sun.ObjectDraw();


		for (int i = 0; i < 8 ; i++)
		{
			planet[i].ObjectSetTessellationLevel(16.F);
			planet[i].ObjectRotate((PI / 180) * 2.F / (i + 1) * loopDurTime.count() / 10000.F, vec3(0.1F, 1.F, 0.F));
			planet[i].ObjectAddModelProductFront(rotate(mat4(1.F), (PI / 180) * 0.5F/(i+1) * loopDurTime.count() / 10000.F, vec3(0.F, 1.F, 0.F)));
			planet[i].ObjectDraw();

		}
		

		if (camMoveActive)
		{
			camMove.camPos = vec3(rotate(mat4(1.F), (PI / 180) * 1.F * loopDurTime.count() / 10000.F, vec3(0.F, 1.F, 0.F)) * vec4(camMove.camPos, 1.F));
			camMove.CamSelect(coreProgID);
			camMove.CamUpdateView();

		}
		


		glFinish();
		glfwSwapBuffers(window);
		glfwPollEvents();
		loopDurTime = duration_cast<microseconds>(curTime - lastTime);
	
	}

	ObjectALLRelease();
	glfwTerminate();

	return 0;
}

void CoreGLSLInit(void)
{
	const char* vertSource = FileLoad(coreVertSource);
	if (vertSource == NULL) 
	{
		cout << "vertSource is NULL!" << endl;
		return;
	}

	const char* fragSource = FileLoad(coreFragSource);
	if (fragSource == NULL)
	{
		cout << "fragSource is NULL!" << endl;
		return;
	}

	const char* tesCSource = FileLoad(coreTesCSource);
	if (tesCSource == NULL)
	{
		cout << "tesCSource is NULL!" << endl;
		return;
	}
	
	const char* tesESource = FileLoad(coreTesESource);
	if (tesESource == NULL)
	{
		cout << "tesESource is NULL!" << endl;
		return;
	}

	const char* geomSource = FileLoad(coreGeomSource);
	if (geomSource == NULL)
	{
		cout << "geomSource is NULL" << endl;
		return;
	}

	printf("core glsl file load\nvertSource:%s\n\nfragSource:%s\n\n",vertSource ,fragSource);

	printf("core glsl file load\ntesCSource:%s\n\ntesESource:%s\n\n", tesCSource, tesESource);

	printf("core glsl file load\ngeomSource:%s\n\n", geomSource);

	coreVertID = glCreateShader(GL_VERTEX_SHADER);
	coreTesCID = glCreateShader(GL_TESS_CONTROL_SHADER);
	coreTesEID = glCreateShader(GL_TESS_EVALUATION_SHADER);
	coreGeomID = glCreateShader(GL_GEOMETRY_SHADER);
	coreFragID = glCreateShader(GL_FRAGMENT_SHADER);
	

	glShaderSource(coreVertID ,1 ,&vertSource ,NULL);
	glShaderSource(coreTesCID, 1, &tesCSource, NULL);
	glShaderSource(coreTesEID, 1, &tesESource, NULL);
	glShaderSource(coreGeomID, 1, &geomSource, NULL);
	glShaderSource(coreFragID ,1 ,&fragSource ,NULL);
	


	glCompileShader(coreVertID);
	glCompileShader(coreTesCID);
	glCompileShader(coreTesEID);
	//glCompileShader(coreGeomID);
	glCompileShader(coreFragID);


	coreProgID = glCreateProgram();
	glAttachShader(coreProgID ,coreVertID);
	glAttachShader(coreProgID ,coreTesCID);
	glAttachShader(coreProgID ,coreTesEID);
	//glAttachShader(coreProgID, coreGeomID);
	glAttachShader(coreProgID ,coreFragID);
	glLinkProgram(coreProgID);
	glUseProgram(coreProgID);

}

void CoreClearBuffer(void)
{	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.F, 0.F, 0.F, 1.F);
	glClearDepth(1.F);
	glDepthRange(-1.F  , 1.F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CoreKeyCall(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		camMoveActive = false;
		switch (key)
		{
		
		case '0':
			cam0.CamSelect(coreProgID);
			
			break;
		case '1':
			cam1.CamSelect(coreProgID);
			cam1.CamUpdateView();
			break;
		case '2':
			cam2.CamSelect(coreProgID);
			
			break;
		case '3':
			cam3.CamSelect(coreProgID);
			
			break;

		case '4':
			camMove.camPos = vec3(0.F, 0.125F, -0.7F);
			camMoveActive = true;
			break;
		default:
			break;
		}
	}


}