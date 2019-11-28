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
	_colliderSize[0] = 0.7f;
	_colliderSize[1] = 0.7f;
	_bulletList = new BulletList(mxView, mxProjection, 10, 'e', _COLOR_YELLOW, 1.25f);
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
	if (_attackTimer >= _attackDuration) {
		_attackTimer = 0.0f;
		_bulletList->BulletShoot(_transform->_mxTRS, 0.0f, -1.0f);
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
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 10);
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
}



/////////EnemyMiddle
EnemyMiddle::EnemyMiddle(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_attackDuration = 0.5f;
	_colliderSize[0] = 0.7f;
	_colliderSize[1] = 0.7f;
	_bulletList = new BulletList(mxView, mxProjection, 20, 'm',  _COLOR_YELLOW, 1.0f);
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
		_points[i].x = 0.07f *cosf(M_PI*2.0f*(float)i / 10.0f); //2拍乘以該點分之總點
		_points[i].y = 0.07f *sinf(M_PI*2.0f*(float)i / 10.0f);
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_YELLOW;
	}
}

void EnemyMiddle::Attack(float dt) {
	if (!_isStop) {
		_attackTimer += dt;
		if (_attackTimer >= _attackDuration) {
			_attackDuration = 2.0f;
			_attackTimer = 0.0f;
			_bulletList->BulletShoot(_transform->_mxTRS, _iX, _iY);
			_bulletList->BulletShoot(_transform->_mxTRS, -_iX, -_iY);
			mat4 mat = _transform->_mxTRS;
			mat._m[0].w += 0.2f;
			_bulletList->BulletShoot(mat, _iX, _iY);
			_bulletList->BulletShoot(mat, -_iX, -_iY);
			mat._m[0].w -= 0.4f;
			_bulletList->BulletShoot(mat, _iX, _iY);
			_bulletList->BulletShoot(mat, -_iX, -_iY);
		}
	}
	else {
		_attackTimer += dt;
		_attackDuration = 3.0f;
		if (_attackTimer >= _attackDuration) {
			_attackTimer = 0.0f;
			mat4 mat = _transform->_mxTRS;
			mat._m[1].w += 0.25f*_iY;
			mat._m[0].w += 0.25f*_iX;
			_bulletList->BulletShoot(mat, _iX, _iY);
			mat = _transform->_mxTRS;
			mat._m[0].w += 0.25f*_iY;
			mat._m[1].w -= 0.25f*_iX;
			_bulletList->BulletShoot(mat, _iY, -_iX);
			mat = _transform->_mxTRS;
			mat._m[1].w -= 0.25f*_iY;
			mat._m[0].w -= 0.25f*_iX;
			_bulletList->BulletShoot(mat, -_iX, -_iY);
			mat = _transform->_mxTRS;
			mat._m[0].w -= 0.25f*_iY;
			mat._m[1].w += 0.25f*_iX;
			_bulletList->BulletShoot(mat, -_iY, _iX);
		}
	}
}

void EnemyMiddle::AutoTranslate(float dt) {
	mat4 mxTra;
	mat4 mxRot;

	if (_transform->_mxTRS._m[1].w >= 0.0f) {
		_translateTimer += dt;
		_bty += dt*_fspeed;
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
				if (_iX == 0.0f) {
					_iX = 1.0f;
					_iY = 1.0f;
				}
				else {
					_iX = 0.0f;
					_iY = 1.0f;
				}
			}
		}
	}

	if (_fZAngle != 0.0f)
		mxRot = RotateZ(_fZAngle);

	mxTra = Translate(_btx, _bty, 0.0f);

	_transform->SetTRSMatrix(mxTra*_transform->_mxOri*mxRot );
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

void EnemyMiddle::Reset() {
	_transform->Reset();
	_isDead = false;
	_initFlag = false;

	_ftottime = 0.0f;
	_attackTimer = 0;
	_rotateTimer = 0.0f;
	_translateTimer = 0.0f;
	_iX = 0.0f;
	_iY = 1.0f;
	_isStop = false;
	_fZAngle = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;
}


/////////EnemyBoss
EnemyBoss::EnemyBoss(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_colliderSize[0] = 0.8f;
	_colliderSize[1] = 0.5f;
	_attackState = Idle;
	_attackDuration = 1.25f;
	_iX = 0.0f;
	_iY = 1.0f;
	_translateTimer = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;
	_isExploShoot = false;
	_pointNum = 249;
	_bulletList = new BulletList(mxView, mxProjection, 50, 'b', _COLOR_YELLOW, 1.0f);
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
		_points[i].x = a* cosf(M_PI*2.0f*i / 20);
		_points[i].y = b* sinf(M_PI*2.0f*i / 20) + 0.09f;
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
		_points[i].x = a* cosf(M_PI*2.0f*i / 20);
		_points[i].y = b* sinf(M_PI*2.0f*i / 20) + 0.13f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_WHITE;
	}

	////////////////////////////////////////////////////monster EYE2
	a = 0.035f;
	b = 0.035f;
	for (int i = 55; i < 65; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 10);
		_points[i].y = b* sinf(M_PI*2.0f*i / 10) + 0.1275f;
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
		_points[i].x = a* cosf(M_PI*2.0f*(i - 80.5) / 20);
		_points[i].y = b* sinf(M_PI*2.0f*(i - 80.5) / 20) + 0.285f;
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
		_points[i].x = a* cosf(M_PI*2.0f*i / 10)-0.595f;
		_points[i].y = b* sinf(M_PI*2.0f*i / 10)-0.52f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}

	/////////////////////////////////////////////////////shoot left circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 117; i < 127; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 10) - 0.505f;
		_points[i].y = b* sinf(M_PI*2.0f*i / 10) - 0.52f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_GRAY;
	}


	/////////////////////////////////////////////////////shoot right circle
	a = 0.035f;
	b = 0.035f;
	for (int i = 127; i < 137; i++)
	{
		_points[i].x = a* cosf(M_PI*2.0f*i / 10) + 0.595f;
		_points[i].y = b* sinf(M_PI*2.0f*i / 10) - 0.52f;
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
		if (_attackState == Idle) {
			_attackDuration = 4.0f;
			_attackState = Normal;
		}
		else if (_attackState == Normal) {
			normalTime += 1;
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
		else if (_attackState == Progressive) {
			_attackState = Normal;
			_attackDuration = 4.0f;
			k = 0;
		}
		else {
			_attackState = Normal;
			_attackDuration = 4.0f;
			k = 0;
			_isExploShoot = false;
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
				_bulletList->BulletShoot(mat, _iX, -_iY);
				mat._m[0].w -= 0.8f;
				_bulletList->BulletShoot(mat, _iX, -_iY);
				mat = _transform->_mxTRS;
				mat._m[1].w -= 0.3f;
				mat._m[0].w += 0.8f;
				_bulletList->BulletShoot(mat, _iX, -_iY);
				break;

			default:
				_bulletList->BulletShoot(mat, _iX, -_iY);
				mat._m[0].w -= 0.6f;
				_bulletList->BulletShoot(mat, _iX, -_iY);
				mat = _transform->_mxTRS;
				mat._m[1].w -= 0.3f;
				mat._m[0].w += 0.6f;
				_bulletList->BulletShoot(mat, _iX, -_iY);
				break;
		}

		_iX = 1.0f;
		_iY = 1.75f;

		for (int i = 0; i < 3; i++)
		{
			_iY -= 0.025f;
			mat = _transform->_mxTRS;
			mat._m[1].w -= 0.3f;
			mat._m[0].w -= 0.3f*i;
			_bulletList->BulletShoot(mat, -_iX, -_iY, fBSpeed);
			mat = _transform->_mxTRS;
			mat._m[1].w -= 0.3f;
			mat._m[0].w += 0.3f*i;
			_bulletList->BulletShoot(mat, _iX, -_iY, fBSpeed);
			fBSpeed -= 0.001f;
		}

		_iX = 0.0f;
		_iY = 1.0f;
		k++;
	}
}

void EnemyBoss::AttackProgressive(int &k) {
	mat4 mat = _transform->_mxTRS;
	mat._m[1].w -= 0.3f;

	if (_attackTimer >= 0.5f*k+0.5f) {
		_bulletList->BulletShoot(mat, _iX, -_iY);
		k++;
	}
}

void EnemyBoss::AttackExplosion() {
	mat4 mat = _transform->_mxTRS;

	if (_attackTimer >= 1.0f && !_isExploShoot) {
		for (int i = 0; i < 30; i++)
		{
			_bulletList->BulletShoot(mat, _iX, -_iY,1.0f, true);
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
	//_isDead = true;
}

void EnemyBoss::Reset() {
	_transform->Reset();
	_isDead = false;
	_initFlag = false;

	_ftottime = 0.0f;
	_attackTimer = 0;
}