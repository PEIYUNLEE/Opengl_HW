#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Collision.h"
#include "Enemy.h"
#include "PBoat.h"

#define BULLET_POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class Bullet
{
private:
	//data
	vec4 _points[BULLET_POINT_NUM];
	vec4 _colors[BULLET_POINT_NUM];

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

	//Collision _collider;
public:

	BulletList(mat4 &mxView, mat4 &mxProjection, int totCount);
	~BulletList();

	void PushTail();		// �blist�����ڷs�Wnode
	void Clear();					// ����list�R��
	void BulletShoot(mat4 &mat);
	void BulletDraw();
	//void Update(float delta,mat4 matPlayer);
	void Update(float delta, mat4 matPlayer);
	//void Collision();	//�P�w���S���I��ĤH�ζW�X�d��
	void DestoryBullet();	//�N�l�u��^�l�u��
};