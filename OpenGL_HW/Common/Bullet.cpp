#include "Bullet.h"


Bullet::Bullet() {
	SetPoint();
	CreateBufferObject();
}

void Bullet::SetPoint() {
	
	for (int i = 0; i < POINT_NUM; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / POINT_NUM); //2�筼�H���I�����`�I
		_points[i].y = 0.07f * sinf(M_PI*2.0f*(float)(i - 10) / POINT_NUM);
		_points[i].w = 1.0f;
		_colors[i] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

}

void Bullet::CreateBufferObject() {

	glGenVertexArrays(1, &_uiVao);
	glBindVertexArray(_uiVao);

	glGenBuffers(1, &_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_points) + sizeof(_colors), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_points), _points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_points), sizeof(_colors), _colors);
}

void Bullet::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {

	if (uiShaderHandle == MAX_UNSIGNED_INT) _uiProgram = InitShader("vsVtxColor.glsl", "fsVtxColor.glsl");
	else _uiProgram = uiShaderHandle;

	GLuint vPosition = glGetAttribLocation(_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(_uiProgram, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(_points)));

	_uiModelView = glGetUniformLocation(_uiProgram, "ModelView");
	_mxView = mxView;
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxView);

	_uiProjection = glGetUniformLocation(_uiProgram, "Projection");
	_mxProjection = mxProjection;
	glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bullet::AutoTranslate(float dt) {
	mat4 mxTra;
	GLfloat btx = 0.0f;
	GLfloat bty = 0.0f;

	_ftottime += dt;
	bty = _ftottime*_fspeed;
	mxTra = Translate(btx, bty, 0.0f);
	SetTRSMatrix(_mxOri*mxTra);
}

void Bullet::SetTRSMatrix(mat4 &mat)
{
	//�x�}����
	_mxTRS = mat;
	_bUpdateMV = true;
	
}

void Bullet::Draw() {
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);

	if (_bUpdateMV) {
		_mxMVFinal = _mxView*_mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	glDrawArrays(GL_TRIANGLE_FAN, 0, POINT_NUM);
}

//void Bullet::DrawW() {
//	glBindVertexArray(_uiVao);
//
//	if (_bUpdateMV) {
//		_mxMVFinal = _mxView*_mxTRS;
//		_bUpdateMV = false;
//	}
//	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);
//
//	glDrawArrays(GL_TRIANGLE_FAN, 0, POINT_NUM);
//}






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
		printf("%d", i);
	}
}

BulletList::~BulletList() {
	Clear();
}

//void BulletList::PushHead() {
//	/*pHead = new Bullet;
//	pHead->index = count++;
//	pHead->link = NULL;
//	pTail = pHead;*/
//}
//

void BulletList::PushTail() {
	pGet = pColliGet;

	pTail->_nextlink = pGet;
	pGet->_prelink = pTail;
	pGet->_mxOri = NULL;
	pTail = pGet;
	pTail->_nextlink = NULL;
}

void BulletList::Clear() {
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
		pDrawGet = pUseHead;
		for (int i = 0; i < _shootCount; i++)
		{
			pDrawGet->Draw();
			pDrawGet = pDrawGet->_nextlink;
		}
	}
}

void BulletList::BulletShoot(mat4 &mat) {
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
			else if (_shootCount == _totCount - 1) {
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
			printf("30\n");
		}
	}
}

void BulletList::AutoTranslate(float timeDelta) {
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
		for (int i = 0; i < _shootCount; i++)
		{
			if (pColliGet != NULL) {
				if (pColliGet->_mxTRS._m[1].w >= 2.0f) {
					DestoryBullet();
					i--;	//���s�ˬd�Ӽ�+1
				}
				else
					pColliGet = pColliGet->_nextlink;
			}
		}
	}
}

void BulletList::DestoryBullet()
{
	if (pColliGet == pUseHead) {
		//�p�G�������O��ܪ��Ĥ@���l�u(_prelink==NULL)
		pUseHead = pUseHead->_nextlink;
		pUseHead->_prelink = NULL;
		if(pUseHead == pUseTail) //�u�Ѥ@��
			pUseHead = pUseTail = NULL;
		PushTail();	//�N�l�u��^�l�u��
		pColliGet = pUseHead;
	}
	else if(pColliGet == pUseTail)
	{
		//�p�G�������O��ܪ��̫�@���l�u(_nextlink==NULL)
		//�B�@�w�OpUseHead != pUseTail ���u�Ѥ@��
		getPre = pColliGet->_prelink;
		getPre->_nextlink = NULL;
		PushTail();	//�N�l�u��^�l�u��
		pColliGet = NULL;	//�����ˬd
	}
	else {
		getPre = pColliGet->_prelink;
		getPre->_nextlink = pColliGet->_nextlink;	//���s�s��
		PushTail();	//�N�l�u��^�l�u��
		pColliGet = getPre->_nextlink;
	}
	_shootCount--;
	_storeCount++;
}