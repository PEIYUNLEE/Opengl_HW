#include "Enemy.h"

Enemy::Enemy(mat4 &mxView, mat4 &mxProjection, float fspeed,float attackDuration, int pointNum, char type){
	_type = type;
	_ftottime = 0;
	_attackTimer = 0;
	_attakDuration = attackDuration;
	_pointNum = pointNum;
	_fspeed = fspeed;

	_bulletList = new BulletList(mxView, mxProjection, 10 , 'e');
}

Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
	if (_bulletList != NULL) delete _bulletList;
}
void Enemy::Action(float dt) {
	_ftottime += dt;
	Attack(dt);
	//AutoTranslate(_ftottime);			//fix

	_bulletList->Update(dt);
}

void Enemy::Reset() {
	_transform->Reset();
	_ftottime = 0;
	_attackTimer = 0;
}




/////////EnemySmall

void EnemySmall::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	for (int i = 0; i < _pointNum; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / _pointNum); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / _pointNum);
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

void EnemySmall::Attack(float dt){
	_attackTimer += dt;
	if (_attackTimer >= _attakDuration) {
		Print(_attackTimer);
		_attackTimer = 0.0f;
		_bulletList->BulletShoot(_transform->_mxTRS);
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, _pointNum);
}


