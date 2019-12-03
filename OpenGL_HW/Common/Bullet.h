#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
class EnemyManager;
class PBoat;
#include "Collision.h"
#include "ColorDefine.h"

#define BULLET_POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class Bullet
{
private:
	//data
	vec4 *_points;
	vec4 *_colors;

	bool _bStartRot = false;
	float _ftottime;

	char _character;

	//node
	Bullet *_prelink;
	Bullet *_nextlink;

public:
	bool _isSpecial;
	float _fSpeed,_fSpeedInit;
	float _bIX, _bIY; //BULLET���V�q
	mat4 _mxRot;
	float *_colliderSize;
	Transform *_transform;

	Bullet(mat4 &mxView, mat4 &mxProjection, char character,float fspeed, const vec4 &color = _COLOR_YELLOW);
	~Bullet();

	void SetPoint(const vec4 &color);
	void AutoTranslate(float dt);
	void AutoTranslate(float dt,int index);
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

	BulletList(mat4 &mxView, mat4 &mxProjection, int totCount , char character, const vec4 &color, float fspeed);
	~BulletList();

	void PushTail();		// �blist�����ڷs�Wnode
	void Clear();					// ����list�R��
	void BulletShoot(mat4 &mat, float bIX, float bIY, float angle,bool isSpecial = false);
	void BulletShoot(mat4 &mat, float bIX, float bIY, float angle, float fSpeed, bool isSpecial = false);
	void BulletDraw();
	void Update(float delta, PBoat *getPBoat);
	void Update(float delta, EnemyManager *getEnemyManager, Bullet *bulletResult);
	//void Collision();	//�P�w���S���I��ĤH�ζW�X�d��
	void DestroyBullet();	//�N�l�u��^�l�u��
	void ResetBulletList();
	void SetBulletSpeed(float fSpeed);
	Bullet* BulletVsBullet(mat4 &mat_Bullet, float cBulletRadius, PBoat *getPBoat);
};