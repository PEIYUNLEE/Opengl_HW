#pragma once
#include "../Header/Angel.h"
#include "Transform.h"

#define POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class Bullet
{
private:
	//data
	vec4 _points[POINT_NUM];
	vec4 _colors[POINT_NUM];

	float _fspeed =0.7f;
	float _ftottime;

	//node
	Bullet *_prelink;
	Bullet *_nextlink;
public:
	Transform *_transform;

	Bullet(mat4 &mxView, mat4 &mxProjection);
	~Bullet();

	void SetPoint();
	void AutoTranslate(float dt);
	void Draw();
	void Reset();

	//list
	friend class BulletList;
};




class BulletList{
private:
	Bullet *pUseTail, *pUseHead;
	Bullet *pHead, *pTail, *pNewGet;
	Bullet *pUpdateGet;

	int _totCount;
	int _shootCount;
	int _storeCount;

	float _timer;
public:

	BulletList(mat4 &mxView, mat4 &mxProjection, int totCount);
	~BulletList();

	void PushTail();		// 在list的尾巴新增node
	void Clear();					// 把整串list刪除
	void BulletShoot(mat4 &mat);
	void BulletDraw();
	void Update(float delta, bool isBoatShoot,mat4 matBoat);
	//void Collision();	//判定有沒有碰到敵人或超出範圍
	void DestoryBullet();	//將子彈丟回子彈池
};