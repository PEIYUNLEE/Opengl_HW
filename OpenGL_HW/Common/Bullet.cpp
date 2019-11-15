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
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / BULLET_POINT_NUM); //2�筼�H���I�����`�I
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
	_totCount = totCount; //�ثe�Ҧ�
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
	if (_shootCount == 0)	//��ثeuse�ѨS�F��A��l�u���n�l�u
	{
		pNewBulletGet = pHead;	//��ثeuse�ѨS�F��A��l�u���n�l�u
		pUseHead = pNewBulletGet;

		pHead = pHead->_nextlink;	
		pHead -> _prelink = NULL;	//�l�u�q�l�u�����X

		pNewBulletGet-> _prelink = NULL;
		pNewBulletGet-> _nextlink = NULL;
		pNewBulletGet->_transform->_mxOri = mat;	//�s����l��m
		pUseTail = pNewBulletGet;
		_shootCount++;
		_storeCount--;
	}
	else
	{
		if (_shootCount < _totCount) {
			pNewBulletGet = pHead;	//��l�u���n�l�u
			if (_shootCount < _totCount - 1) {
				pHead = pHead->_nextlink;
				pHead->_prelink = NULL;	//�l�u�q�l�u�����X
			}
			else if (pHead == pTail) {
				pHead = pTail = NULL;	//�l�u�q�l�u�����X
			}
			pUseTail->_nextlink = pNewBulletGet;
			pNewBulletGet->_prelink = pUseTail;
			pNewBulletGet->_nextlink = NULL;
			pNewBulletGet->_transform->_mxOri = mat;	//�s����l��m
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
		//�p�G�������O��ܪ��Ĥ@���l�u(_prelink==NULL)
		if (pUseHead == pUseTail) //�u�Ѥ@��
			pUseHead = pUseTail = NULL;
		else
		{
			pUseHead = pUseHead->_nextlink;
			pUseHead->_prelink = NULL;
		}
		
		PushTail();	//�N�l�u��^�l�u��
		pUpdateGet = pUseHead;
	}
	else if(pUpdateGet == pUseTail)
	{
		//�p�G�������O��ܪ��̫�@���l�u(_nextlink==NULL)
		//�B�@�w�OpUseHead != pUseTail ���u�Ѥ@��
		pGetPre = pUpdateGet->_prelink;
		pUseTail = pGetPre;
		pUseTail->_nextlink = NULL;
		PushTail();	//�N�l�u��^�l�u��
		pUpdateGet = NULL;	//�����ˬd
	}
	else {
		pGetPre = pUpdateGet->_prelink;
		pGetNext = pUpdateGet->_nextlink;

		pGetPre->_nextlink = pGetNext;
		pGetNext->_prelink = pGetPre;	//���s�s��

		PushTail();	//�N�l�u��^�l�u��
		pUpdateGet = pGetNext;
	}
}

void BulletList::Update(float delta,bool isBoatShoot,mat4 matBoat) {

	_timer += delta;
	if (isBoatShoot == true) {
		if (_timer >= 0.2f) {
			_timer = 0.0f;
			BulletShoot(matBoat); //player�g�X�l�u�A�ǤJplayer�y��
		}
	}
	

	//���C���l�u�n������
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