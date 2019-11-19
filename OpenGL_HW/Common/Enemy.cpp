#include "Enemy.h"
#include "PBoat.h"
#include "Bullet.h"

Enemy::Enemy(mat4 &mxView, mat4 &mxProjection, float fspeed,float attackDuration, int pointNum, char type){
	_type = type;
	_ftottime = 0;
	_attackTimer = 0;
	_attakDuration = attackDuration;
	_pointNum = pointNum;
	_fspeed = fspeed;
	_circlecollider = 0.07f;
	_isDead = false;
	_initFlag = false;
}

Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
	if (_bulletList != NULL) delete _bulletList;
}

void Enemy::Action(float dt, PBoat *getPBoat) {
	_ftottime += dt;
	Attack(dt);
	AutoTranslate(_ftottime);		

	_bulletList->Update(dt, getPBoat);
}

void Enemy::Reset() {
	_transform->Reset();
	_ftottime = 0.0f;
	_attackTimer = 0;
	_isDead = false;
	_initFlag = false;
}




/////////EnemySmall
EnemySmall::EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_bulletList = new BulletList(mxView, mxProjection, 10, 'e', 1.25f);
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
};

void EnemySmall::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	//Body
	_points[0] = vec4(-0.15f, 0.225f, 0.0f, 1.0f);
	_points[1] = vec4(-0.15f, -0.075f, 0.0f, 1.0f);
	_points[2] = vec4(0.15f, 0.225f, 0.0f, 1.0f);
	_points[3] = vec4(0.15f, -0.075f, 0.0f, 1.0f);

	//pshoot
	_points[4] = vec4(-0.15f, -0.075f, 0.0f, 1.0f);
	_points[5] = vec4(0.15f, -0.075f, 0.0f, 1.0f);
	_points[6] = vec4(-0.075f, -0.195f, 0.0f, 1.0f);
	_points[7] = vec4(0.075f, -0.195f, 0.0f, 1.0f);

	//cBody
	_colors[0] = _COLOR_BLACK;
	_colors[1] = _COLOR_BLACK;
	_colors[2] = _COLOR_BLACK;
	_colors[3] = _COLOR_BLACK;

	//cshoot
	_colors[4] = _COLOR_YELLOW;
	_colors[5] = _COLOR_YELLOW;
	_colors[6] = _COLOR_YELLOW;
	_colors[7] = _COLOR_YELLOW;

	//center
	for (int i = 8; i < _pointNum; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)i / 10.0f); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)i / 10.0f)+0.07f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_YELLOW;
	}
}

void EnemySmall::Attack(float dt){
	_attackTimer += dt;
	if (!_initFlag&&_attackTimer>=0.5f) {
		_bulletList->BulletShoot(_transform->_mxTRS,0.0f,-1.0f);
		_initFlag = true;
	}
	if (_attackTimer >= _attakDuration) {
		_attackTimer = 0.0f;
		_bulletList->BulletShoot(_transform->_mxTRS, 0.0f, -1.0f);
	}
}

void EnemySmall::AutoTranslate(float ftottime) {
	mat4 mxTra;
	GLfloat btx = 0.0f;
	GLfloat bty = 0.0f;

	bty = ftottime*_fspeed;
	mxTra = Translate(btx, bty, 0.0f);
	_transform->SetTRSMatrix(mxTra*_transform->_mxOri);
}

void EnemySmall::Draw() {
	_bulletList->BulletDraw();

	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 10);
}

void EnemySmall::Hurt() {
	_isDead = true;
}



/////////EnemyMiddle
EnemyMiddle::EnemyMiddle(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {

	_bulletList = new BulletList(mxView, mxProjection, 50, 'm', 1.25f);
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
};

void EnemyMiddle::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	//Body
	_points[0] = vec4(-0.15f, 0.15f, 0.0f, 1.0f);
	_points[1] = vec4(-0.15f, -0.15f, 0.0f, 1.0f);
	_points[2] = vec4(0.15f, 0.15f, 0.0f, 1.0f);
	_points[3] = vec4(0.15f, -0.15f, 0.0f, 1.0f);

	//pshoot1
	_points[4] = vec4(-0.14f, -0.15f, 0.0f, 1.0f);
	_points[5] = vec4(0.14f, -0.15f, 0.0f, 1.0f);
	_points[6] = vec4(-0.075f, -0.27f, 0.0f, 1.0f);
	_points[7] = vec4(0.075f, -0.27f, 0.0f, 1.0f);

	//pshoot2
	_points[8] = vec4(0.15f, -0.149f, 0.0f, 1.0f);
	_points[9] = vec4(0.15f, 0.149f, 0.0f, 1.0f);
	_points[10] = vec4(0.27f, -0.075f, 0.0f, 1.0f);
	_points[11] = vec4(0.27f, 0.075f, 0.0f, 1.0f);

	//pshoot3
	_points[12] = vec4(-0.14f, 0.15f, 0.0f, 1.0f);
	_points[13] = vec4(0.14f, 0.15f, 0.0f, 1.0f);
	_points[14] = vec4(-0.075f, 0.27f, 0.0f, 1.0f);
	_points[15] = vec4(0.075f, 0.27f, 0.0f, 1.0f);

	//pshoot4
	_points[16] = vec4(-0.15f, -0.149f, 0.0f, 1.0f);
	_points[17] = vec4(-0.15f, 0.149f, 0.0f, 1.0f);
	_points[18] = vec4(-0.27f, -0.075f, 0.0f, 1.0f);
	_points[19] = vec4(-0.27f, 0.075f, 0.0f, 1.0f);

	//cBody
	_colors[0] = _COLOR_BLACK;
	_colors[1] = _COLOR_BLACK;
	_colors[2] = _COLOR_BLACK;
	_colors[3] = _COLOR_BLACK;

	//cshoot
	_colors[4] = _COLOR_YELLOW;
	_colors[5] = _COLOR_YELLOW;
	_colors[6] = _COLOR_YELLOW;
	_colors[7] = _COLOR_YELLOW;

	//cshoot
	_colors[8] = _COLOR_YELLOW;
	_colors[9] = _COLOR_YELLOW;
	_colors[10] = _COLOR_YELLOW;
	_colors[11] = _COLOR_YELLOW;

	//cshoot
	_colors[12] = _COLOR_YELLOW;
	_colors[13] = _COLOR_YELLOW;
	_colors[14] = _COLOR_YELLOW;
	_colors[15] = _COLOR_YELLOW;

	//cshoot
	_colors[16] = _COLOR_YELLOW;
	_colors[17] = _COLOR_YELLOW;
	_colors[18] = _COLOR_YELLOW;
	_colors[19] = _COLOR_YELLOW;

	//center
	for (int i = 20; i < _pointNum; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)i / 10.0f); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)i / 10.0f);
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_YELLOW;
	}
}



float iX = 0.0f;
float iY = -1.0f;
void EnemyMiddle::Attack(float dt) {
	_attackTimer += dt;
	if (!_initFlag&&_attackTimer >= 0.5f) {
		_bulletList->BulletShoot(_transform->_mxTRS, iX, iY);
		_bulletList->BulletShoot(_transform->_mxTRS, iY, iX);
		_bulletList->BulletShoot(_transform->_mxTRS, iX, -iY);
		_bulletList->BulletShoot(_transform->_mxTRS, -iY, iX);
		_initFlag = true;
	}
	if (_attackTimer >= _attakDuration) {
		_attackTimer = 0.0f;
		_bulletList->BulletShoot(_transform->_mxTRS, iX, iY);
		_bulletList->BulletShoot(_transform->_mxTRS, iY, iX);
		_bulletList->BulletShoot(_transform->_mxTRS, iX, -iY);
		_bulletList->BulletShoot(_transform->_mxTRS, -iY, iX);
	}
}

void EnemyMiddle::AutoTranslate(float ftottime) {
	/*mat4 mxTra;
	GLfloat btx = 0.0f;
	GLfloat bty = 0.0f;

	bty = ftottime*_fspeed;
	mxTra = Translate(btx, bty, 0.0f);
	_transform->SetTRSMatrix(mxTra*_transform->_mxOri);*/
}

void EnemyMiddle::Draw() {
	_bulletList->BulletDraw();

	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 10);
}

void EnemyMiddle::Hurt() {
	_isDead = true;
}

