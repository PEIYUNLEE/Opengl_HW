#include "Header\Angel.h"
#include "Common\MainScene.h"
#include "Common\PBoat.h"
#include "Common\EnemyManager.h"

#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2)
#define VP_HALFWIDTH 2.5f

MainScene *g_MainScene;

mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

GLfloat g_fTx = 0, g_fTy = 0;

void IdleProcess();

void init(void)
{
	g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);
	g_MainScene = new MainScene(g_mxModelView, g_mxProjection);
	glClearColor(0.0667f, 0.1333f, 0.2392f,1.0f); //background
}
//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	g_MainScene->Draw();
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	GL_Display();
	g_MainScene->Update(delta);
}
//----------------------------------------------------------------------------

void Win_MouseMotion(int x, int y) {
	mat4 mxGT, mxT;

	g_fTx = 2.5f*(x - HALF_SIZE) / (HALF_SIZE);
	g_fTy = -2.5f*(y - HALF_SIZE) / (HALF_SIZE);
	mxGT = Translate(g_fTx, g_fTy, 0);
	g_MainScene->_pBoat->_transform->SetTRSMatrix(mxGT);
}
void Win_PassiveMotion(int x, int y) {
	mat4 mxGT, mxT;

	g_fTx = 2.5f*(x - HALF_SIZE) / (HALF_SIZE);
	g_fTy = -2.5f*(y - HALF_SIZE) / (HALF_SIZE);
	mxGT = Translate(g_fTx, g_fTy, 0);
	g_MainScene->_pBoat->_transform->SetTRSMatrix(mxGT);
}

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		delete g_MainScene;
		exit(EXIT_SUCCESS);
		break;
	}
}

void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN) {
			g_MainScene->isBoatShoot=true;
		}
		else if (state == GLUT_UP) {
			g_MainScene->isBoatShoot = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 
		if (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		if (state == GLUT_DOWN);
		break;
	default:
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
	glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Color Shoot Game");

	glewExperimental = GL_TRUE;
	glewInit();

	init();
	
	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
	glutPassiveMotionFunc(Win_PassiveMotion);

	glutDisplayFunc(GL_Display);
	glutKeyboardFunc(Win_Keyboard);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);
	glutMainLoop();
	return 0;
}
