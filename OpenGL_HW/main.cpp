///////////////////////////////////////////////////////
/*
///////////////功能需求///////////////

(6/7%)一、操控與背景部分

FINISH
(1%)滑鼠可以控制戰鬥機的左右移動
(1%)可以發射飛彈 FINISH
(2%)能提供連續發射(LINKEDLIST)
(2%)能產生有速度感的背景物件，或是其他裝飾性的物件
(1%)戰鬥機傭有防禦裝置，並以父子關係方式呈現	//click a鍵

////////////////////////////////////////////

(10/10%)二、敵人部分

FINISH
(1%)有至少三種以上不同外形的敵人(不同的顏色)，基本的四方型不算在內
(2%)以物件導向的多型來控制所有的敵人
(1%)敵人可以不斷的產生，而且具有不同的顏色
(1%)敵人能隨機朝向玩家發射子彈攻擊
(2%)戰鬥機發射的子彈可以打到敵人，而且敵人會消失
(3%)有BOSS級的敵人，且至會根據被攻擊的多寡至少三種不同的狀態可以切換

////////////////////////////////////////////

(2/4%)三、玩家部分

FINISH
(2%)能判斷玩家是否被打中並做出合理的反應

尚未
(2%)玩家的船艦至少有三種狀態，且有提供玩家的船艦可改變狀態的機制(受傷)

////////////////////////////////////////////到此目前18分

(2/5%)四、其他你覺得可以展示的技術，包含物理或是數學的運算

FINISH
(2%)提供階層式動態控制，並以時間為基礎進行動態的展示(如:OpenGL_2的Example4，以自動產生的軌跡去控制相關的物件運動)
敵人被打到有其他的效果(受傷)
戰鬥機被打到時有其他的效果(受傷)

尚未
發射導向飛彈攻擊移動的Boss
背景除了速度感物件外，有其他的效果
愛心
無敵狀態

///////////////////////////////////////////////////////

總分：(請依照上面四大部分的描述,根據你所完成部分,自己先加計總分寫在此處)

(4%)創意分數，老師的個人的主觀

特別要求
此處的計分必須放在主程式的開頭，並標示出每一個部分是否完成（沒有寫，將不與計分）
並根據每項完成的部分,自行加計出總分
*/

///////////////////////////////////////////////////////
#include "Header\Angel.h"
#include "Common\MainScene.h"
#include "Common\PBoat.h"
#include "Common\EnemyManager.h"
#include "Common\ColorDefine.h"

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	if (g_MainScene->_pBoat->_playerState < PBoat::DEAD) {
		mat4 mxGT, mxT;

		g_fTx = 2.5f*(x - HALF_SIZE) / (HALF_SIZE);
		g_fTy = -2.5f*(y - HALF_SIZE) / (HALF_SIZE);
		mxGT = Translate(g_fTx, g_fTy, 0);
		g_MainScene->_pBoat->_transform->SetTRSMatrix(mxGT);
	}
}
void Win_PassiveMotion(int x, int y) {
	if (g_MainScene->_pBoat->_playerState < PBoat::DEAD) {
		mat4 mxGT, mxT;

		g_fTx = 2.5f*(x - HALF_SIZE) / (HALF_SIZE);
		g_fTy = -2.5f*(y - HALF_SIZE) / (HALF_SIZE);
		mxGT = Translate(g_fTx, g_fTy, 0);
		g_MainScene->_pBoat->_transform->SetTRSMatrix(mxGT);
	}
}

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		g_MainScene->_enemyManager->GoLevel(LEVEL1);
		break;
	case '2':
		g_MainScene->_enemyManager->GoLevel(LEVEL2);
		break;
	case '3':
		g_MainScene->_enemyManager->GoLevel(LEVEL3);
		break;
	case 'q':
		if (g_MainScene->_pBoat->_playerState == PBoat::DEADANIMFIN) {
			g_MainScene->_pBoat->Revival();
			printf("revival\n");
		}
		break;
	case 'Q':
		if (g_MainScene->_pBoat->_playerState == PBoat::DEADANIMFIN) {
			g_MainScene->_pBoat->Revival();
			printf("revival\n");
		}
		break;
	case 'a':
		if (g_MainScene->_pBoat->_playerState < PBoat::DEAD && g_MainScene->_pBoat->_showDefense) {
			g_MainScene->_pBoat->_playerState = PBoat::DEFENSE;
		}
		break;
	case 'A':
			if (g_MainScene->_pBoat->_playerState < PBoat::DEAD && g_MainScene->_pBoat->_showDefense) {
				g_MainScene->_pBoat->_playerState = PBoat::DEFENSE;
			}
			break;
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
			if(g_MainScene->_pBoat->_playerState < PBoat::DEAD)
				g_MainScene->isBoatShoot=true;
		}
		else if (state == GLUT_UP) {
			if (g_MainScene->_pBoat->_playerState < PBoat::DEAD)
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

	glutCreateWindow("Shoot Game");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

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
