#include "Enemy.h"

Enemy::Enemy() {
	_transform = new Transform(POINT_NUM);
	SetPoint();
	_transform->_points = _points;
	_transform->_colors = _colors;
	_transform->CreateBufferObject();
}

Enemy::~Enemy() {
	delete _transform;
}

void Enemy::SetPoint() {

	for (int i = 0; i < POINT_NUM; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / POINT_NUM); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / POINT_NUM) - 0.02f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

void Enemy::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {
	_transform->SetShader(mxView, mxProjection, uiShaderHandle);
}

void Enemy::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, POINT_NUM);
}