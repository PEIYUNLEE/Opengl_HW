#include "Enemy.h"

Enemy::Enemy(mat4 &mxView, mat4 &mxProjection) {
	SetPoint();
	_transform = new Transform(mxView, mxProjection, POINT_NUM, _points, _colors);
}

Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
}

void Enemy::SetPoint() {

	for (int i = 0; i < POINT_NUM; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / POINT_NUM); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / POINT_NUM) - 0.02f;
		_points[i].w = 1.0f;
		_colors[i] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

void Enemy::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, POINT_NUM);
}