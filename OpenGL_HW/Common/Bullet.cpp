#include "Bullet.h"


Bullet::Bullet() {
	_transform = new Transform(POINT_NUM);
	SetPoint();
	_transform->_points = _points;
	_transform->_colors = _colors;
	_transform->CreateBufferObject();
}

Bullet::~Bullet() {
	delete _transform;
}

void Bullet::SetPoint() {
	
	for (int i = 0; i < POINT_NUM; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / POINT_NUM); //2�筼�H���I�����`�I
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / POINT_NUM);
		_points[i].w = 1.0f;
		_colors[i] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

}

void Bullet::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {
	_transform->SetShader(mxView, mxProjection, uiShaderHandle);
}

void Bullet::AutoTranslate(float dt) {
	mat4 mxTra;
	GLfloat btx = 0.0f;
	GLfloat bty = 0.0f;

	_ftottime += dt;
	bty = _ftottime*_fspeed;
	mxTra = Translate(btx, bty, 0.0f);
	_transform->SetTRSMatrix(mxTra*_mxOri);
}

void Bullet::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, POINT_NUM);
}




//BulletList
BulletList::BulletList(mat4 g_mxModelView, mat4 g_mxProjection,int count) {
	_totCount = count; //�ثe�Ҧ�
	_storeCount = _totCount;

	//bulid bullet
	pHead = pTail = NULL;
	pHead = new Bullet;
	pHead->SetShader(g_mxModelView, g_mxProjection);
	pHead->_prelink = NULL;
	pHead->_nextlink = NULL;
	pTail = pHead;
	for (int i= 1; i < _totCount; i++)
	{
		pNewGet = new Bullet;
		pNewGet->SetShader(g_mxModelView, g_mxProjection);
		pNewGet->_prelink = pTail;
		pNewGet->_nextlink = NULL;
		pTail->_nextlink = pNewGet;
		pTail = pNewGet;
	}
}

BulletList::~BulletList() {
	Clear();
}

void BulletList::PushTail() {
	mat4 init;
	Bullet *pGet;
	pGet = pColliGet;

	pTail->_nextlink = pGet;
	pGet->_prelink = pTail;
	pGet->_mxOri = init;
	pGet->_transform->_mxTRS = init;
	pGet->_transform->_mxMVFinal = init;
	pGet->_ftottime = 0.0f;
	pTail = pGet;
	pTail->_nextlink = NULL;
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
		pHead->_prelink = NULL;	//�l�u�q�l�u�����X

		pNewBulletGet->_prelink = NULL;
		pNewBulletGet-> _nextlink = NULL;
		pNewBulletGet-> _mxOri = mat;	//�s����l��m
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
			pNewBulletGet->_mxOri = mat;	//�s����l��m
			pUseTail = pNewBulletGet;
			_shootCount++;
			_storeCount--;
		}
		else {
			printf("%d", _shootCount);
		}
	}
}

void BulletList::AutoTranslate(float timeDelta) {
	Bullet *pTraGet;
	if (_shootCount > 0) {
		pTraGet = pUseHead;
		for (int i = 0; i < _shootCount; i++)
		{
			if (pTraGet != NULL) {
				pTraGet->AutoTranslate(timeDelta);
				pTraGet = pTraGet->_nextlink;
			}
		}
	}
}

void BulletList::Collision()
{
	if (_shootCount > 0) {
		pColliGet = pUseHead;
		int k = 0;
		for (int i = 0; i < _shootCount; i++)
		{
			if (pColliGet != NULL) {
				if (pColliGet->_transform->_mxTRS._m[1].w >= 2.0f|| pColliGet->_transform->_mxTRS._m[1].w <= -2.0f) {
					DestoryBullet();
					k++;
				}
				//if()
				else {
					if(pColliGet!=pUseTail)
						pColliGet = pColliGet->_nextlink;
				}	
			}
		}
		_shootCount -= k;
		_storeCount += k;
	}
}

void BulletList::DestoryBullet()
{
	Bullet *pGetPre,*pGetNext;
	if (pColliGet == pUseHead) {
		//�p�G�������O��ܪ��Ĥ@���l�u(_prelink==NULL)
		if (pUseHead == pUseTail) //�u�Ѥ@��
			pUseHead = pUseTail = NULL;
		else
		{
			pUseHead = pUseHead->_nextlink;
			pUseHead->_prelink = NULL;
		}
		
		PushTail();	//�N�l�u��^�l�u��
		pColliGet = pUseHead;
	}
	else if(pColliGet == pUseTail)
	{
		//�p�G�������O��ܪ��̫�@���l�u(_nextlink==NULL)
		//�B�@�w�OpUseHead != pUseTail ���u�Ѥ@��
		pGetPre = pColliGet->_prelink;
		pUseTail = pGetPre;
		pUseTail->_nextlink = NULL;
		PushTail();	//�N�l�u��^�l�u��
		pColliGet = NULL;	//�����ˬd
	}
	else {
		pGetPre = pColliGet->_prelink;
		pGetNext = pColliGet->_nextlink;

		pGetPre->_nextlink = pGetNext;
		pGetNext->_prelink = pGetPre;	//���s�s��

		PushTail();	//�N�l�u��^�l�u��
		pColliGet = pGetNext;
	}
}

void BulletList::Update(float delta,bool isBoatShoot,mat4 matBoat) {
	Collision();

	_timer += delta;
	if (isBoatShoot == true) {
		if (_timer >= 0.2f) {
			_timer = 0.0f;
			BulletShoot(matBoat); //player�g�X�l�u�A�ǤJplayer�y��
		}
	}


	AutoTranslate(delta);
}