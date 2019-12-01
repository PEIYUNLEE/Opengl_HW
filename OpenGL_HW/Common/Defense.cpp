#include "Defense.h"

Defense::Defense(mat4 &mxView, mat4 &mxProjection,float circlecollider) {
	_colliderSize = new float[2];
	_colliderSize[0] = circlecollider;
	_colliderSize[1] = circlecollider;
	_pointNum = 12;
	_rotTimer = 0.0f;
	_rotSpeed = 720.0f;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
}

Defense::~Defense() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
}

void Defense::SetPoint() {
	_points = new vec4[_pointNum];
	_colors = new vec4[_pointNum];

	///////////////////////////////////////////////////////GRAY CIRCLE
	float a = _colliderSize[0] - 0.02f;
	float b = _colliderSize[0];

	for (int k = 0; k < 2; k++)
	{
		for (int i = 0 + 6 * k , j = 0; i < 6 + 6 * k; i++)
		{
			if (i % 2 == 0) {
				_points[i].x = a* cosf(M_PI*2.0f*(float)(j / 2 - 10*k - 1) / 20.0f) - 0.005f;
				_points[i].y = a* sinf(M_PI*2.0f*(float)(j / 2 - 10*k - 1) / 20.0f) - 0.0275f;
			}
			else {
				_points[i].x = b * cosf(M_PI*2.0f*(float)(j / 2 - 10 * k - 1) / 20.0f) - 0.005f;
				_points[i].y = b * sinf(M_PI*2.0f*(float)(j / 2 - 10 * k - 1) / 20.0f) - 0.0275f;
			}
			_points[i].w = 1.0f;
			_colors[i] = _COLOR_DEFENSE;
			j++;
		}
	}
}

void Defense::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 6, 6);
}

void Defense::AutoRotation(float dt) {
	mat4 mxRot;
	float _fZAngle = 0.0f;

	_rotTimer += dt;
	_fZAngle = _rotTimer*_rotSpeed;
	mxRot = RotateZ(_fZAngle);

	_transform->SetTRSMatrix(_transform->_mxTRS*mxRot);
}

void Defense::Reset() {
	_rotTimer = 0.0f;
}
