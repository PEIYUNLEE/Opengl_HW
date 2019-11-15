#include "EnemyManager.h"

EnemyManager::EnemyManager(mat4 &mxView, mat4 &mxProjection,int totCount_s,int totCount_m) {
	_totCount_s = totCount_s;
	_totCount_m = totCount_m;
	//bulid Enemy
	pHead_s = pTail_s = pHead_m = pTail_m = NULL;
	pHead_s = new EnemySmall(mxView, mxProjection);
	pTail_s = pHead_s;
	for (int i = 1; i < _totCount_s; i++)
	{
		pNewGet = new EnemySmall(mxView, mxProjection);
		pNewGet->_prelink = pTail_s;
		pTail_s->_nextlink = pNewGet;
		pTail_s = pNewGet;
	}

	/*pHead_m = new EnemyMiddle(mxView, mxProjection);
	pTail_m = pHead_m;
	for (int i = 1; i < _totCount_m; i++)
	{
		pNewGet = new EnemyMiddle(mxView, mxProjection);
		pNewGet->_prelink = pTail_m;
		pTail_m->_nextlink = pNewGet;
		pTail_m = pNewGet;
	}*/
}

EnemyManager::~EnemyManager() {
	Clear();
}

void EnemyManager::Clear() {
	Enemy *pClearGet;

	for (int i = 0; i < _totCount_s; i++)
	{
		pClearGet = pHead_s;
		if (pClearGet != NULL) {
			pHead_s = pClearGet->_nextlink;
			delete pClearGet;
			i++;
		}
	}

	/*for (int i = 0; i < _totCount_m; i++)
	{
		pClearGet = pHead_m;
		if (pClearGet != NULL) {
			pHead_m = pClearGet->_nextlink;
			delete pClearGet;
			i++;
		}
	}*/
}
