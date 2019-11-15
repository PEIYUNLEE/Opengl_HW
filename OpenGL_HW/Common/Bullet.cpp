#include "Bullet.h"


Bullet::Bullet(mat4 &mxView, mat4 &mxProjection) {
	_prelink = NULL;
	_nextlink = NULL;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, BULLET_POINT_NUM, _points, _colors);
}

Bullet::~Bullet() {
	if(_transform!=NULL) delete _transform;
}

void Bullet::SetPoint() {
	
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
BulletList::BulletList(mat4 &mxView, mat4 &mxProjection, int totCount) {
	_totCount = totCount; //目前所有
	_storeCount = _totCount;
	_shootCount = 0;

	//bulid bullet
	pHead = pTail = NULL;
	pHead = new Bullet(mxView, mxProjection);
	pTail = pHead;
	for (int i= 1; i < _totCount; i++)
	{
		pNewGet = new Bullet(mxView, mxProjection);
		pNewGet->_prelink = pTail;
		pTail->_nextlink = pNewGet;
		pTail = pNewGet;
	}
}

BulletList::~BulletList() {
	Clear();
}

void BulletList::Clear() {
	Bullet *pClearGet;
	for (int i = 0; i < _totCount; i++)
	{
		pClearGet = pHead;
		if (pClearGet != NULL) {
			pHead = pClearGet->_nextlink;
			delete pClearGet;
			i++;
		}
	}
}

void BulletList::PushTail() {
	Bullet *pGet;
	pGet = pUpdateGet;

	pTail->_nextlink = pGet;
	pGet->_prelink = pTail;
	pGet->Reset();
	pTail = pGet;
	pTail->_nextlink = NULL;
}

void BulletList::BulletDraw() {
	if (_shootCount > 0) {
		Bullet *pDrawGet;
		pDrawGet = pUseHead;
		for (int i = 0; i < _shootCount; i++)
		{
			pDrawGet->Draw();
			pDrawGet = pDrawGet->_nextlink;
		}
	}
}

void BulletList::BulletShoot(mat4 &mat) {
	Bullet *pNewBulletGet;
	if (_shootCount == 0)	//當目前use槽沒東西，跟子彈池要子彈
	{
		pNewBulletGet = pHead;	//當目前use槽沒東西，跟子彈池要子彈
		pUseHead = pNewBulletGet;

		pHead = pHead->_nextlink;	
		pHead -> _prelink = NULL;	//子彈從子彈池移出

		pNewBulletGet-> _prelink = NULL;
		pNewBulletGet-> _nextlink = NULL;
		pNewBulletGet->_transform->_mxOri = mat;	//存取初始位置
		pUseTail = pNewBulletGet;
		_shootCount++;
		_storeCount--;
	}
	else
	{
		if (_shootCount < _totCount) {
			pNewBulletGet = pHead;	//跟子彈池要子彈
			if (_shootCount < _totCount - 1) {
				pHead = pHead->_nextlink;
				pHead->_prelink = NULL;	//子彈從子彈池移出
			}
			else if (pHead == pTail) {
				pHead = pTail = NULL;	//子彈從子彈池移出
			}
			pUseTail->_nextlink = pNewBulletGet;
			pNewBulletGet->_prelink = pUseTail;
			pNewBulletGet->_nextlink = NULL;
			pNewBulletGet->_transform->_mxOri = mat;	//存取初始位置
			pUseTail = pNewBulletGet;
			_shootCount++;
			_storeCount--;
		}
		else {
			printf("%d", _shootCount);
		}
	}
}



void BulletList::DestoryBullet()
{
	Bullet *pGetPre,*pGetNext;
	if (pUpdateGet == pUseHead) {
		//如果消失的是顯示的第一顆子彈(_prelink==NULL)
		if (pUseHead == pUseTail) //只剩一顆
			pUseHead = pUseTail = NULL;
		else
		{
			pUseHead = pUseHead->_nextlink;
			pUseHead->_prelink = NULL;
		}
		
		PushTail();	//將子彈丟回子彈池
		pUpdateGet = pUseHead;
	}
	else if(pUpdateGet == pUseTail)
	{
		//如果消失的是顯示的最後一顆子彈(_nextlink==NULL)
		//且一定是pUseHead != pUseTail 不只剩一顆
		pGetPre = pUpdateGet->_prelink;
		pUseTail = pGetPre;
		pUseTail->_nextlink = NULL;
		PushTail();	//將子彈丟回子彈池
		pUpdateGet = NULL;	//結束檢查
	}
	else {
		pGetPre = pUpdateGet->_prelink;
		pGetNext = pUpdateGet->_nextlink;

		pGetPre->_nextlink = pGetNext;
		pGetNext->_prelink = pGetPre;	//重新連結

		PushTail();	//將子彈丟回子彈池
		pUpdateGet = pGetNext;
	}
}

void BulletList::Update(float delta,bool isBoatShoot,mat4 matBoat) {

	_timer += delta;
	if (isBoatShoot == true) {
		if (_timer >= 0.2f) {
			_timer = 0.0f;
			BulletShoot(matBoat); //player射出子彈，傳入player座標
		}
	}
	

	//做每顆子彈要做的事
	if (_shootCount > 0) {
		pUpdateGet = pUseHead;
		int k = 0;
		for (int i = 0; i < _shootCount; i++)
		{
			if (pUpdateGet != NULL) {
				if (pUpdateGet->_transform->_mxTRS._m[1].w >= 2.0f || pUpdateGet->_transform->_mxTRS._m[1].w <= -2.0f) {
					DestoryBullet();
					k++;
				}
				else {
					pUpdateGet->AutoTranslate(delta);
					if (pUpdateGet != pUseTail)
						pUpdateGet = pUpdateGet->_nextlink;
				}
			}
		}

		_shootCount -= k;
		_storeCount += k;
	}

}