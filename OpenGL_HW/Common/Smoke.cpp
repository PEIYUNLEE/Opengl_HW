#include "Smoke.h"

Smoke::Smoke(mat4 &mxView, mat4 &mxProjection,int type) {
	_smokeState = NONE;	//0不顯示
	_timer = 0.0f;

	switch (type) {
	case HURT1:
		_showCount = 2;
		break;
	case HURT2:
		_showCount = 2;
		break;
	case DEAD:
		_showCount = 1;
		break;
	}

	SetPoint(type);
	_transform = new Transform(mxView, mxProjection, POINT_NUM, _points, _colors);
}

Smoke::~Smoke() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
}

void Smoke::SetPoint(int type) {
	_points = new vec4[POINT_NUM];
	_colors = new vec4[POINT_NUM];

	if (type == HURT1) {

		for (int i = 0; i < 20; i++) {
			_points[i].x = 0.14f * cosf(M_PI*2.0f*i / 20.0f) + 0.05f; //2拍乘以該點分之總點
			_points[i].y = 0.14f * sinf(M_PI*2.0f*i / 20.0f);
			_points[i].w = 1.0f;
			_colors[i] = _COLOR_SMOKE_GRAY_1;
		}

		for (int i = 20; i < 40; i++) {
			_points[i].x = 0.11f * cosf(M_PI*2.0f*i / 20.0f) + 0.1f; //2拍乘以該點分之總點
			_points[i].y = 0.11f * sinf(M_PI*2.0f*i / 20.0f) - 0.1f;
			_points[i].w = 1.0f;
			_colors[i] = _COLOR_SMOKE_GRAY_2;
		}

		for (int i = 40; i < 60; i++) {
			_points[i].x = 0.095f * cosf(M_PI*2.0f*i / 20.0f) + 0.13f; //2拍乘以該點分之總點
			_points[i].y = 0.095f * sinf(M_PI*2.0f*i / 20.0f) - 0.23f;
			_points[i].w = 1.0f;
			_colors[i] = _COLOR_SMOKE_GRAY_3;
		}

		for (int i = 60; i < 80; i++) {
			_points[i].x = 0.05f * cosf(M_PI*2.0f*i / 20.0f) + 0.18f; //2拍乘以該點分之總點
			_points[i].y = 0.05f * sinf(M_PI*2.0f*i / 20.0f) - 0.32f;
			_points[i].w = 1.0f;
			_colors[i] = _COLOR_SMOKE_GRAY_4;
		}
	}
	else if(type == DEAD || type == HURT2){
		for (int i = 0; i < 20; i++) {
			_points[i].x = 0.14f * cosf(M_PI*2.0f*i / 20.0f) + 0.05f; //2拍乘以該點分之總點
			_points[i].y = 0.14f * sinf(M_PI*2.0f*i / 20.0f);
			_points[i].w = 1.0f;
			if (type == HURT2)
				_colors[i] = _COLOR_SMOKE_GRAY_1;
			else
				_colors[i] = _COLOR_SMOKE_RED_1;
		}

		for (int i = 20; i < 40; i++) {
			_points[i].x = 0.11f * cosf(M_PI*2.0f*i / 20.0f) + 0.18f; //2拍乘以該點分之總點
			_points[i].y = 0.11f * sinf(M_PI*2.0f*i / 20.0f) + 0.1f;
			_points[i].w = 1.0f;
			if (type == HURT2)
				_colors[i] = _COLOR_SMOKE_GRAY_2;
			else
				_colors[i] = _COLOR_SMOKE_RED_2;
		}

		for (int i = 40; i < 60; i++) {
			_points[i].x = 0.095f * cosf(M_PI*2.0f*i / 20.0f) + 0.11f; //2拍乘以該點分之總點
			_points[i].y = 0.095f * sinf(M_PI*2.0f*i / 20.0f) + 0.31f;
			_points[i].w = 1.0f;
			if (type == HURT2) 
				_colors[i] = _COLOR_SMOKE_GRAY_3;
			else
				_colors[i] = _COLOR_SMOKE_RED_3;
		}

		for (int i = 60; i < 80; i++) {
			_points[i].x = 0.05f * cosf(M_PI*2.0f*i / 20.0f) + 0.24f; //2拍乘以該點分之總點
			_points[i].y = 0.05f * sinf(M_PI*2.0f*i / 20.0f) + 0.36f;
			_points[i].w = 1.0f;
			if (type == HURT2) {
				_colors[i] = _COLOR_SMOKE_GRAY_4;
			}
			else {
				_colors[i] = _COLOR_SMOKE_RED_4;
			}
		}
	}
}

void Smoke::Update(float dt,mat4 mat) {
	float a = 0.0f;
	float aspeed = 3.03f;	//1.0/0.33
	if (_smokeState > NONE && _showCount >= 0) {
		_transform->SetTRSMatrix(mat);
		_timer += dt;
		a = aspeed*_timer;
		if(_showCount > 0)
			_transform->SetColorA(a, 0 + 20 * (_smokeState - 1), 19 + 20 * (_smokeState - 1));
		if(_smokeState > FIRST)
			_transform->SetColorA(1.0f- a, 0 + 20 * (_smokeState-2), 19 + 20 * (_smokeState - 2));
		else if (_smokeState == FIRST && _showCount < 2) {
			_transform->SetColorA(1.0f - a, 60, 79);
		}
		if (_timer >= 0.33f) {	//每個階段duration	3.0/9.0f
			//_transform->SetColorA(1.0f, 0 + 20 * (_smokeState - 1), 20 + 20 * (_smokeState - 1));
			_timer = 0.0f;
			_smokeState += 1;
			if (_smokeState > FOURTH ) {
				_smokeState = 1;
				_showCount--;
			}
			if (_showCount == 0 && _smokeState == SECOND) {
				_smokeState = 0;
				_showCount = 0;
			}
		}
		/*else if (_timer <= 2.5f && !smokeflag) {
			_transform->SetColorA(0.5f, 0 + 20 * (_smokeState - 1), 20 + 20 * (_smokeState - 1));
			smokeflag = true;
		}*/
	}
}

void Smoke::Draw() {
	if (_smokeState >= FIRST) {
		_transform->Draw();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	}
	if (_smokeState >= SECOND) {
		glDrawArrays(GL_TRIANGLE_FAN, 20, 20);
	}
	if (_smokeState >= THIRD) {
		glDrawArrays(GL_TRIANGLE_FAN, 40, 20);
	}
	if(_smokeState == FOURTH) {
		glDrawArrays(GL_TRIANGLE_FAN, 60, 20);
	}
}

void Smoke::Show(int type) {
	_timer = 0.0f;
	_smokeState = FIRST;


	switch (type) {
	case HURT1:
		_showCount = 2;
		break;
	case HURT2:
		_showCount = 2;
		break;
	case DEAD:
		_showCount = 1;
		break;
	}
}

void Smoke::Reset(int type) {
	_timer = 0.0f;
	_smokeState = NONE;


	switch (type) {
	case HURT1:
		_showCount = 2;
		break;
	case HURT2:
		_showCount = 2;
		break;
	case DEAD:
		_showCount = 1;
		break;
	}
}