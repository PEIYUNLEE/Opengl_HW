#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
class EnemyManager;
class PBoat;
#include "Collision.h"

#define BULLET_POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class Bullet
{
private:
	//data
	vec4 *_points;
	vec4 *_colors;

	float _fspeed;
	float _ftottime;

	char _character;

	//node
	Bullet *_prelink;
	Bullet *_nextlink;

public:
	float _bIX, _bIY; //BULLET單位向量
	float *_colliderSize;
	Transform *_transform;

	Bullet(mat4 &mxView, mat4 &mxProjection, char character,float fspeed);
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
	Bullet *pBHead, *pBTail, *pBNewGet;
	Bullet *pBUpdateGet;

	int _totCount;
	int _storeCount;

	char _character;

	Collision _colliSystem;
public:

	Bullet *pBUseTail, *pBUseHead;
	int _shootCount;

	BulletList(mat4 &mxView, mat4 &mxProjection, int totCount , char character, float fspeed);
	~BulletList();

	void PushTail();		// 在list的尾巴新增node
	void Clear();					// 把整串list刪除
	void BulletShoot(mat4 &mat, float bIX, float bIY);
	void BulletDraw();
	void Update(float delta, PBoat *getPBoat);
	void Update(float delta, EnemyManager *getEnemyManager);
	//void Collision();	//判定有沒有碰到敵人或超出範圍
	void DestroyBullet();	//將子彈丟回子彈池
	void ResetBulletList();
	Bullet* BulletVsBullet(mat4 &mat_Bullet, float cBulletRadius, PBoat *getPBoat);
};