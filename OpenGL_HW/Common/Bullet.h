#pragma once
#include "../Header/Angel.h"
#include "Transform.h"

#define BULLET_POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class Bullet
{
private:
	//data
	vec4 *_points;
	vec4 *_colors;

	float _fspeed =0.7f;
	float _ftottime;

	char _character;

	//node
	Bullet *_prelink;
	Bullet *_nextlink;
public:
	Transform *_transform;

	Bullet(mat4 &mxView, mat4 &mxProjection, char character);
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
	Bullet *pBUseTail, *pBUseHead;
	Bullet *pBHead, *pBTail, *pBNewGet;
	Bullet *pBUpdateGet;

	int _totCount;
	int _shootCount;
	int _storeCount;

	char _character;

	//Collision _collider;
public:

	BulletList(mat4 &mxView, mat4 &mxProjection, int totCount , char character);
	~BulletList();

	void PushTail();		// 在list的尾巴新增node
	void Clear();					// 把整串list刪除
	void BulletShoot(mat4 &mat);
	void BulletDraw();
	//void Update(float delta,mat4 matPlayer);
	void Update(float delta);
	//void Collision();	//判定有沒有碰到敵人或超出範圍
	void DestroyBullet();	//將子彈丟回子彈池
};