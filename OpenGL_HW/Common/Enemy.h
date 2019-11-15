#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Bullet.h"

#define POINT_NUM 20 //center circle

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Enemy
{
private:
	vec4 _points[POINT_NUM];
	vec4 _colors[POINT_NUM];
public:
	Transform *_transform;

	Enemy(mat4 &mxView, mat4 &mxProjection);
	~Enemy();
	void SetPoint();
	void Draw();
	//void Update(float delta, bool isBoatShoot);

	friend class EnemyManager;
};