#include "Header\Angel.h"
#include "Common\Planet.h"
#include "Common\PBoat.h"

//PBoat *g_pBoat;
Planet *g_planet;

mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

void IdleProcess();

void init(void)
{
	g_planet = new Planet(0.75f,1);
	//g_pBoat = new PBoat;

	g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

	g_planet->SetShader(g_mxModelView, g_mxProjection);
	//g_pBoat->SetShader(g_mxModelView, g_mxProjection);

	glClearColor(0.0667f, 0.1333f, 0.2392f,1.0f); //background
}

//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	g_planet->Draw();
	//g_pBoat->Draw();
	glutSwapBuffers();	// ец┤л Frame Buffer
}

void onFrameMove(float delta)
{
	g_planet->AutoTranslate(delta);
	GL_Display();
}
//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		delete g_planet;
		//delete g_pBoat;
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
