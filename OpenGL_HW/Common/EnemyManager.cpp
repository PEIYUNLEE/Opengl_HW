#include "EnemyManager.h"
#include "Enemy.h"
#include "PBoat.h"
#include "Bullet.h"

EnemyManager::EnemyManager(mat4 &mxView, mat4 &mxProjection,int totCount_s,int totCount_m) {
	_state = LEVEL3;

	srand((unsigned)time(NULL));

	_totCount_s = _storeCount_s = totCount_s;
	_totCount_m = _storeCount_m = totCount_m;
	_totCount_b = _storeCount_b = 1;
	_storetotCount = _totCount_s + _totCount_m + _totCount_b;
	_usetotCount = 0;
	_useCount_s = 0;
	_useCount_m = 0;
	_useCount_b = 0;

	_timer  = 0.0f;
	_genDuration = RandomTime();
	_genMat = RandomPosition();

	//bulid Enemy
	pEHead_s = pETail_s = pEHead_m = pETail_m = NULL;
	pEHead_s = new EnemySmall(mxView, mxProjection);
	pETail_s = pEHead_s;
	for (int i = 1; i < _totCount_s; i++)
	{
		pENewGet = new EnemySmall(mxView, mxProjection);
		pENewGet->_prelink = pETail_s;
		pETail_s->_nextlink = pENewGet;
		pETail_s = pENewGet;
	}

	pEHead_m = new EnemyMiddle(mxView, mxProjection);
	pETail_m = pEHead_m;
	for (int i = 1; i < _totCount_m; i++)
	{
		pENewGet = new EnemyMiddle(mxView, mxProjection);
		pENewGet->_prelink = pETail_m;
		pETail_m->_nextlink = pENewGet;
		pETail_m = pENewGet;
	}

	pEHead_b = new EnemyBoss(mxView, mxProjection);
}

EnemyManager::~EnemyManager() {
	Clear();
}

void EnemyManager::GetComponent(PBoat *getPBoat) {
	_getPBoat = getPBoat;
}

void EnemyManager::Clear() {
	Enemy *pClearGet;

	for (int i = 0; i < _totCount_s; i++)
	{
		pClearGet = pEHead_s;
		if (pClearGet != NULL) {
			pEHead_s = pClearGet->_nextlink;
			delete pClearGet;
			i++;
		}
	}

	for (int i = 0; i < _totCount_m; i++)
	{
		pClearGet = pEHead_m;
		if (pClearGet != NULL) {
			pEHead_m = pClearGet->_nextlink;
			delete pClearGet;
			i++;
		}
	}

	if (pEHead_b != NULL) delete pEHead_b;
}

void EnemyManager::EnemyGenerater(char type, mat4 &mat) {

	Enemy *pNewEnemyGet,*pHead,*pTail;
	int *useCount,*storeCount,*totCount;
	pNewEnemyGet = pHead = pTail = NULL;
	useCount = storeCount = totCount = NULL;

	switch (type) {
	case 's':
		pHead = pEHead_s;
		pTail = pETail_s;
		useCount = &_useCount_s;
		storeCount= &_storeCount_s;
		totCount = &_totCount_s;
		break;
	case 'm':
		pHead = pEHead_m;
		pTail = pETail_m;
		useCount = &_useCount_m;
		storeCount = &_storeCount_m;
		totCount = &_totCount_m;
		break;
	case 'b':
		pHead = pEHead_b;
		pTail = pEHead_b;
		useCount = &_useCount_b;
		storeCount = &_storeCount_b;
		totCount = &_totCount_b;
		break;
	}

	if (_usetotCount == 0)	//��ثeuse�ѨS�F��A��l�u���n�l�u
	{
		pNewEnemyGet = pHead;
		pEUseHead = pNewEnemyGet;
		if (*totCount != 1) {
			pHead = pHead->_nextlink;
			pHead->_prelink = NULL;	//�l�u�q�l�u�����X
		}

		pNewEnemyGet->_prelink = NULL;
		pNewEnemyGet->_nextlink = NULL;
		pNewEnemyGet->_transform->_mxOri = mat;	//�s����l��m
		pEUseTail = pNewEnemyGet;
		(*useCount)++;
		_usetotCount++;
		(*storeCount)--;
	}
	else
	{
		if (*useCount < *totCount) {
			pNewEnemyGet = pHead;	//��l�u���n�l�u
			if (*useCount < *totCount - 1) {
				pHead = pHead->_nextlink;
				pHead->_prelink = NULL;	//�l�u�q�l�u�����X
			}
			else if (pHead == pTail) {
				//store�ѳ̫�@��
				pHead = pTail = NULL;	//�l�u�q�l�u�����X
			}
			pEUseTail->_nextlink = pNewEnemyGet;
			pNewEnemyGet->_prelink = pEUseTail;
			pNewEnemyGet->_nextlink = NULL;
			pNewEnemyGet->_transform->_mxOri = mat;	//�s����l��m
			pEUseTail = pNewEnemyGet;
			(*useCount)++;
			_usetotCount++;
			(*storeCount)--;
		}
		else {
			printf("%d", _usetotCount);
		}
	}

	switch (type) {
	case 's':
		pEHead_s = pHead;
		pETail_s = pTail;
		break;
	case 'm':
		pEHead_m = pHead;
		pETail_m = pTail;
		break;
	}
}

void EnemyManager::EnemyDraw() {
	if (_usetotCount > 0) {
		Enemy *pDrawGet;
		pDrawGet = pEUseHead;
		for (int i = 0; i < _usetotCount; i++)
		{
			pDrawGet->Draw();
			pDrawGet = pDrawGet->_nextlink;
		}
	}
}

void EnemyManager::PushTail() {
	Enemy *pGet,*pTail;
	pTail = NULL;
	pGet = pEUpdateGet;

	switch (pGet->_type)
	{
		case 's':
			pTail = pETail_s;
			break;
		case 'm':
			pTail = pETail_m;
			break;
		case 'b':
			pTail = pEHead_b;
			break;
	}

	pTail->_nextlink = pGet;
	pGet->_prelink = pTail;
	pGet->Reset();
	pTail = pGet;
	pTail->_nextlink = NULL;

	switch (pGet->_type)
	{
	case 's':
		pETail_s = pTail;
		break;
	case 'm':
		pETail_m = pTail;
		break;
	case 'b':
		pTail = pEHead_b;
		break;
	}
}

void EnemyManager::DestroyEnemy()
{
	Enemy *pGetPre, *pGetNext;
	pEUpdateGet->_bulletList->ResetBulletList();
	if (pEUpdateGet == pEUseHead) {
		//�p�G�������O��ܪ��Ĥ@�ӼĤH(_prelink==NULL)
		if (pEUseHead == pEUseTail) //�u�Ѥ@��
			pEUseHead = pEUseTail = NULL;
		else
		{
			pEUseHead = pEUseHead->_nextlink;
			pEUseHead->_prelink = NULL;
		}

		PushTail();	//�N�l�u��^�l�u��
		pEUpdateGet = pEUseHead;
	}
	else if (pEUpdateGet == pEUseTail)
	{
		//�p�G�������O��ܪ��̫�@���l�u(_nextlink==NULL)
		//�B�@�w�OpUseHead != pUseTail ���u�Ѥ@��
		pGetPre = pEUpdateGet->_prelink;
		pEUseTail = pGetPre;
		pEUseTail->_nextlink = NULL;
		PushTail();	//�N�l�u��^�l�u��
		pEUpdateGet = NULL;	//�����ˬd
	}
	else {
		pGetPre = pEUpdateGet->_prelink;
		pGetNext = pEUpdateGet->_nextlink;

		pGetPre->_nextlink = pGetNext;
		pGetNext->_prelink = pGetPre;	//���s�s��

		PushTail();	//�N�l�u��^�l�u��
		pEUpdateGet = pGetNext;
	}
}

void EnemyManager::Update(float dt) {
	_timer += dt;
	//���ͼĤH

	EGeneratorController();

	//���e��Enemy�n������
	if (_usetotCount > 0) {
		pEUpdateGet = pEUseHead;
		int k = 0,ds = 0,dm = 0;
		for (int i = 0; i < _usetotCount; i++)
		{
			if (pEUpdateGet != NULL) {
				if (pEUpdateGet->_isDead == true) {

					switch (pEUpdateGet->_type)
					{
					case 's':
						ds++;
						break;
					case 'm':
						dm++;
						break;
					}

					DestroyEnemy(); 
					k++;
				}
				else if (pEUpdateGet->_type != 'b' && (pEUpdateGet->_transform->_mxTRS._m[1].w >= 2.6f || pEUpdateGet->_transform->_mxTRS._m[1].w <= -2.6f)) {

					switch (pEUpdateGet->_type)
					{
					case 's':
						ds++;
						break;
					case 'm':
						dm++;
						break;
					}

					DestroyEnemy();	//�p�G�I����ɭn�R��
					k++;
				}
				else if (_colliSystem.OnBoxCollision(pEUpdateGet->_transform->_mxTRS, pEUpdateGet->_colliderSize, _getPBoat->_transform->_mxTRS, _getPBoat->_colliderSize)) {

					switch (pEUpdateGet->_type)
					{
					case 's':
						ds++;
						break;
					case 'm':
						dm++;
						break;
					}
					Print("hurt!!!!!");
					//DestroyEnemy();	//�p�G�I����ɭn�R��
					//k++;
				}
				else {
					pEUpdateGet->Action(dt,_getPBoat);	//�����Bmove
					if (pEUpdateGet != pEUseTail)
						pEUpdateGet = pEUpdateGet->_nextlink;
				}
			}
		}

		_usetotCount -= k;
		_useCount_s -= ds;
		_useCount_m -= dm;
		_storetotCount += k;
		_storeCount_s += ds;
		_storeCount_m += dm;
	}

}

float EnemyManager::RandomTime(float min, float max) {
	float result;

	/* ���� [min , max) ���B�I�ƶü� */
	result = (max - min) * rand() / (RAND_MAX + 1.0f) + min;

	return result;
}

mat4 EnemyManager::RandomPosition(float minX, float maxX, float Y) {
	float x,y;
	mat4 result;

	/* ���� [min , max) ���B�I�ƶü� */
	x = (maxX - minX) * rand() / (RAND_MAX + 1.0f) + minX;
	y = Y;

	result._m[0].w = x;
	result._m[1].w = y;
	return result;
}

bool flag=false;
void EnemyManager::EGeneratorController(){
	switch (_state)
	{
		case LEVEL1:
			if (_timer > _genDuration) {
				_timer = 0.0f;
				EnemyGenerater('s', _genMat);
				_genDuration = RandomTime();
				_genMat = RandomPosition();
			}
			break;
		case LEVEL2:
			if (_timer > _genDuration && !flag) {
				flag = true;
				_genMat._m[0].w = 1.5f;
				_genMat._m[1].w = 2.55f;
				EnemyGenerater('m', _genMat);
				_genMat._m[0].w = -1.5f;
				_genMat._m[1].w = 2.55f;
				EnemyGenerater('m', _genMat);
			}
			break;
		case LEVEL3:
			if (!flag) {
				flag = true;
				_genMat = RandomPosition(0.0f,0.0f,3.0f);
				EnemyGenerater('b', _genMat);
			}
			break;
		default:
			break;
		}

}