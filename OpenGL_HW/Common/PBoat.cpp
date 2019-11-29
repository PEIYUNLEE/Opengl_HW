#include "PBoat.h"
#include "Bullet.h"
#include "EnemyManager.h"


mat4 resetMat = mat4(	1.0, 0.0, 0.0, 0.0,
						0.0, 1.0, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, 3.0, 0.0, 1.0	);

PBoat::PBoat(mat4 &mxView, mat4 &mxProjection) {
	//_isDefense = true;
	_playerState = PBoat::NORMAL;
	_colliderSize = new float[2];
	_colliderSize[0] = 0.13f;
	_colliderSize[1] = 0.19f;
	_timer = 0.0f;
	_hurtTimer = 0.0f;
	_heart = 3;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, BTOTPOINT_NUM, _points,_colors);
	//_defense = new Defense(mxView, mxProjection, 0.35f);
	_bulletList = new BulletList(mxView, mxProjection, 50, 'p', _COLOR_RED ,1.0f);
}

PBoat::~PBoat() {
	if(_transform != NULL) delete _transform;
	//if (_defense != NULL) delete _defense;
	if (_bulletList != NULL) delete _bulletList;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
	if (_colliderSize != NULL) delete[] _colliderSize;
}

void PBoat::GetComponent(EnemyManager *getEnemyManager) {
	_getEnemyManager = getEnemyManager;
}

void PBoat::SetPoint() {
	_points = new vec4[BTOTPOINT_NUM];
	_colors = new vec4[BTOTPOINT_NUM];

	//pBRSide
	_points[0] = vec4(0.130f, -0.11f, 0.0, 1.0f);
	_points[1] = vec4(0.2f, -0.11f, 0.0, 1.0f);
	_points[2] = vec4(0.130f, 0.0f, 0.0, 1.0f);

	//pBLSide
	_points[3] = vec4(-0.130f, -0.11f, 0.0, 1.0f);
	_points[4] = vec4(-0.20f, -0.11f, 0.0, 1.0f);
	_points[5] = vec4(-0.130f, 0.0f, 0.0, 1.0f);

	//pBBody
	_points[6] = vec4(-0.130f, -0.14f, 0.0, 1.0f);
	_points[7] = vec4(-0.130f, 0.12f, 0.0, 1.0f);
	_points[8] = vec4(0.130f, -0.14f, 0.0, 1.0f);
	_points[9] = vec4(0.130f, 0.12f, 0.0, 1.0f);

	//cBRSide
	_colors[0] = _COLOR_BOATBODY_RED;
	_colors[1] = _COLOR_BOATBODY_RED;
	_colors[2] = _COLOR_BOATBODY_RED;

	//cBLSide
	_colors[3] = _COLOR_BOATBODY_RED;
	_colors[4] = _COLOR_BOATBODY_RED;
	_colors[5] = _COLOR_BOATBODY_RED;

	//cBBody
	_colors[6] = _COLOR_BOATBODY_WIGHT;
	_colors[7] = _COLOR_BOATBODY_WIGHT;
	_colors[8] = _COLOR_BOATBODY_WIGHT;
	_colors[9] = _COLOR_BOATBODY_WIGHT;

	//pBCenter
	for (int i = 10; i < 30; i++) {
		_points[i].x = 0.06f * cosf(M_PI*2.0f*(float)(i - 10) / BCPOINT_NUM); //2拍乘以該點分之總點
		_points[i].y = 0.06f * sinf(M_PI*2.0f*(float)(i - 10) / BCPOINT_NUM) - 0.03f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BACKGROUND;
	}

	//pbTop
	for (int i = 30; i < 41; i++) {
		_points[i].x = 0.13f * cosf(M_PI*2.0f*(float)(i) / BCPOINT_NUM); //2拍乘以該點分之總點
		_points[i].y = -0.13f * sinf(M_PI*2.0f*(float)(i) / BCPOINT_NUM) + 0.12f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BOATBODY_RED;
	}

	//pBFire Yellow
	for (int i = 50; i > 40; i--) {
		_points[i].x = 0.014f*(i - 51) + 0.01f;
		_points[i].y = 10.0f*(_points[i].x)*(_points[i].x) + 0.025f*(_points[i].x) - 0.3f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BOATFIRE_YELLOW;
	}

	_points[51].x = 0.0f;
	_points[51].y = -0.3f;
	_points[51].w = 1.0f;
	_colors[51] = _COLOR_BOATFIRE_YELLOW;

	for (int i = 52; i < 62; i++) {
		_points[i].x = 0.014f*(i - 51) - 0.01f;;
		_points[i].y = 10.0f*(_points[i].x)*(_points[i].x) - 0.025f*(_points[i].x) - 0.3f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BOATFIRE_YELLOW;
	}

	//pBFire red
	for (int i = 71; i > 61; i--) {
		_points[i].x = 0.006f*(i - 72);
		_points[i].y = 20.0f*(_points[i].x)*(_points[i].x) + 0.05f*(_points[i].x) - 0.205f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BOATBODY_RED;
	}

	_points[72].x = 0.0f;
	_points[72].y = -0.205f;
	_points[72].w = 1.0f;
	_colors[72] = _COLOR_BOATBODY_RED;

	for (int i = 73; i < 83; i++) {
		_points[i].x = 0.006f*(i - 72);
		_points[i].y = 20.0f*(_points[i].x)*(_points[i].x) - 0.05f*(_points[i].x) - 0.205f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_BOATBODY_RED;
	}

}

void PBoat::Draw() {
	if (_playerState != PBoat::DEAD) {
		_bulletList->BulletDraw();
		//if (_isDefense == true)	_defense->Draw('c');
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
	if (_playerState == PBoat::HURT) {
		_hurtTimer += delta;
		if (_hurtTimer >= 3.0f) {
			_hurtTimer = 0.0f;
			_playerState = PBoat::NORMAL;
		}
	}
	if (_playerState != PBoat::DEAD) {
		_timer += delta;
		if (isBoatShoot == true) {
			if (_timer >= 0.4f) {
				_timer = 0.0f;
				_bulletList->BulletShoot(_transform->_mxTRS, 0.0f , 1.0f); //player射出子彈，傳入player座標
			}
		}

		//if (_isDefense == true)	_defense->_transform->SetTRSMatrix(_transform->_mxTRS);

		_bulletList->Update(delta,_getEnemyManager,_bulletResult);
	}
}

void PBoat::Hurt() {
	if (_playerState != PBoat::DEAD) {
		_heart--;
		_playerState = PBoat::HURT;
		//if (_isDefense)	_isDefense = false;
		if (_heart <= 0) {
			_transform->SetTRSMatrix(resetMat);
			_playerState = PBoat::DEAD;
			Print("_playerState");
			_bulletList->ResetBulletList();
		}
	}
}

void PBoat::Revival() {	//外掛
	_transform->Reset();
	_playerState = PBoat::NORMAL;
	//_isDefense = true;
	_heart = 3;
	_hurtTimer = 0.0f;
	_timer = 0.0f;
}