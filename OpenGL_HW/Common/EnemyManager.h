#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Enemy.h"

class EnemyManager {
private:
	Enemy *pUseTail, *pUseHead;
	Enemy *pHead, *pTail, *pNewGet;
	Enemy *pColliGet;

	int _totCount;

	float _timer;

public:
	int _shootCount = 0;
	int _storeCount = 0;

	EnemyManager(mat4 g_mxModelView, mat4 g_mxProjection, int count);
	~EnemyManager();
	void PrintManager();			// �L�XManager���Ҧ����
	void PushHead();		// �bManager�����ڷs�Wnode
	void PushTail();		// �bManager�����ڷs�Wnode
	void Delete(int index);			// �R��Manager����index
	void Clear();					// ����Manager�R��
	void EnemyShoot(mat4 &mat);
	void EnemyDraw();
	void AutoTranslate(float timeDelta);
	void Update(float delta, bool isBoatShoot, mat4 matBoat);
	void Collision();	//�P�w���S���I��ĤH�ζW�X�d��
	void DestoryEnemy();	//�N�l�u��^�l�u��
};