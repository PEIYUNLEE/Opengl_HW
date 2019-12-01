///////////////////////////////////////////////////////
/*
///////////////�\��ݨD///////////////

(6/7%)�@�B�ޱ��P�I������

FINISH
(1%)�ƹ��i�H����԰��������k����
(1%)�i�H�o�g���u FINISH
(2%)�ണ�ѳs��o�g(LINKEDLIST)
(2%)�ಣ�ͦ��t�׷P���I������A�άO��L�˹��ʪ�����
(1%)�԰����Ħ����m�˸m�A�åH���l���Y�覡�e�{	//click a��

////////////////////////////////////////////

(10/10%)�G�B�ĤH����

FINISH
(1%)���ܤ֤T�إH�W���P�~�Ϊ��ĤH(���P���C��)�A�򥻪��|�諬����b��
(2%)�H����ɦV���h���ӱ���Ҧ����ĤH
(1%)�ĤH�i�H���_�����͡A�ӥB�㦳���P���C��
(1%)�ĤH���H���¦V���a�o�g�l�u����
(2%)�԰����o�g���l�u�i�H����ĤH�A�ӥB�ĤH�|����
(3%)��BOSS�Ū��ĤH�A�B�ܷ|�ھڳQ�������h��ܤ֤T�ؤ��P�����A�i�H����

////////////////////////////////////////////

(2/4%)�T�B���a����

FINISH
(2%)��P�_���a�O�_�Q�����ð��X�X�z������

�|��
(2%)���a����ĥ�ܤ֦��T�ت��A�A�B�����Ѫ��a����ĥ�i���ܪ��A������(����)

////////////////////////////////////////////�즹�ثe18��

(2/5%)�|�B��L�Aı�o�i�H�i�ܪ��޳N�A�]�t���z�άO�ƾǪ��B��

FINISH
(2%)���Ѷ��h���ʺA����A�åH�ɶ�����¦�i��ʺA���i��(�p:OpenGL_2��Example4�A�H�۰ʲ��ͪ��y��h�������������B��)
�ĤH�Q���즳��L���ĪG(����)
�԰����Q����ɦ���L���ĪG(����)

�|��
�o�g�ɦV���u�������ʪ�Boss
�I�����F�t�׷P����~�A����L���ĪG
�R��
�L�Ī��A

///////////////////////////////////////////////////////

�`���G(�Ш̷ӤW���|�j�������y�z,�ھڧA�ҧ�������,�ۤv���[�p�`���g�b���B)

(4%)�зN���ơA�Ѯv���ӤH���D�[

�S�O�n�D
���B���p��������b�D�{�����}�Y�A�üХܥX�C�@�ӳ����O�_�����]�S���g�A�N���P�p���^
�îھڨC������������,�ۦ�[�p�X�`��
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
	glutSwapBuffers();	// �洫 Frame Buffer
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
	case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
		if (state == GLUT_DOWN) {
			if(g_MainScene->_pBoat->_playerState < PBoat::DEAD)
				g_MainScene->isBoatShoot=true;
		}
		else if (state == GLUT_UP) {
			if (g_MainScene->_pBoat->_playerState < PBoat::DEAD)
				g_MainScene->isBoatShoot = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ����� 
		if (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
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
