#include "PBoat.h"
#include "Bullet.h"
#include "EnemyManager.h"


mat4 resetMat = mat4(	1.0, 0.0, 0.0, 0.0,
						0.0, 1.0, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, 3.0, 0.0, 1.0	);

PBoat::PBoat(mat4 &mxView, mat4 &mxProjection) {
	_isDefense = true;
	_isDead = false;
	_colliderSize = new float[2];
	_colliderSize[0] = 0.175f;
	_colliderSize[1] = 0.2f;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, BTOTPOINT_NUM, _points,_colors);
	_defense = new Defense(mxView, mxProjection, 0.35f);
	_bulletList = new BulletList(mxView, mxProjection, 50, 'p',1.0f);
}

PBoat::~PBoat() {
	if(_transform != NULL) delete _transform;
	if (_defense != NULL) delete _defense;
	if (_bulletList != NULL) delete _bulletList;
}

void PBoat::GetComponent(EnemyManager *getEnemyManager) {
	_getEnemyManager = getEnemyManager;
}

void PBoat::SetPoint() {
	_points = new vec4[BTOTPOINT_NUM];
	_colors = new vec4[BTOTPOINT_NUM];
	//pBRSide
	_points[0] = vec4(0.150f, -0.12f, 0.0, 1.0f);
	_points[1] = vec4(0.230f, -0.12f, 0.0, 1.0f);
	_points[2] = vec4(0.150f, 0.02f, 0.0, 1.0f);

	//pBLSide
	_points[3] = vec4(-0.150f, -0.12f, 0.0, 1.0f);
	_points[4] = vec4(-0.230f, -0.12f, 0.0, 1.0f);
	_points[5] = vec4(-0.150f, 0.02f, 0.0, 1.0f);

	//pBBody
	_points[6] = vec4(-0.150f, -0.16f, 0.0, 1.0f);
	_points[7] = vec4(-0.150f, 0.16f, 0.0, 1.0f);
	_points[8] = vec4(0.150f, -0.16f, 0.0, 1.0f);
	_points[9] = vec4(0.150f, 0.16f, 0.0, 1.0f);

	//cBRSide
	_colors[0] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	_colors[1] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	_colors[2] = vec4(0.78f, 0.208f, 0.22f, 1.0f);

	//cBLSide
	_colors[3] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	_colors[4] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	_colors[5] = vec4(0.78f, 0.208f, 0.22f, 1.0f);

	//cBBody
	_colors[6] = vec4(0.94f, 0.94f, 0.94f, 1.0f);
	_colors[7] = vec4(0.94f, 0.94f, 0.94f, 1.0f);
	_colors[8] = vec4(0.94f, 0.94f, 0.94f, 1.0f);
	_colors[9] = vec4(0.94f, 0.94f, 0.94f, 1.0f);
	//pBCenter
	for (int i = 10; i < 30; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / BCPOINT_NUM); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / BCPOINT_NUM) - 0.02f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BACKGROUND;
	}

	//pbTop
	for (int i = 30; i < 41; i++) {
		_points[i].x = 0.15f * cosf(M_PI*2.0f*(float)(i) / BCPOINT_NUM); //2拍乘以該點分之總點
		_points[i].y = -0.15f * sinf(M_PI*2.0f*(float)(i) / BCPOINT_NUM) + 0.15f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	}

	//pBFire Yellow
	for (int i = 50; i > 40; i--) {
		_points[i].x = 0.016f*(i - 51) + 0.01f;
		_points[i].y = 10.0f*(_points[i].x)*(_points[i].x) + 0.025f*(_points[i].x) - 0.37f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.87f, 0.58f, 0.22f, 1.0f);
	}

	_points[51].x = 0.0f;
	_points[51].y = -0.37f;
	_points[51].w = 1.0f;
	_colors[51] = vec4(0.87f, 0.58f, 0.22f, 1.0f);

	for (int i = 52; i < 62; i++) {
		_points[i].x = 0.016f*(i - 51) - 0.01f;;
		_points[i].y = 10.0f*(_points[i].x)*(_points[i].x) - 0.025f*(_points[i].x) - 0.37f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.87f, 0.58f, 0.22f, 1.0f);
	}

	//pBFire red
	for (int i = 71; i > 61; i--) {
		_points[i].x = 0.008f*(i - 72);
		_points[i].y = 20.0f*(_points[i].x)*(_points[i].x) + 0.05f*(_points[i].x) - 0.275f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	}

	_points[72].x = 0.0f;
	_points[72].y = -0.275f;
	_points[72].w = 1.0f;
	_colors[72] = vec4(0.78f, 0.208f, 0.22f, 1.0f);

	for (int i = 73; i < 83; i++) {
		_points[i].x = 0.008f*(i - 72);
		_points[i].y = 20.0f*(_points[i].x)*(_points[i].x) - 0.05f*(_points[i].x) - 0.275f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.78f, 0.208f, 0.22f, 1.0f);
	}

}

void PBoat::Draw() {
	if (!_isDead) {
		_bulletList->BulletDraw();
		if (_isDefense == true)	_defense->Draw('c');
		_transform->Draw();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, BSPOINT_NUM);
		glDrawArrays(GL_TRIANGLE_STRIP, BSPOINT_NUM, BSPOINT_NUM);
		glDrawArrays(GL_TRIANGLE_STRIP, BSPOINT_NUM * 2, BBPOINT_NUM);
		glDrawArrays(GL_TRIANGLE_FAN, BSPOINT_NUM * 2 + BBPOINT_NUM, BCPOINT_NUM);
		glDrawArrays(GL_TRIANGLE_FAN, BSPOINT_NUM * 2 + BBPOINT_NUM + BCPOINT_NUM, BTPOINT_NUM);
		glDrawArrays(GL_TRIANGLE_FAN, BSPOINT_NUM * 2 + BBPOINT_NUM + BCPOINT_NUM + BTPOINT_NUM, BPPOINT_NUM);
		glDrawArrays(GL_TRIANGLE_FAN, BSPOINT_NUM * 2 + BBPOINT_NUM + BCPOINT_NUM + BTPOINT_NUM + BPPOINT_NUM, BPPOINT_NUM);
	}
}

void PBoat::Update(float delta,bool isBoatShoot) {
	if (!_isDead) {
		_timer += delta;
		if (isBoatShoot == true) {
			if (_timer >= 0.3f) {
				_timer = 0.0f;
				_bulletList->BulletShoot(_transform->_mxTRS); //player射出子彈，傳入player座標
			}
		}

		if (_isDefense == true)	_defense->_transform->SetTRSMatrix(_transform->_mxTRS);

		_bulletList->Update(delta,_getEnemyManager);
	}
}

void PBoat::Hurt() {
	if (_isDefense)	_isDefense = false;
	else {
		_transform->SetTRSMatrix(resetMat);
		_isDead = true;
	}
}

void PBoat::Revival() {	//外掛
	_transform->Reset();
	_isDead = false;
	_isDefense = true;
}