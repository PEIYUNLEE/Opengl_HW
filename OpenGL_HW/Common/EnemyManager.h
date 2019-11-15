#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Enemy.h"

class EnemyManager {
private:
	Enemy *pUseTail, *pUseHead;
	Enemy *pHead_s, *pTail_s;
	Enemy *pHead_m, *pTail_m;
	Enemy *pColliGet, *pNewGet;

	int _totCount_s, _totCount_m;

	float _timer;

public:
	int _shootCount = 0;
	int _storeCount = 0;

	EnemyManager(mat4 &mxView, mat4 &mxProjection, int totCount_s=5, int totCount_m=5);
	~EnemyManager();
	void Clear();	// §â¾ã¦êlist§R°£
};