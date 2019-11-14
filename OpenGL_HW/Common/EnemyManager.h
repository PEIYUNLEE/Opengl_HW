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
	void PrintManager();			// 印出Manager的所有資料
	void PushHead();		// 在Manager的尾巴新增node
	void PushTail();		// 在Manager的尾巴新增node
	void Delete(int index);			// 刪除Manager中的index
	void Clear();					// 把整串Manager刪除
	void EnemyShoot(mat4 &mat);
	void EnemyDraw();
	void AutoTranslate(float timeDelta);
	void Update(float delta, bool isBoatShoot, mat4 matBoat);
	void Collision();	//判定有沒有碰到敵人或超出範圍
	void DestoryEnemy();	//將子彈丟回子彈池
};