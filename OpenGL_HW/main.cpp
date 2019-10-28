#include "Header\Angel.h"
#include "Common\Planet.h"
#include "Common\PBoat.h"

PBoat *g_pBoat;
Planet *g_planet[3];

mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

void IdleProcess();
void CreateGameObject();

void init(void)
{
	g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	CreateGameObject();
	glClearColor(0.0667f, 0.1333f, 0.2392f,1.0f); //background
}


void CreateGameObject() {

	GLuint uiShaderHandle;
	int idx = 0;
	for (int i = 0; i < 3; i++)
	{
		if (idx == 0) { // 第一個物件，必須建立 Shader
			g_planet[idx] = new Planet(0.75f, 1,-0.7f, 8.0f);
			g_planet[idx]->SetVShaderName("vsPlanet1.glsl");
			g_planet[idx]->SetShader(g_mxModelView, g_mxProjection);
			uiShaderHandle = g_planet[idx]->GetShaderHandle(); // 取得 Shader Handle
		}
		else {
			if (idx == 2) {
				g_planet[idx] = new Planet(0.5f, 2, -0.8f, 10.0f);
				g_planet[idx]->SetVShaderName("vsPlanet2.glsl");
			}
			else {
				g_planet[idx] = new Planet(0.35f, 3, -0.6f, 12.0f);
				g_planet[idx]->SetVShaderName("vsPlanet3.glsl");
			}
			g_planet[idx]->SetShader(g_mxModelView, g_mxProjection);
		}
		idx++;
	}

	g_pBoat = new PBoat;
	g_pBoat->SetShader(g_mxModelView, g_mxProjection);
}
//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 3; i++)
	{
		g_planet[i]->Draw();
	}

	g_pBoat->Draw();
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	for (int i = 0; i < 3; i++)
	{
		g_planet[i]->AutoTranslate(delta);
	}

	GL_Display();
}
//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		delete [] g_planet;
		delete g_pBoat;
		exit(EXIT_SUCCESS);
		break;
	}
}

//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Color Shoot Game");

	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutDisplayFunc(GL_Display);
	glutKeyboardFunc(Win_Keyboard);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);
	glutMainLoop();
	return 0;
}
