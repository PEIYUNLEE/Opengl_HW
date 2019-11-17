#include "Bullet.h"
#include "PBoat.h"
#include "EnemyManager.h"


Bullet::Bullet(mat4 &mxView, mat4 &mxProjection, char character) {
	_prelink = NULL;
	_nextlink = NULL;
	_character = character;
	_circlecollider = 0.07f;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, BULLET_POINT_NUM, _points, _colors);
}

Bullet::~Bullet() {
	if(_transform!=NULL) delete _transform;
}

void Bullet::SetPoint() {
	_points = new vec4[BULLET_POINT_NUM];
	_colors = new vec4[BULLET_POINT_NUM];

	for (int i = 0; i < BULLET_POINT_NUM; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / BULLET_POINT_NUM); //2拍乘以該點分之總點
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / BULLET_POINT_NUM);
		_points[i].w = 1.0f;
		_colors[i] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

}

void Bullet::AutoTranslate(float dt) {
	mat4 mxTra;
	GLfloat btx = 0.0f;
	GLfloat bty = 0.0f;


	_ftottime += dt;
	bty = _ftottime*_fspeed;

	if (_character == 'e')
		mxTra = Translate(btx, -bty, 0.0f);
	else if (_character == 'p')
		mxTra = Translate(btx, bty, 0.0f);

	_transform->SetTRSMatrix(mxTra*_transform->_mxOri);
}

void Bullet::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, BULLET_POINT_NUM);
}

void Bullet::Reset() {
	_transform->Reset();

	_ftottime = 0.0f;
}



//BulletList
BulletList::BulletList(mat4 &mxView, mat4 &mxProjection, int totCount, char character) {
	_totCount = totCount; //目前所有
	_storeCount = _totCount;
	_shootCount = 0;
	_character = character;

	//bulid bullet
	pBHead = pBTail = NULL;
	pBHead = new Bullet(mxView, mxProjection , _character);
	pBTail = pBHead;
	for (int i= 1; i < _totCount; i++)
	{
		pBNewGet = new Bullet(mxView, mxProjection , _character);
		pBNewGet->_prelink = pBTail;
		pBTail->_nextlink = pBNewGet;
		pBTail = pBNewGet;
	}
}

BulletList::~BulletList() {
	Clear();
}

void BulletList::Clear() {
	Bullet *pClearGet;
	for (int i = 0; i < _totCount; i++)
	{
		pClearGet = pBHead;
		if (pClearGet != NULL) {
			pBHead = pClearGet->_nextlink;
			delete pClearGet;
			i++;
		}
	}
}

void BulletList::PushTail() {
	Bullet *pGet;
	pGet = pBUpdateGet;

	pBTail->_nextlink = pGet;
	pGet->_prelink = pBTail;
	pGet->Reset();
	pBTail = pGet;
	pBTail->_nextlink = NULL;
}

void BulletList::BulletDraw() {
	if (_shootCount > 0) {
		Bullet *pDrawGet;
		pDrawGet = pBUseHead;
		for (int i = 0; i < _shootCount; i++)
		{
			if (pDrawGet != NULL) {
				pDrawGet->Draw();
				pDrawGet = pDrawGet->_nextlink;
			}
		}
	}
}

void BulletList::BulletShoot(mat4 &mat) {
	Bullet *pNewBulletGet;
	if (_shootCount == 0)	//當目前use槽沒東西，跟子彈池要子彈
	{
		pNewBulletGet = pBHead;	//當目前use槽沒東西，跟子彈池要子彈
		pBUseHead = pNewBulletGet;

		pBHead = pBHead->_nextlink;	
		pBHead -> _prelink = NULL;	//子彈從子彈池移出

		pNewBulletGet-> _prelink = NULL;
		pNewBulletGet-> _nextlink = NULL;
		pNewBulletGet->_transform->_mxOri = mat;	//存取初始位置
		pBUseTail = pNewBulletGet;
		_shootCount++;
		_storeCount--;
	}
	else
	{
		if (_shootCount < _totCount) {
			pNewBulletGet = pBHead;	//跟子彈池要子彈
			if (_shootCount < _totCount - 1) {
				pBHead = pBHead->_nextlink;
				pBHead->_prelink = NULL;	//子彈從子彈池移出
			}
			else if (pBHead == pBTail && pBHead != NULL) {
				pBHead = NULL;	//子彈從子彈池移出
				pBTail = NULL;
			}
			pBUseTail->_nextlink = pNewBulletGet;
			pNewBulletGet->_prelink = pBUseTail;
			pNewBulletGet->_nextlink = NULL;
			pNewBulletGet->_transform->_mxOri = mat;	//存取初始位置
			pBUseTail = pNewBulletGet;
			_shootCount++;
			_storeCount--;
		}
		else {
			printf("%d", _shootCount);
		}
	}
}

void BulletList::DestroyBullet()
{
	Bullet *pGetPre,*pGetNext;
	if (pBUpdateGet == pBUseHead) {
		//如果消失的是顯示的第一顆子彈(_prelink==NULL)
		if (pBUseHead == pBUseTail) //只剩一顆
			pBUseHead = pBUseTail = NULL;
		else
		{
			pBUseHead = pBUseHead->_nextlink;
			pBUseHead->_prelink = NULL;
		}
		
		PushTail();	//將子彈丟回子彈池
		pBUpdateGet = pBUseHead;
	}
	else if(pBUpdateGet == pBUseTail)
	{
		//如果消失的是顯示的最後一顆子彈(_nextlink==NULL)
		//且一定是pUseHead != pUseTail 不只剩一顆
		pGetPre = pBUpdateGet->_prelink;
		pBUseTail = pGetPre;
		pBUseTail->_nextlink = NULL;
		PushTail();	//將子彈丟回子彈池
		pBUpdateGet = NULL;	//結束檢查
	}
	else {
		pGetPre = pBUpdateGet->_prelink;
		pGetNext = pBUpdateGet->_nextlink;

		pGetPre->_nextlink = pGetNext;
		pGetNext->_prelink = pGetPre;	//重新連結

		PushTail();	//將子彈丟回子彈池
		pBUpdateGet = pGetNext;
	}
}

void BulletList::ResetBulletList()
{
	pBUpdateGet == pBUseHead;
	for (int i = 0; i < _shootCount; i++)
	{
		if(pBUpdateGet!=NULL)
			DestroyBullet();
	}
	_shootCount = 0;
	_storeCount = _totCount;
}

void BulletList::Update(float delta, EnemyManager *getEnemyManager) {
	//player的bulletllist
	//做每顆子彈要做的事
	if (_shootCount > 0) {
		pBUpdateGet = pBUseHead;
		int k = 0;
		bool result = false;
		for (int i = 0; i < _shootCount; i++)
		{
			if (pBUpdateGet != NULL) {
				if (pBUpdateGet->_transform->_mxTRS._m[1].w >= 2.0f || pBUpdateGet->_transform->_mxTRS._m[1].w <= -2.0f) {
					DestroyBullet();
					k++;
				}
				else {
					if (getEnemyManager->_usetotCount > 0)
					{
						result = _colliSystem.OnCircleCollision(pBUpdateGet->_transform->_mxTRS, pBUpdateGet->_circlecollider, getEnemyManager);
					}
					if (result == true) {
						DestroyBullet();
						k++;
					}
					else if (result == false) {
						pBUpdateGet->AutoTranslate(delta);
						if (pBUpdateGet != pBUseTail)
							pBUpdateGet = pBUpdateGet->_nextlink;
					}
				}

			}
		}

		_shootCount -= k;
		_storeCount += k;
	}

}

void BulletList::Update(float delta, PBoat *getPBoat) {
	//player的bulletllist
	//做每顆子彈要做的事
	if (_shootCount > 0) {
		pBUpdateGet = pBUseHead;
		int k = 0;
		for (int i = 0; i < _shootCount; i++)
		{
			if (pBUpdateGet != NULL) {
				if (pBUpdateGet->_transform->_mxTRS._m[1].w >= 2.0f || pBUpdateGet->_transform->_mxTRS._m[1].w <= -2.0f) {
					DestroyBullet();
					k++;
				}
				/*else if (getPBoat->_usetotCount > 0) {
					bool test = _colliSystem.OnCircleCollision(pBUpdateGet->_transform->_mxTRS, pBUpdateGet->_circlecollider, getEnemyManager);
				}*/
				else {
					pBUpdateGet->AutoTranslate(delta);
					if (pBUpdateGet != pBUseTail)
						pBUpdateGet = pBUpdateGet->_nextlink;
				}

			}
		}

		_shootCount -= k;
		_storeCount += k;
	}

}