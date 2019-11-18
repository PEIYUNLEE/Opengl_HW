#include "Defense.h"

Defense::Defense(mat4 &mxView, mat4 &mxProjection,float circlecollider) {
	_colliderSize = new float;
	*_colliderSize = circlecollider;
	SetPoint(*_colliderSize);
	_transform = new Transform(mxView, mxProjection, POINT_NUM_CIRCLE, _points, _colors);
}

Defense::Defense(mat4 &mxView, mat4 &mxProjection, float boxCollider_X, float boxCollider_Y) {
	_colliderSize = new float[2];
	_colliderSize[0] = boxCollider_X;
	_colliderSize[1] = boxCollider_Y;
	//SetPoint(_colliderSize[0], _colliderSize[1]);
	_transform = new Transform(mxView, mxProjection, POINT_NUM_BOX, _points, _colors);
}

Defense::~Defense() {
	if (_transform != NULL) delete _transform;
}

void Defense::SetPoint(float circlecollider) {
	_points = new vec4[POINT_NUM_CIRCLE];
	_colors = new vec4[POINT_NUM_CIRCLE];

	for (int i = 0; i < POINT_NUM_CIRCLE; i++) {
		_points[i].x = circlecollider * cosf(M_PI*2.0f*(float)(i - 10) / POINT_NUM_CIRCLE); //2拍乘以該點分之總點
		_points[i].y = circlecollider * sinf(M_PI*2.0f*(float)(i - 10) / POINT_NUM_CIRCLE)-0.035f;
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_PBOATDEFENSE;
	}
}

void Defense::Draw(char type) {
	_transform->Draw();

	switch (type)
	{
	case 'c':
		glDrawArrays(GL_LINE_LOOP, 0, POINT_NUM_CIRCLE);
		break;
	case 'b':
		glDrawArrays(GL_TRIANGLE_FAN, 0, POINT_NUM_BOX);
		break;
	}
}
