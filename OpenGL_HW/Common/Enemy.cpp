#include "Enemy.h"

Enemy::Enemy(mat4 &mxView, mat4 &mxProjection, int pointNum) {
	_pointNum = pointNum;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
}

Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
}

void Enemy::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, _pointNum);
}





/////////EnemySmall
EnemySmall::EnemySmall(mat4 &mxView, mat4 &mxProjection, int pointNum = 20) :Enemy(mxView, mxProjection) {
	
}
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