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
	float _bIX, _bIY; //BULLET���V�q
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

	void PushTail();		// �blist�����ڷs�Wnode
	void Clear();					// ����list�R��
	void BulletShoot(mat4 &mat, float bIX, float bIY);
	void BulletDraw();
	void Update(float delta, PBoat *getPBoat);
	void Update(float delta, EnemyManager *getEnemyManager);
	//void Collision();	//�P�w���S���I��ĤH�ζW�X�d��
	void DestroyBullet();	//�N�l�u��^�l�u��
	void ResetBulletList();
	Bullet* BulletVsBullet(mat4 &mat_Bullet, float cBulletRadius, PBoat *getPBoat);
};