#include "Enemy.h"
#include "PBoat.h"
#include "Bullet.h"

Enemy::Enemy(mat4 &mxView, mat4 &mxProjection, float fspeed,float attackDuration, int pointNum, char type){
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
}

void Enemy::Action(float dt, PBoat *getPBoat) {
	_ftottime += dt;
	Attack(dt);
	AutoTranslate(dt);		

	_bulletList->Update(dt, getPBoat);
}





/////////EnemySmall
EnemySmall::EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed, float attackDuration, int pointNum, char type) :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	_circlecollider = 0.7f;	//fix
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
	_circlecollider = 0.7f;	//fix
	_bulletList = new BulletList(mxView, mxProjection, 20, 'm', 1.0f);
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
	_attackState = Normal;
	_bulletList = new BulletList(mxView, mxProjection, 30, 'b', 1.0f);
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
};

void EnemyBoss::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	//Body
	_points[0] = vec4(-1.0f, 0.5f, 0.0f, 1.0f);
	_points[1] = vec4(-1.0f, -0.5f, 0.0f, 1.0f);
	_points[2] = vec4(1.0f, 0.5f, 0.0f, 1.0f);
	_points[3] = vec4(1.0f, -0.5f, 0.0f, 1.0f);

	////pshoot1
	//_points[4] = vec4(-0.14f, -0.15f, 0.0f, 1.0f);
	//_points[5] = vec4(0.14f, -0.15f, 0.0f, 1.0f);
	//_points[6] = vec4(-0.075f, -0.27f, 0.0f, 1.0f);
	//_points[7] = vec4(0.075f, -0.27f, 0.0f, 1.0f);

	////pshoot2
	//_points[8] = vec4(0.15f, -0.149f, 0.0f, 1.0f);
	//_points[9] = vec4(0.15f, 0.149f, 0.0f, 1.0f);
	//_points[10] = vec4(0.27f, -0.075f, 0.0f, 1.0f);
	//_points[11] = vec4(0.27f, 0.075f, 0.0f, 1.0f);

	////pshoot3
	//_points[12] = vec4(-0.14f, 0.15f, 0.0f, 1.0f);
	//_points[13] = vec4(0.14f, 0.15f, 0.0f, 1.0f);
	//_points[14] = vec4(-0.075f, 0.27f, 0.0f, 1.0f);
	//_points[15] = vec4(0.075f, 0.27f, 0.0f, 1.0f);

	////pshoot4
	//_points[16] = vec4(-0.15f, -0.149f, 0.0f, 1.0f);
	//_points[17] = vec4(-0.15f, 0.149f, 0.0f, 1.0f);
	//_points[18] = vec4(-0.27f, -0.075f, 0.0f, 1.0f);
	//_points[19] = vec4(-0.27f, 0.075f, 0.0f, 1.0f);

	//cBody
	_colors[0] = _COLOR_BLACK;
	_colors[1] = _COLOR_BLACK;
	_colors[2] = _COLOR_BLACK;
	_colors[3] = _COLOR_BLACK;

	////cshoot
	//_colors[4] = _COLOR_YELLOW;
	//_colors[5] = _COLOR_YELLOW;
	//_colors[6] = _COLOR_YELLOW;
	//_colors[7] = _COLOR_YELLOW;

	////cshoot
	//_colors[8] = _COLOR_YELLOW;
	//_colors[9] = _COLOR_YELLOW;
	//_colors[10] = _COLOR_YELLOW;
	//_colors[11] = _COLOR_YELLOW;

	////cshoot
	//_colors[12] = _COLOR_YELLOW;
	//_colors[13] = _COLOR_YELLOW;
	//_colors[14] = _COLOR_YELLOW;
	//_colors[15] = _COLOR_YELLOW;

	////cshoot
	//_colors[16] = _COLOR_YELLOW;
	//_colors[17] = _COLOR_YELLOW;
	//_colors[18] = _COLOR_YELLOW;
	//_colors[19] = _COLOR_YELLOW;

	////center
	//for (int i = 20; i < _pointNum; i++) {
	//	_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)i / 10.0f); //2拍乘以該點分之總點
	//	_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)i / 10.0f);
	//	_points[i].w = 1.0f;
	//	_colors[i] = _COLOR_YELLOW;
	//}
}

int normalTime = 0;
void EnemyBoss::Attack(float dt) {
	_attackTimer += dt;
	if (_attackTimer >= 2.0) {
		_attackTimer = 0.0f;
		if (_attackState == Normal) {
			//進入Normal模式
			AttackNormal();
			/*normalTime += 1;
			switch (normalTime) {
				case 1:
					_attackState = Progressive;
					break;
				case 2:
					_attackState = Explosion;
					break;
			}*/
		}
		else if (_attackState == Progressive) {
			//進入Progressive模式
			AttackProgressive();
			_attackState = Normal;
			normalTime += 1;
		}
		else {
			//進入Explosion模式
			AttackExplosion();
			_attackState = Normal;
			normalTime = 0;
		}
	}
}

void EnemyBoss::AttackNormal(){
	mat4 mat = _transform->_mxTRS;
	float fBSpeed = 0.65f;

	_bulletList->BulletShoot(mat, _iX, -_iY);
	mat._m[0].w -= 0.4f;
	_bulletList->BulletShoot(mat, _iX, -_iY);
	mat = _transform->_mxTRS;
	mat._m[0].w += 0.4f;
	_bulletList->BulletShoot(mat, _iX, -_iY);

	_iX = 1.0f;
	_iY = 1.75f;

	for (int i = 0; i < 3; i++)
	{
		_iY -= 0.25f;
		mat = _transform->_mxTRS;
		mat._m[0].w -= 0.3f*i;
		_bulletList->BulletShoot(mat, -_iX, -_iY, fBSpeed);
		mat = _transform->_mxTRS;
		mat._m[0].w += 0.3f*i;
		_bulletList->BulletShoot(mat, _iX, -_iY,fBSpeed);
		fBSpeed -= 0.001f;
	}

	_iX = 0.0f;
	_iY = 1.0f;
}

void EnemyBoss::AttackProgressive() {

}

void EnemyBoss::AttackExplosion() {

}

void EnemyBoss::AutoTranslate(float dt) {
	//mat4 mxTra;
	//mat4 mxRot;

	//if (_transform->_mxTRS._m[1].w >= 0.0f) {
	//	_translateTimer += dt;
	//	_bty += dt*_fspeed;
	//}
	//else {
	//	_isStop = true;
	//	_rotateTimer += dt;

	//	if (_rotateTimer >= _rotateDuration) {
	//		//開始轉
	//		if (_rotateTimer <= 1.5f + _rotateDuration)
	//			_fZAngle += 30.0f * dt;
	//		else {
	//			_rotateTimer = 0.0f;
	//			if (_iX == 0.0f) {
	//				_iX = 1.0f;
	//				_iY = 1.0f;
	//			}
	//			else {
	//				_iX = 0.0f;
	//				_iY = 1.0f;
	//			}
	//		}
	//	}
	//}

	//if (_fZAngle != 0.0f)
	//	mxRot = RotateZ(_fZAngle);

	//mxTra = Translate(_btx, _bty, 0.0f);

	//_transform->SetTRSMatrix(mxTra*_transform->_mxOri*mxRot);
}

void EnemyBoss::Draw() {
	_bulletList->BulletDraw();

	_transform->Draw();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 10);
}

void EnemyBoss::Hurt() {
	_isDead = true;
}

void EnemyBoss::Reset() {
	_transform->Reset();
	_isDead = false;
	_initFlag = false;

	_ftottime = 0.0f;
	_attackTimer = 0;
	/*_rotateTimer = 0.0f;
	_translateTimer = 0.0f;
	_iX = 0.0f;
	_iY = 1.0f;
	_isStop = false;
	_fZAngle = 0.0f;
	_btx = 0.0f;
	_bty = 0.0f;*/
}