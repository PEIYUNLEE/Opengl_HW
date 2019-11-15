#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Bullet.h"

#define BSPOINT_NUM 3 //side
#define BBPOINT_NUM 4 //body
#define BCPOINT_NUM 20 //center circle
#define BTPOINT_NUM 11 //top circle
#define BPPOINT_NUM 21 //�ߪ��u
#define BTOTPOINT_NUM BSPOINT_NUM*2+BBPOINT_NUM+BCPOINT_NUM+BTPOINT_NUM+BPPOINT_NUM*2+1

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class PBoat
{
private:
	vec4 _points[BTOTPOINT_NUM];
	vec4 _colors[BTOTPOINT_NUM];

	float _timer;
public:
	Transform * _transform;
	BulletList * _bulletList;

	PBoat(mat4 &mxView, mat4 &mxProjection);
	~PBoat();
	void SetPoint();
	void Draw();
	void Update(float delta, bool isBoatShoot);
};