#include "Enemy.h"
#include "PBoat.h"
#include "Bullet.h"

Enemy::Enemy(mat4 &mxView, mat4 &mxProjection, float fspeed,float attackDuration, int pointNum, char type){
	_colliderSize = new float[2];
	_type = type;
	_ftottime = 0;
	_attackTimer = 0;
	_attackDuration = attackDuration;
	_pointNum = pointNum;
	_fspeed = fspeed;
	_isDead = false;
	_initFlag = false;
	_isDefaultEnemy = true;
}

Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
	if (_bulletList != NULL) delete _bulletList;
	if (_colliderSize != NULL) delete [] _colliderSize;
}

void Enemy::Action(float dt, PBoat *getPBoat) {
	_ftottime += dt;
	Attack(dt);
	AutoTranslate(dt);		

	_bulletList->Update(dt, getPBoat);
}



/////////EnemySmall
EnemySmall::EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_colliderSize[0] = 0.15f;
	_colliderSize[1] = 0.17f;
	_attackDuration = 0.8f;
	_fspeed = -1.0f;
	_pointNum = 64;
	_bulletList = new BulletList(mxView, mxProjection, 15, 'e', _COLOR_YELLOW, 1.75f);
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
};

void EnemySmall::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	//center
	for (int i = 0; i < _pointNum; i++) {
		_points[i].x = 0.17f * cosf(M_PI*2.0f*((float)i + 0.5f) / 20.0f); //2拍乘以該點分之總點
		_points[i].y = 0.17f * sinf(M_PI*2.0f*((float)i + 0.5f) / 20.0f);
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_WINDOW_1;
	}

	//WINDOW2
	_points[10] = vec4(-0.17f, 0.0f, 0.0f, 1.0f);
	_points[11] = vec4(-0.12f, 0.12f, 0.0f, 1.0f);
	_points[12] = vec4(-0.13f, 0.0f, 0.0f, 1.0f);
	_points[13] = vec4(-0.03f, 0.15f, 0.0f, 1.0f);

	_colors[10] = _COLOR_WINDOW_2;
	_colors[11] = _COLOR_WINDOW_2;
	_colors[12] = _COLOR_WINDOW_2;
	_colors[13] = _COLOR_WINDOW_2;

	_points[14] = vec4(-0.08f, 0.0f, 0.0f, 1.0f);
	_points[15] = vec4(0.03f, 0.15f, 0.0f, 1.0f);
	_points[16] = vec4(0.01f, 0.0f, 0.0f, 1.0f);
	_points[17] = vec4(0.1f, 0.15f, 0.0f, 1.0f);

	_colors[14] = _COLOR_WINDOW_2;
	_colors[15] = _COLOR_WINDOW_2;
	_colors[16] = _COLOR_WINDOW_2;
	_colors[17] = _COLOR_WINDOW_2;

	_points[18] = vec4(0.05f, 0.0f, 0.0f, 1.0f);
	_points[19] = vec4(0.12f, 0.11f, 0.0f, 1.0f);
	_points[20] = vec4(0.16f, 0.0f, 0.0f, 1.0f);
	_points[21] = vec4(0.08f, 0.15f, 0.0f, 1.0f);

	_colors[18] = _COLOR_WINDOW_2;
	_colors[19] = _COLOR_WINDOW_2;
	_colors[20] = _COLOR_WINDOW_2;
	_colors[21] = _COLOR_WINDOW_2;

	//SHOOT
	////////////////////////////////////////////////////shoot center 1
	_points[22] = vec4(0.07f, -0.05f, 0.0f, 1.0f);
	_points[23] = vec4(0.07f, -0.185f, 0.0f, 1.0f);
	_points[24] = vec4(-0.07f, -0.05f, 0.0f, 1.0f);
	_points[25] = vec4(-0.07f, -0.185f, 0.0f, 1.0f);

	_colors[22] = _COLOR_GRAY;
	_colors[23] = _COLOR_GRAY;
	_colors[24] = _COLOR_GRAY;
	_colors[25] = _COLOR_GRAY;


	///////////////////////////////////////////////////////shoot center 2
	_points[26] = vec4(-0.045f, -0.225f, 0.0f, 1.0f);
	_points[27] = vec4(-0.045f, -0.175f, 0.0f, 1.0f);
	_points[28] = vec4(-0.02f, -0.225f, 0.0f, 1.0f);
	_points[29] = vec4(-0.02f, -0.175f, 0.0f, 1.0f);

	_colors[26] = _COLOR_GRAY;
	_colors[27] = _COLOR_GRAY;
	_colors[28] = _COLOR_GRAY;
	_colors[29] = _COLOR_GRAY;

	//////////////////////////////////////////////////////shoot center 2
	_points[30] = vec4(0.045f, -0.225f, 0.0f, 1.0f);
	_points[31] = vec4(0.045f, -0.175f, 0.0f, 1.0f);
	_points[32] = vec4(0.02f, -0.225f, 0.0f, 1.0f);
	_points[33] = vec4(0.02f, -0.175f, 0.0f, 1.0f);

	_colors[30] = _COLOR_GRAY;
	_colors[31] = _COLOR_GRAY;
	_colors[32] = _COLOR_GRAY;
	_colors[33] = _COLOR_GRAY;

	///////////////////////////////////////////////////////shoot center circle
	for (int i = 34; i < 44; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) - 0.0325f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.235f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	///////////////////////////////////////////////////////shoot center circle
	for (int i = 44; i < 54; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) + 0.0325f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.235f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	//////////////////////////////////////////////////////body
	_points[54] = vec4(-0.3f, -0.0525f, 0.0f, 1.0f);
	_points[55] = vec4(-0.17f, 0.025f, 0.0f, 1.0f);
	_points[56] = vec4(-0.17f, -0.13f, 0.0f, 1.0f);
	_points[57] = vec4(0.17f, 0.025f, 0.0f, 1.0f);
	_points[58] = vec4(0.17f, -0.13f, 0.0f, 1.0f);
	_points[59] = vec4(0.3f, -0.0525f, 0.0f, 1.0f);

	_colors[54] = _COLOR_BLUEGREEN;
	_colors[55] = _COLOR_BLUEGREEN;
	_colors[56] = _COLOR_BLUEGREEN;
	_colors[57] = _COLOR_BLUEGREEN;
	_colors[58] = _COLOR_BLUEGREEN;
	_colors[59] = _COLOR_BLUEGREEN;

	//////////////////////////////////////////////////////YELLOW LINE
	_points[60] = vec4(-0.3f, -0.0525f, 0.0f, 1.0f);
	_points[61] = vec4(-0.3f, -0.065f, 0.0f, 1.0f);
	_points[62] = vec4(0.3f, -0.0525f, 0.0f, 1.0f);
	_points[63] = vec4(0.3f, -0.065f, 0.0f, 1.0f);

	_colors[60] = _COLOR_YELLOW;
	_colors[61] = _COLOR_YELLOW;
	_colors[62] = _COLOR_YELLOW;
	_colors[63] = _COLOR_YELLOW;
}

void EnemySmall::Attack(float dt){
	mat4 mat = _transform->_mxTRS;
	mat._m[1].w -= 0.2f;
	_attackTimer += dt;
	if (!_initFlag && _attackTimer>=0.5f) {
		_attackTimer = 0.0f;
		_bulletList->BulletShoot(mat, 0.0f,-1.0f);
		_initFlag = true;
	}
	if (_attackTimer >= _attackDuration) {
		_attackTimer = 0.0f;
		_bulletList->BulletShoot(mat, 0.0f, -1.0f);
	}
}

void EnemySmall::AutoTranslate(float dt) {
	mat4 mxTra;
	GLfloat btx = 0.0f;
	GLfloat bty = 0.0f;

	bty = _ftottime*_fspeed;
	mxTra = Translate(btx, bty, 0.0f);
	_transform->SetTRSMatrix(mxTra*_transform->_mxOri);
}

void EnemySmall::Draw() {
	_bulletList->BulletDraw();

	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
	glDrawArrays(GL_TRIANGLE_STRIP, 10, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 14, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 18, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 22, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 26, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 30, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 34, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 44, 10);
	glDrawArrays(GL_TRIANGLE_STRIP, 54, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 60, 4);
}

void EnemySmall::Hurt() {
	_isDead = true;
}

void EnemySmall::Reset() {
	_transform->Reset();
	_ftottime = 0.0f;
	_attackTimer = 0;
	_isDead = false;
	_initFlag = false;
	_isDefaultEnemy = true;
}



/////////EnemyMiddle
EnemyMiddle::EnemyMiddle(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_fspeed = -0.8f;
	_attackDuration = 0.5f;
	_colliderSize[0] = 0.3f;
	_colliderSize[1] = 0.3f;

	_bIX = 0.0f;
	_bIY = 1.0f;
	_rotateDuration = 5.0f;
	_rotateTimer = 0.0f;
	_translateTimer = 0.0f;
	_fZAngle = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;
	_isStop = false;

	_bulletList = new BulletList(mxView, mxProjection, 20, 'm',  _COLOR_YELLOW, 1.0f);
	_pointNum = 344;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
};

void EnemyMiddle::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	////SHOOT
	//////////////////////////////////////////////////shoot center 1
	_points[0] = vec4(0.09f, -0.285f, 0.0f, 1.0f);
	_points[1] = vec4(0.09f, -0.4f, 0.0f, 1.0f);
	_points[2] = vec4(-0.09f, -0.285f, 0.0f, 1.0f);
	_points[3] = vec4(-0.09f, -0.4f, 0.0f, 1.0f);

	_colors[0] = _COLOR_GRAY;
	_colors[1] = _COLOR_GRAY;
	_colors[2] = _COLOR_GRAY;
	_colors[3] = _COLOR_GRAY;

	///////////////////////////////////////////////////////shoot center 2
	_points[4] = vec4(-0.05f, -0.435f, 0.0f, 1.0f);
	_points[5] = vec4(-0.05f, -0.375f, 0.0f, 1.0f);
	_points[6] = vec4(-0.02f, -0.435f, 0.0f, 1.0f);
	_points[7] = vec4(-0.02f, -0.375f, 0.0f, 1.0f);

	_colors[4] = _COLOR_GRAY;
	_colors[5] = _COLOR_GRAY;
	_colors[6] = _COLOR_GRAY;
	_colors[7] = _COLOR_GRAY;

	////////////////////////////////////////////////////////shoot center 2
	_points[8] = vec4(0.05f, -0.435f, 0.0f, 1.0f);
	_points[9] = vec4(0.05f, -0.375f, 0.0f, 1.0f);
	_points[10] = vec4(0.02f, -0.435f, 0.0f, 1.0f);
	_points[11] = vec4(0.02f, -0.375f, 0.0f, 1.0f);

	_colors[8] = _COLOR_GRAY;
	_colors[9] = _COLOR_GRAY;
	_colors[10] = _COLOR_GRAY;
	_colors[11] = _COLOR_GRAY;

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 12; i < 22; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) - 0.033f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.44f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 22; i < 32; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) + 0.033f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.44f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	////SHOOT TOP
	//////////////////////////////////////////////////shoot center 1
	_points[32] = vec4(0.09f, 0.285f, 0.0f, 1.0f);
	_points[33] = vec4(0.09f, 0.4f, 0.0f, 1.0f);
	_points[34] = vec4(-0.09f, 0.285f, 0.0f, 1.0f);
	_points[35] = vec4(-0.09f, 0.4f, 0.0f, 1.0f);

	_colors[32] = _COLOR_GRAY;
	_colors[33] = _COLOR_GRAY;
	_colors[34] = _COLOR_GRAY;
	_colors[35] = _COLOR_GRAY;

	///////////////////////////////////////////////////////shoot center 2
	_points[36] = vec4(-0.05f, 0.435f, 0.0f, 1.0f);
	_points[37] = vec4(-0.05f, 0.375f, 0.0f, 1.0f);
	_points[38] = vec4(-0.02f, 0.435f, 0.0f, 1.0f);
	_points[39] = vec4(-0.02f, 0.375f, 0.0f, 1.0f);

	_colors[36] = _COLOR_GRAY;
	_colors[37] = _COLOR_GRAY;
	_colors[38] = _COLOR_GRAY;
	_colors[39] = _COLOR_GRAY;

	////////////////////////////////////////////////////////shoot center 2
	_points[40] = vec4(0.05f, 0.435f, 0.0f, 1.0f);
	_points[41] = vec4(0.05f, 0.375f, 0.0f, 1.0f);
	_points[42] = vec4(0.02f, 0.435f, 0.0f, 1.0f);
	_points[43] = vec4(0.02f, 0.375f, 0.0f, 1.0f);

	_colors[40] = _COLOR_GRAY;
	_colors[41] = _COLOR_GRAY;
	_colors[42] = _COLOR_GRAY;
	_colors[43] = _COLOR_GRAY;

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 44; i < 54; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) - 0.033f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) + 0.44f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 54; i < 64; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) + 0.033f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) + 0.44f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	////SHOOT LEFT
	//////////////////////////////////////////////////shoot center 1
	_points[64] = vec4(-0.4f, -0.09f, 0.0f, 1.0f);
	_points[65] = vec4(-0.4f, 0.09f, 0.0f, 1.0f);
	_points[66] = vec4(-0.285f, -0.09f, 0.0f, 1.0f);
	_points[67] = vec4(-0.285f, 0.09f, 0.0f, 1.0f);

	_colors[64] = _COLOR_GRAY;
	_colors[65] = _COLOR_GRAY;
	_colors[66] = _COLOR_GRAY;
	_colors[67] = _COLOR_GRAY;

	///////////////////////////////////////////////////////shoot center 2
	_points[68] = vec4(-0.435f, 0.02f, 0.0f, 1.0f);
	_points[69] = vec4(-0.435f, 0.05f, 0.0f, 1.0f);
	_points[70] = vec4(-0.375f, 0.02f, 0.0f, 1.0f);
	_points[71] = vec4(-0.375f, 0.05f, 0.0f, 1.0f);

	_colors[68] = _COLOR_GRAY;
	_colors[69] = _COLOR_GRAY;
	_colors[70] = _COLOR_GRAY;
	_colors[71] = _COLOR_GRAY;

	//////////////////////////////////////////////////////////shoot center 2
	_points[72] = vec4(-0.435f, -0.02f, 0.0f, 1.0f);
	_points[73] = vec4(-0.435f, -0.05f, 0.0f, 1.0f);
	_points[74] = vec4(-0.375f, -0.02f, 0.0f, 1.0f);
	_points[75] = vec4(-0.375f, -0.05f, 0.0f, 1.0f);

	_colors[72] = _COLOR_GRAY;
	_colors[73] = _COLOR_GRAY;
	_colors[74] = _COLOR_GRAY;
	_colors[75] = _COLOR_GRAY;

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 76; i < 86; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) - 0.44f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) + 0.035f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 86; i < 96; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) - 0.44f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.035f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	////SHOOT RIGHT
	//////////////////////////////////////////////////shoot center 1
	_points[96] = vec4(0.4f, -0.09f, 0.0f, 1.0f);
	_points[97] = vec4(0.4f, 0.09f, 0.0f, 1.0f);
	_points[98] = vec4(0.285f, -0.09f, 0.0f, 1.0f);
	_points[99] = vec4(0.285f, 0.09f, 0.0f, 1.0f);

	_colors[96] = _COLOR_GRAY;
	_colors[97] = _COLOR_GRAY;
	_colors[98] = _COLOR_GRAY;
	_colors[99] = _COLOR_GRAY;

	///////////////////////////////////////////////////////shoot center 2
	_points[100] = vec4(0.435f, 0.02f, 0.0f, 1.0f);
	_points[101] = vec4(0.435f, 0.05f, 0.0f, 1.0f);
	_points[102] = vec4(0.375f, 0.02f, 0.0f, 1.0f);
	_points[103] = vec4(0.375f, 0.05f, 0.0f, 1.0f);

	_colors[100] = _COLOR_GRAY;
	_colors[101] = _COLOR_GRAY;
	_colors[102] = _COLOR_GRAY;
	_colors[103] = _COLOR_GRAY;

	//////////////////////////////////////////////////////////shoot center 2
	_points[104] = vec4(0.435f, -0.02f, 0.0f, 1.0f);
	_points[105] = vec4(0.435f, -0.05f, 0.0f, 1.0f);
	_points[106] = vec4(0.375f, -0.02f, 0.0f, 1.0f);
	_points[107] = vec4(0.375f, -0.05f, 0.0f, 1.0f);

	_colors[104] = _COLOR_GRAY;
	_colors[105] = _COLOR_GRAY;
	_colors[106] = _COLOR_GRAY;
	_colors[107] = _COLOR_GRAY;

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 108; i < 118; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) + 0.44f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) + 0.035f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////////shoot center circle
	for (int i = 118; i < 128; i++)
	{
		_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)i / 10.0f) + 0.44f;
		_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.035f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////////window1
	for (int i = 128; i < 148; i++)
	{
		_points[i].x = 0.2f* cosf(M_PI*2.0f*(float)i / 20.0f);
		_points[i].y = 0.2f* sinf(M_PI*2.0f*(float)i / 20.0f);
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_WINDOW_1;
	}

	/////////////////////////////////////////////////////////window1
	for (int i = 148; i < 168; i++)
	{
		_points[i].x = 0.2f* cosf(M_PI*2.0f*(float)i / 20.0f);
		_points[i].y = 0.2f* sinf(M_PI*2.0f*(float)i / 20.0f);
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_WINDOW_1;
	}

	///////////////////////////////////////////////////////window2 138~150

	_points[168] = vec4(-0.22f, 0.05f, 0.0f, 1.0f);
	_points[169] = vec4(-0.08f, 0.2f, 0.0f, 1.0f);
	_points[170] = vec4(-0.19f, -0.02f, 0.0f, 1.0f);
	_points[171] = vec4(-0.03f, 0.21f, 0.0f, 1.0f);

	_colors[168] = _COLOR_WINDOW_2;
	_colors[169] = _COLOR_WINDOW_2;
	_colors[170] = _COLOR_WINDOW_2;
	_colors[171] = _COLOR_WINDOW_2;

	_points[172] = vec4(-0.17f, -0.08f, 0.0f, 1.0f);
	_points[173] = vec4(0.04f, 0.21f, 0.0f, 1.0f);
	_points[174] = vec4(-0.08f, -0.16f, 0.0f, 1.0f);
	_points[175] = vec4(0.15f, 0.15f, 0.0f, 1.0f);

	_colors[172] = _COLOR_WINDOW_2;
	_colors[173] = _COLOR_WINDOW_2;
	_colors[174] = _COLOR_WINDOW_2;
	_colors[175] = _COLOR_WINDOW_2;

	_points[176] = vec4(-0.02f, -0.18f, 0.0f, 1.0f);
	_points[177] = vec4(0.18f, 0.1f, 0.0f, 1.0f);
	_points[178] = vec4(0.12f, -0.15f, 0.0f, 1.0f);
	_points[179] = vec4(0.22f, 0.0f, 0.0f, 1.0f);

	_colors[176] = _COLOR_WINDOW_2;
	_colors[177] = _COLOR_WINDOW_2;
	_colors[178] = _COLOR_WINDOW_2;
	_colors[179] = _COLOR_WINDOW_2;

	///////////////////////////////////////////////////////GRAY CIRCLE
	for (int i = 180; i < 222; i++)
	{
		if (i % 2 == 0) {
			_points[i].x = 0.22f* cosf(M_PI*2.0f*(float)(i / 2) / 20.0f);
			_points[i].y = 0.22f* sinf(M_PI*2.0f*(float)(i / 2)/ 20.0f);
		}
		else {
			_points[i].x = 0.2f* cosf(M_PI*2.0f*(float)(i / 2) / 20.0f);
			_points[i].y = 0.2f* sinf(M_PI*2.0f*(float)(i / 2) / 20.0f);
		}
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	///////////////////////////////////////////////////////BLUEGREEN CIRCLE
	for (int i = 222; i < 264; i++)
	{
		if (i % 2 == 0) {
			_points[i].x = 0.22f* cosf(M_PI*2.0f*(float)(i / 2) / 20.0f);
			_points[i].y = 0.22f* sinf(M_PI*2.0f*(float)(i / 2) / 20.0f);
		}
		else {
			_points[i].x = 0.35f* cosf(M_PI*2.0f*(float)(i / 2) / 20.0f);
			_points[i].y = 0.35f* sinf(M_PI*2.0f*(float)(i / 2) / 20.0f);
		}
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BLUEGREEN;
	}

	///////////////////////////////////////////////////////YELLOW CIRCLE
	for (int j = 0; j < 8; j++)
	{
		for (int i = 264+10*j; i < 274 + 10 * j; i++)
		{
			_points[i].x = 0.025f* cosf(M_PI*2.0f*(float)(i) / 10.0f) + 0.275f* cosf(M_PI*2.0f*(float)(j) / 8.0f);
			_points[i].y = 0.025f* sinf(M_PI*2.0f*(float)(i) / 10.0f) + 0.275f* sinf(M_PI*2.0f*(float)(j) / 8.0f);
			_points[i].w = 1.0f;
			_colors[i] = _COLOR_YELLOW;
		}
	}

}

void EnemyMiddle::Draw() {
	_bulletList->BulletDraw();

	_transform->Draw();

	//SHOOT
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 10);

	glDrawArrays(GL_TRIANGLE_STRIP, 32, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 36, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 40, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 44, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 54, 10);

	glDrawArrays(GL_TRIANGLE_STRIP, 64, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 68, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 72, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 76, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 86, 10);

	glDrawArrays(GL_TRIANGLE_STRIP, 96, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 100, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 104, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 108, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 118, 10);

	//WINDOW
	glDrawArrays(GL_TRIANGLE_FAN, 128, 20);
	glDrawArrays(GL_TRIANGLE_FAN, 148, 20);
	glDrawArrays(GL_TRIANGLE_STRIP, 168, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 172, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 176, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 180, 42);
	glDrawArrays(GL_TRIANGLE_STRIP, 222, 42);

	//YELLOW CIRCLE
	glDrawArrays(GL_TRIANGLE_FAN, 264, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 274, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 284, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 294, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 304, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 314, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 324, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 334, 10);
}

void EnemyMiddle::Attack(float dt) {
	if (!_isStop) {
		//到定位開始攻擊
		_attackTimer += dt;
		if (_attackTimer >= _attackDuration) {
			//開始第一種攻擊
			_attackDuration = 1.5f;
			_attackTimer = 0.0f;
			_bulletList->BulletShoot(_transform->_mxTRS, _bIX, _bIY);
			_bulletList->BulletShoot(_transform->_mxTRS, -_bIX, -_bIY);
			mat4 mat = _transform->_mxTRS;
			mat._m[0].w += 0.2f;
			_bulletList->BulletShoot(mat, _bIX, _bIY);
			_bulletList->BulletShoot(mat, -_bIX, -_bIY);
			mat._m[0].w -= 0.4f;
			_bulletList->BulletShoot(mat, _bIX, _bIY);
			_bulletList->BulletShoot(mat, -_bIX, -_bIY);
		}
	}
	else {
		_attackTimer += dt;
		_attackDuration = 3.0f;
		if (_attackTimer >= _attackDuration) {
			//開始第二種攻擊
			_attackTimer = 0.0f;
			mat4 mat = _transform->_mxTRS;
			mat._m[1].w += 0.25f*_bIY;
			mat._m[0].w += 0.25f*_bIX;
			_bulletList->BulletShoot(mat, _bIX, _bIY);
			mat = _transform->_mxTRS;
			mat._m[0].w += 0.25f*_bIY;
			mat._m[1].w -= 0.25f*_bIX;
			_bulletList->BulletShoot(mat, _bIY, -_bIX);
			mat = _transform->_mxTRS;
			mat._m[1].w -= 0.25f*_bIY;
			mat._m[0].w -= 0.25f*_bIX;
			_bulletList->BulletShoot(mat, -_bIX, -_bIY);
			mat = _transform->_mxTRS;
			mat._m[0].w -= 0.25f*_bIY;
			mat._m[1].w += 0.25f*_bIX;
			_bulletList->BulletShoot(mat, -_bIY, _bIX);
		}
	}
}

void EnemyMiddle::AutoTranslate(float dt) {
	mat4 mxTra;
	mat4 mxRot;

	if (_transform->_mxTRS._m[0].w >= 1.5f || _transform->_mxTRS._m[0].w <= -1.5f) {
		_translateTimer += dt;
		if(_isDefaultEnemy)
			_btx += dt*_fspeed;
		else
			_btx += dt*(-_fspeed);
	}
	else {
		_isStop = true;
		_rotateTimer += dt;

		if (_rotateTimer >= _rotateDuration) {
			//開始轉
			if (_rotateTimer <= 1.5f + _rotateDuration)
				_fZAngle += 30.0f * dt;
			else {
				_rotateTimer = 0.0f;
				if (_bIX == 0.0f) {
					_bIX = 1.0f;
					_bIY = 1.0f;
				}
				else {
					_bIX = 0.0f;
					_bIY = 1.0f;
				}
			}
		}
	}

	if (_fZAngle != 0.0f)
		mxRot = RotateZ(_fZAngle);

	mxTra = Translate(_btx, _bty, 0.0f);

	_transform->SetTRSMatrix(mxTra*_transform->_mxOri*mxRot );
}

void EnemyMiddle::Hurt() {
	_isDead = true;
}

void EnemyMiddle::Reset() {
	_transform->Reset();
	_isDead = false;
	_initFlag = false;

	_ftottime = 0.0f;
	_attackTimer = 0;
	_rotateTimer = 0.0f;
	_translateTimer = 0.0f;
	_bIX = 0.0f;
	_bIY = 1.0f;
	_isStop = false;
	_fZAngle = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;
	_isDefaultEnemy = true;
}


/////////EnemyBoss
EnemyBoss::EnemyBoss(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_colliderSize[0] = 0.8f;
	_colliderSize[1] = 0.5f;
	_attackState = Idle;
	_attackDuration = 1.25f;

	_bIX = 0.0f;
	_bIY = 1.0f;
	_translateTimer = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;
	_isExploShoot = false;
	_heart = 30;

	_pointNum = 249;
	_bulletList = new BulletList(mxView, mxProjection, 50, 'b', _COLOR_YELLOW, 1.2f);
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
};

void EnemyBoss::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	float a = 0.0f;
	float b = 0.0f;

	////////////////////////////////////////////////////window background
	_points[0] = vec4(-0.4f , -0.2f , 0.0f , 1.0f);
	_points[1] = vec4(-0.4f, 0.35f, 0.0f, 1.0f);
	_points[2] = vec4(0.4f, -0.2f, 0.0f, 1.0f);
	_points[3] = vec4(0.4f, 0.35f, 0.0f, 1.0f);

	_colors[0] = _COLOR_BLUEGREEN;
	_colors[1] = _COLOR_BLUEGREEN;
	_colors[2] = _COLOR_BLUEGREEN;
	_colors[3] = _COLOR_BLUEGREEN;

	////////////////////////////////////////////////////shoot left 1
	_points[4] = vec4(-0.65f, -0.45f, 0.0f, 1.0f);
	_points[5] = vec4(-0.65f, -0.1f, 0.0f, 1.0f);
	_points[6] = vec4(-0.45f, -0.45f, 0.0f, 1.0f);
	_points[7] = vec4(-0.45f, -0.1f, 0.0f, 1.0f);

	_colors[4] = _COLOR_GRAY;
	_colors[5] = _COLOR_GRAY;
	_colors[6] = _COLOR_GRAY;
	_colors[7] = _COLOR_GRAY;

	////////////////////////////////////////////////////window1
	_points[8] = vec4(-0.375f, -0.2f, 0.0f, 1.0f);
	_points[9] = vec4(-0.375f, 0.35f, 0.0f, 1.0f);
	_points[10] = vec4(0.375f, -0.2f, 0.0f, 1.0f);
	_points[11] = vec4(0.375f, 0.35f, 0.0f, 1.0f);

	_colors[8] = _COLOR_WINDOW_1;
	_colors[9] = _COLOR_WINDOW_1;
	_colors[10] = _COLOR_WINDOW_1;
	_colors[11] = _COLOR_WINDOW_1;

	////////////////////////////////////////////////////monster
	a = 0.16f;
	b = 0.16f;
	for (int i = 12; i < 32; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(float)i / 20.0f);
		_points[i].y = b* sinf(M_PI*2.0f*(float)i / 20.0f) + 0.09f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_PURPLE;
	}

	////////////////////////////////////////////////////monster hand
	_points[32] = vec4(-0.21f, 0.09f, 0.0f, 1.0f);
	_points[33] = vec4(0.21f, 0.09f, 0.0f, 1.0f);
	_points[34] = vec4(0.0f, -0.05f, 0.0f, 1.0f);

	_colors[32] = _COLOR_PURPLE;
	_colors[33] = _COLOR_PURPLE;
	_colors[34] = _COLOR_PURPLE;

	////////////////////////////////////////////////////monster EYE1
	a = 0.08f;
	b = 0.08f;
	for (int i = 35; i < 55; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(float)i / 20.0f);
		_points[i].y = b* sinf(M_PI*2.0f*(float)i / 20.0f) + 0.13f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_WHITE;
	}

	////////////////////////////////////////////////////monster EYE2
	a = 0.035f;
	b = 0.035f;
	for (int i = 55; i < 65; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(float)i / 10.0f);
		_points[i].y = b* sinf(M_PI*2.0f*(float)i / 10.0f) + 0.1275f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BLACK;
	}

	////////////////////////////////////////////////////window2 left
	_points[65] = vec4(-0.375f, 0.19f, 0.0f, 1.0f);
	_points[66] = vec4(-0.21f, 0.46f, 0.0f, 1.0f);
	_points[67] = vec4(-0.37f, -0.08f, 0.0f, 1.0f);
	_points[68] = vec4(-0.07f, 0.38f, 0.0f, 1.0f);

	_colors[65] = _COLOR_WINDOW_2;
	_colors[66] = _COLOR_WINDOW_2;
	_colors[67] = _COLOR_WINDOW_2;
	_colors[68] = _COLOR_WINDOW_2;

	////////////////////////////////////////////////////window2 center
	_points[69] = vec4(-0.20f, -0.03f, 0.0f, 1.0f);
	_points[70] = vec4(0.11f, 0.43f, 0.0f, 1.0f);
	_points[71] = vec4(-0.06f, -0.12f, 0.0f, 1.0f);
	_points[72] = vec4(0.26f, 0.34f, 0.0f, 1.0f);

	_colors[69] = _COLOR_WINDOW_2;
	_colors[70] = _COLOR_WINDOW_2;
	_colors[71] = _COLOR_WINDOW_2;
	_colors[72] = _COLOR_WINDOW_2;

	////////////////////////////////////////////////////window2 right
	_points[73] = vec4(0.07f, -0.09f, 0.0f, 1.0f);
	_points[74] = vec4(0.29f, -0.24f, 0.0f, 1.0f);
	_points[75] = vec4(0.375f, 0.36f, 0.0f, 1.0f);
	_points[76] = vec4(0.375f, -0.09f, 0.0f, 1.0f);

	_colors[73] = _COLOR_WINDOW_2;
	_colors[74] = _COLOR_WINDOW_2;
	_colors[75] = _COLOR_WINDOW_2;
	_colors[76] = _COLOR_WINDOW_2;

	////////////////////////////////////////////////////top line
	_points[77] = vec4(-0.01f, 0.63f, 0.0f, 1.0f);
	_points[78] = vec4(-0.01f, 0.69f, 0.0f, 1.0f);
	_points[79] = vec4(0.01f, 0.63f, 0.0f, 1.0f);
	_points[80] = vec4(0.01f, 0.69f, 0.0f, 1.0f);

	_colors[77] = _COLOR_YELLOW;
	_colors[78] = _COLOR_YELLOW;
	_colors[79] = _COLOR_YELLOW;
	_colors[80] = _COLOR_YELLOW;

	////////////////////////////////////////////////////head
	a = 0.405f;
	b = 0.35f;
	for (int i = 81; i < 91; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*((float)i - 80.5f) / 20.0f);
		_points[i].y = b* sinf(M_PI*2.0f*((float)i - 80.5f) / 20.0f) + 0.285f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BLUEGREEN;
	}

	////////////////////////////////////////////////////shoot left 2
	_points[91] = vec4(-0.61f, -0.5f, 0.0f, 1.0f);
	_points[92] = vec4(-0.61f, -0.44f, 0.0f, 1.0f);
	_points[93] = vec4(-0.58f, -0.5f, 0.0f, 1.0f);
	_points[94] = vec4(-0.58f, -0.44f, 0.0f, 1.0f);

	_colors[91] = _COLOR_GRAY;
	_colors[92] = _COLOR_GRAY;
	_colors[93] = _COLOR_GRAY;
	_colors[94] = _COLOR_GRAY;

	////////////////////////////////////////////////////shoot left 3
	_points[95] = vec4(-0.52f, -0.5f, 0.0f, 1.0f);
	_points[96] = vec4(-0.52f, -0.44f, 0.0f, 1.0f);
	_points[97] = vec4(-0.49f, -0.5f, 0.0f, 1.0f);
	_points[98] = vec4(-0.49f, -0.44f, 0.0f, 1.0f);

	_colors[95] = _COLOR_GRAY;
	_colors[96] = _COLOR_GRAY;
	_colors[97] = _COLOR_GRAY;
	_colors[98] = _COLOR_GRAY;


	/////////////////////////////////////////////////////shoot right 2
	_points[99] = vec4(0.61f, -0.5f, 0.0f, 1.0f);
	_points[100] = vec4(0.61f, -0.44f, 0.0f, 1.0f);
	_points[101] = vec4(0.58f, -0.5f, 0.0f, 1.0f);
	_points[102] = vec4(0.58f, -0.44f, 0.0f, 1.0f);

	_colors[99] = _COLOR_GRAY;
	_colors[100] = _COLOR_GRAY;
	_colors[101] = _COLOR_GRAY;
	_colors[102] = _COLOR_GRAY;

	////////////////////////////////////////////////////shoot right 3
	_points[103] = vec4(0.52f, -0.5f, 0.0f, 1.0f);
	_points[104] = vec4(0.52f, -0.44f, 0.0f, 1.0f);
	_points[105] = vec4(0.49f, -0.5f, 0.0f, 1.0f);
	_points[106] = vec4(0.49f, -0.44f, 0.0f, 1.0f);

	_colors[103] = _COLOR_GRAY;
	_colors[104] = _COLOR_GRAY;
	_colors[105] = _COLOR_GRAY;
	_colors[106] = _COLOR_GRAY;

	/////////////////////////////////////////////////////shoot left circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 107; i < 117; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(float)i / 10.0f)-0.595f;
		_points[i].y = b* sinf(M_PI*2.0f*(float)i / 10.0f)-0.52f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////shoot left circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 117; i < 127; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(float)i / 10.0f) - 0.505f;
		_points[i].y = b* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.52f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}


	/////////////////////////////////////////////////////shoot right circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 127; i < 137; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(float)i / 10.0f) + 0.595f;
		_points[i].y = b* sinf(M_PI*2.0f*(float)i / 10.0f) - 0.52f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////shoot right circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 137; i < 147; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 10) + 0.505f;
		_points[i].y = b* sinf(M_PI*2.0f*i / 10) - 0.52f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	////////////////////////////////////////////////////shoot right 1
	_points[147] = vec4(0.65f, -0.45f, 0.0f, 1.0f);
	_points[148] = vec4(0.65f, -0.1f, 0.0f, 1.0f);
	_points[149] = vec4(0.45f, -0.45f, 0.0f, 1.0f);
	_points[150] = vec4(0.45f, -0.1f, 0.0f, 1.0f);

	_colors[147] = _COLOR_GRAY;
	_colors[148] = _COLOR_GRAY;
	_colors[149] = _COLOR_GRAY;
	_colors[150] = _COLOR_GRAY;


	////////////////////////////////////////////////////shoot center bottom gray
	a = 0.46f;
	b = 0.42f;
	for (int i = 151; i < 161; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*(i - 20) / 20);
		_points[i].y = b* sinf(M_PI*2.0f*(i - 20) / 20) - 0.07f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	////////////////////////////////////////////////////shoot center bottom yellow
	_points[161] = vec4(-0.30f, -0.405f, 0.0f, 1.0f);
	_points[162] = vec4(-0.30f, -0.37f, 0.0f, 1.0f);
	_points[163] = vec4(0.30f, -0.405f, 0.0f, 1.0f);
	_points[164] = vec4(0.30f, -0.37f, 0.0f, 1.0f);

	_colors[161] = _COLOR_YELLOW;
	_colors[162] = _COLOR_YELLOW;
	_colors[163] = _COLOR_YELLOW;
	_colors[164] = _COLOR_YELLOW;


	////////////////////////////////////////////////////shoot center 1
	_points[165] = vec4(0.1f, -0.575f, 0.0f, 1.0f);
	_points[166] = vec4(0.1f, -0.45f, 0.0f, 1.0f);
	_points[167] = vec4(-0.1f, -0.575f, 0.0f, 1.0f);
	_points[168] = vec4(-0.1f, -0.45f, 0.0f, 1.0f);

	_colors[165] = _COLOR_GRAY;
	_colors[166] = _COLOR_GRAY;
	_colors[167] = _COLOR_GRAY;
	_colors[168] = _COLOR_GRAY;


	/////////////////////////////////////////////////////shoot center 2
	_points[169] = vec4(-0.06f, -0.665f, 0.0f, 1.0f);
	_points[170] = vec4(-0.06f, -0.565f, 0.0f, 1.0f);
	_points[171] = vec4(-0.03f, -0.665f, 0.0f, 1.0f);
	_points[172] = vec4(-0.03f, -0.565f, 0.0f, 1.0f);

	_colors[169] = _COLOR_GRAY;
	_colors[170] = _COLOR_GRAY;
	_colors[171] = _COLOR_GRAY;
	_colors[172] = _COLOR_GRAY;

	////////////////////////////////////////////////////shoot center 2
	_points[173] = vec4(0.03f, -0.665f, 0.0f, 1.0f);
	_points[174] = vec4(0.03f, -0.565f, 0.0f, 1.0f);
	_points[175] = vec4(0.06f, -0.65f, 0.0f, 1.0f);
	_points[176] = vec4(0.06f, -0.565f, 0.0f, 1.0f);

	_colors[173] = _COLOR_GRAY;
	_colors[174] = _COLOR_GRAY;
	_colors[175] = _COLOR_GRAY;
	_colors[176] = _COLOR_GRAY;

	/////////////////////////////////////////////////////shoot center circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 177; i < 187; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 10) - 0.045f;
		_points[i].y = b* sinf(M_PI*2.0f*i / 10) - 0.645f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////shoot center circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 187; i < 197; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 10) + 0.045f;
		_points[i].y = b* sinf(M_PI*2.0f*i / 10) - 0.645f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}



	///////////////////////////////////////////////////////body
	a = 0.85f;
	b = 0.2f;
	for (int i = 197; i < 217; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 20);
		_points[i].y = b* sinf(M_PI*2.0f*i / 20)-0.2f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BLUEGREEN;
	}


	/////////////////////////////////////////////////////body center yellow
	_points[217] = vec4(-0.85f, -0.18f, 0.0f, 1.0f);
	_points[218] = vec4(-0.85f, -0.22f, 0.0f, 1.0f);
	_points[219] = vec4(0.85f, -0.18f, 0.0f, 1.0f);
	_points[220] = vec4(0.85f, -0.22f, 0.0f, 1.0f);

	_colors[217] = _COLOR_YELLOW;
	_colors[218] = _COLOR_YELLOW;
	_colors[219] = _COLOR_YELLOW;
	_colors[220] = _COLOR_YELLOW;

	/////////////////////////////////////////////////////body center green
	_points[221] = vec4(-0.015f, -0.18f, 0.0f, 1.0f);
	_points[222] = vec4(-0.015f, -0.22f, 0.0f, 1.0f);
	_points[223] = vec4(0.015f, -0.18f, 0.0f, 1.0f);
	_points[224] = vec4(0.015f, -0.22f, 0.0f, 1.0f);

	_colors[221] = _COLOR_BLUEGREEN;
	_colors[222] = _COLOR_BLUEGREEN;
	_colors[223] = _COLOR_BLUEGREEN;
	_colors[224] = _COLOR_BLUEGREEN;

	/////////////////////////////////////////////////////body center green
	_points[225] = vec4(-0.245f, -0.18f, 0.0f, 1.0f);
	_points[226] = vec4(-0.245f, -0.22f, 0.0f, 1.0f);
	_points[227] = vec4(-0.215f, -0.18f, 0.0f, 1.0f);
	_points[228] = vec4(-0.215f, -0.22f, 0.0f, 1.0f);

	_colors[225] = _COLOR_BLUEGREEN;
	_colors[226] = _COLOR_BLUEGREEN;
	_colors[227] = _COLOR_BLUEGREEN;
	_colors[228] = _COLOR_BLUEGREEN;

	/////////////////////////////////////////////////////body center green
	_points[229] = vec4(-0.475f, -0.18f, 0.0f, 1.0f);
	_points[230] = vec4(-0.475f, -0.22f, 0.0f, 1.0f);
	_points[231] = vec4(-0.445f, -0.18f, 0.0f, 1.0f);
	_points[232] = vec4(-0.445f, -0.22f, 0.0f, 1.0f);

	_colors[229] = _COLOR_BLUEGREEN;
	_colors[230] = _COLOR_BLUEGREEN;
	_colors[231] = _COLOR_BLUEGREEN;
	_colors[232] = _COLOR_BLUEGREEN;

	/////////////////////////////////////////////////////body center green
	_points[233] = vec4(-0.705f, -0.18f, 0.0f, 1.0f);
	_points[234] = vec4(-0.705f, -0.22f, 0.0f, 1.0f);
	_points[235] = vec4(-0.675f, -0.18f, 0.0f, 1.0f);
	_points[236] = vec4(-0.675f, -0.22f, 0.0f, 1.0f);

	_colors[233] = _COLOR_BLUEGREEN;
	_colors[234] = _COLOR_BLUEGREEN;
	_colors[235] = _COLOR_BLUEGREEN;
	_colors[236] = _COLOR_BLUEGREEN;


	/////////////////////////////////////////////////////body center green
	_points[237] = vec4(0.245f, -0.18f, 0.0f, 1.0f);
	_points[238] = vec4(0.245f, -0.22f, 0.0f, 1.0f);
	_points[239] = vec4(0.215f, -0.18f, 0.0f, 1.0f);
	_points[240] = vec4(0.215f, -0.22f, 0.0f, 1.0f);

	_colors[237] = _COLOR_BLUEGREEN;
	_colors[238] = _COLOR_BLUEGREEN;
	_colors[239] = _COLOR_BLUEGREEN;
	_colors[240] = _COLOR_BLUEGREEN;

	/////////////////////////////////////////////////////body center green
	_points[241] = vec4(0.475f, -0.18f, 0.0f, 1.0f);
	_points[242] = vec4(0.475f, -0.22f, 0.0f, 1.0f);
	_points[243] = vec4(0.445f, -0.18f, 0.0f, 1.0f);
	_points[244] = vec4(0.445f, -0.22f, 0.0f, 1.0f);

	_colors[241] = _COLOR_BLUEGREEN;
	_colors[242] = _COLOR_BLUEGREEN;
	_colors[243] = _COLOR_BLUEGREEN;
	_colors[244] = _COLOR_BLUEGREEN;

	/////////////////////////////////////////////////////body center green
	_points[245] = vec4(0.705f, -0.18f, 0.0f, 1.0f);
	_points[246] = vec4(0.705f, -0.22f, 0.0f, 1.0f);
	_points[247] = vec4(0.675f, -0.18f, 0.0f, 1.0f);
	_points[248] = vec4(0.675f, -0.22f, 0.0f, 1.0f);

	_colors[245] = _COLOR_BLUEGREEN;
	_colors[246] = _COLOR_BLUEGREEN;
	_colors[247] = _COLOR_BLUEGREEN;
	_colors[248] = _COLOR_BLUEGREEN;
}

void EnemyBoss::Draw() {
	_bulletList->BulletDraw();

	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  //window background
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4); 	//shoot left 1
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);	//window1

	glDrawArrays(GL_TRIANGLE_FAN, 12, 20);	//monster
	glDrawArrays(GL_TRIANGLES, 32, 3);	//monster hand
	glDrawArrays(GL_TRIANGLE_FAN, 35, 20);	//monster eye1
	glDrawArrays(GL_TRIANGLE_FAN, 55, 10);	//monster eye2
	glDrawArrays(GL_TRIANGLE_STRIP, 65, 4);	//monster hand

	glDrawArrays(GL_TRIANGLE_STRIP, 69, 4);	//window2 left
	glDrawArrays(GL_TRIANGLE_STRIP, 73, 4);	//window2 center
	glDrawArrays(GL_TRIANGLE_STRIP, 77, 4); //window2 right
	glDrawArrays(GL_TRIANGLE_FAN, 81, 10); //head

	glDrawArrays(GL_TRIANGLE_STRIP, 91, 4); //shoot left 2-1
	glDrawArrays(GL_TRIANGLE_STRIP, 95, 4); //shoot left 2-2
	glDrawArrays(GL_TRIANGLE_STRIP, 99, 4); //shoot right 2-1
	glDrawArrays(GL_TRIANGLE_STRIP, 103, 4); //shoot right 2-2
	glDrawArrays(GL_TRIANGLE_FAN, 107, 10); //shoot left circle-1
	glDrawArrays(GL_TRIANGLE_FAN, 117, 10); //shoot left circle-2
	glDrawArrays(GL_TRIANGLE_FAN, 127, 10); //shoot right circle-1
	glDrawArrays(GL_TRIANGLE_FAN, 137, 10); //shoot right circle-2
	glDrawArrays(GL_TRIANGLE_STRIP, 147, 4); 	//shoot right 1
	glDrawArrays(GL_TRIANGLE_FAN, 151, 10);     //shoot center bottom gray
	glDrawArrays(GL_TRIANGLE_STRIP, 161, 4); 	//shoot center bottom yellow
	glDrawArrays(GL_TRIANGLE_STRIP, 165, 4); 	//shoot center 1
	glDrawArrays(GL_TRIANGLE_STRIP, 169, 4); //shoot center 2-1
	glDrawArrays(GL_TRIANGLE_STRIP, 173, 4); //shoot center 2-2
	glDrawArrays(GL_TRIANGLE_FAN, 177, 10); //shoot center circle-1
	glDrawArrays(GL_TRIANGLE_FAN, 187, 10); //shoot center circle-2

	glDrawArrays(GL_TRIANGLE_FAN, 197, 20); //body
	glDrawArrays(GL_TRIANGLE_STRIP, 217, 4); //body center yellow
	glDrawArrays(GL_TRIANGLE_STRIP, 221, 4); //body center green
	glDrawArrays(GL_TRIANGLE_STRIP, 225, 4); //body center green
	glDrawArrays(GL_TRIANGLE_STRIP, 229, 4); //body center green
	glDrawArrays(GL_TRIANGLE_STRIP, 233, 4); //body center green
	glDrawArrays(GL_TRIANGLE_STRIP, 237, 4); //body center green
	glDrawArrays(GL_TRIANGLE_STRIP, 241, 4); //body center green
	glDrawArrays(GL_TRIANGLE_STRIP, 245, 4); //body center green

	
	//257
}

int normalTime = 0;
int k = 0;

void EnemyBoss::Attack(float dt) {
	_attackTimer += dt;

	if (_attackTimer >= _attackDuration) {
		_attackTimer = 0.0f;
		switch (_attackState) {
		case Idle:
			_attackDuration = 4.0f;
			_attackState = Normal;
			break;
		case Normal:
			if (_heart <= 22) {
				if (_heart <= 12)
					normalTime += 1;
				else normalTime = 1;
				k = 0;
				switch (normalTime) {
				case 1:
					_attackState = Progressive;
					_attackDuration = 8.0f;
					break;
				case 2:
					_attackState = Explosion;
					_attackDuration = 8.0f;
					normalTime = 0;
				}
			}
			else {
				//_attackDuration = 4.0f;
				k = 0;
			}
			break;
		case Progressive:
			_attackState = Normal;
			_attackDuration = 4.0f;
			k = 0;
			break;
		case Explosion:
			_attackState = Normal;
			_attackDuration = 4.0f;
			k = 0;
			break;
		default:
			break;
		}
	}

	switch (_attackState) {
		case Normal:
			//進入Normal模式
			AttackNormal();
			break;
		case Progressive:
			AttackProgressive(k);
			break;
		case Explosion:
			AttackExplosion();
			break;
	}
}

void EnemyBoss::AttackNormal(){
	mat4 mat = _transform->_mxTRS;
	mat._m[1].w -= 0.3f;
	float fBSpeed = 0.65f;

	if (_attackTimer >= 1.5f*k+0.5f && k<=2) {

		switch (k) {
			case 1:
				_bulletList->BulletShoot(mat, _bIX, -_bIY);
				mat._m[0].w -= 0.8f;
				_bulletList->BulletShoot(mat, _bIX, -_bIY);
				mat = _transform->_mxTRS;
				mat._m[1].w -= 0.3f;
				mat._m[0].w += 0.8f;
				_bulletList->BulletShoot(mat, _bIX, -_bIY);
				break;
			default:
				_bulletList->BulletShoot(mat, _bIX, -_bIY);
				mat._m[0].w -= 0.6f;
				_bulletList->BulletShoot(mat, _bIX, -_bIY);
				mat = _transform->_mxTRS;
				mat._m[1].w -= 0.3f;
				mat._m[0].w += 0.6f;
				_bulletList->BulletShoot(mat, _bIX, -_bIY);
				break;
		}

		_bIX = 1.0f;
		_bIY = 1.75f;

		for (int i = 0; i < 3; i++)
		{
			_bIY -= 0.025f;
			mat = _transform->_mxTRS;
			mat._m[1].w -= 0.3f;
			mat._m[0].w -= 0.3f*i;
			_bulletList->BulletShoot(mat, -_bIX, -_bIY, fBSpeed);
			mat = _transform->_mxTRS;
			mat._m[1].w -= 0.3f;
			mat._m[0].w += 0.3f*i;
			_bulletList->BulletShoot(mat, _bIX, -_bIY, fBSpeed);
			fBSpeed -= 0.001f;
		}

		_bIX = 0.0f;
		_bIY = 1.0f;
		k++;
	}
}

void EnemyBoss::AttackProgressive(int &k) {
	mat4 mat = _transform->_mxTRS;
	mat._m[1].w -= 0.3f;

	if (_attackTimer >= 0.5f*k+0.5f) {
		_bulletList->BulletShoot(mat, _bIX, -_bIY);
		k++;
	}
}

void EnemyBoss::AttackExplosion() {
	mat4 mat = _transform->_mxTRS;

	if (_attackTimer >= 1.0f && !_isExploShoot) {
		for (int i = 0; i < 30; i++)
		{
			_bulletList->BulletShoot(mat, _bIX, -_bIY,1.0f, true);
		}
		_isExploShoot = true;
	}

}

bool isLeft = true;
void EnemyBoss::AutoTranslate(float dt) {
	mat4 mxTra;
	mat4 mxRot;

	switch (_attackState) {
	case Progressive:
		if (isLeft) {
			_translateTimer -= dt;
			_btx = _translateTimer*_fspeed;
			if (_btx <= -2.0f) {
				isLeft = false;
			}
		}
		else if (!isLeft) {
			_translateTimer += dt;
			_btx = _translateTimer*_fspeed;
			if (_btx >= 2.0f) {
				isLeft = true;
			}
		}
		break;
	case Idle:
		_bty = _attackTimer*-_fspeed;
		break;
	default:
		/*_btx = 0;
		_bty = 0;*/
		break;
	}

	mxTra = Translate(_btx, _bty, 0.0f);

	_transform->SetTRSMatrix(mxTra*_transform->_mxOri);
}

void EnemyBoss::Hurt() {
	_heart--;
	printf("boss heart = %d\n",_heart);
	if (_heart <= 0) {
		_isDead = true;
		_bulletList->ResetBulletList();
	}
}

void EnemyBoss::Reset() {
	_transform->Reset();
	_isDead = false;
	_initFlag = false;
	_isDefaultEnemy = true;

	_attackState = Idle;
	_ftottime = 0.0f;
	_attackTimer = 0;
	_attackDuration = 1.25f;
	_bIX = 0.0f;
	_bIY = 1.0f;
	_translateTimer = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;
	_isExploShoot = false;
	_heart = 30;
}