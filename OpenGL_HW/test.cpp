#include "Header\Angel.h"
#include "ctest.h"

PBoat *g_pBoat;

mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

void init(void)
{
	g_pBoat = new PBoat;

	g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

	g_pBoat->SetShader(g_mxModelView, g_mxProjection);

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}

//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		
	g_pBoat->Draw();
	glutSwapBuffers();	// ец┤л Frame Buffer
}

//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
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
	glutMainLoop();
	return 0;
}
