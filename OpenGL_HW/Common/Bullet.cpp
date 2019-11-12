#include "Bullet.h"


Bullet::Bullet() {
	SetPoint();
	CreateBufferObject();
}

void Bullet::SetPoint() {
	
	for (int i = 0; i < POINT_NUM; i++) {
		_points[i].x = 0.07f * cosf(M_PI*2.0f*(float)(i - 10) / POINT_NUM); //2拍乘以該點分之總點
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
	Collider();
}

void Bullet::SetTRSMatrix(mat4 &mat)
{
	//矩陣改變
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

void Bullet::Collision()
{
	//if(_mxTRS)

}



//BulletList
BulletList::BulletList(mat4 g_mxModelView, mat4 g_mxProjection,int count) {

	_totCount = count; //目前所有

	//bulid bullet
	pHead = pTail = NULL;
	pHead = new Bullet;
	pHead->SetShader(g_mxModelView, g_mxProjection);
	pHead->index = 0;
	pHead->_prelink = NULL;
	pHead->_nextlink = NULL;
	pTail = pHead;
	for (int i= 1; i < count; i++)
	{
		pGet = new Bullet;
		pGet->SetShader(g_mxModelView, g_mxProjection);
		pHead->index = i;
		pGet->_prelink = pTail;
		pGet->_nextlink = NULL;
		pTail->_nextlink = pGet;
		pTail = pGet;
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
//void BulletList::PushTail() {
//	//pGet = new Bullet;
//	////pHead->index = count++;
//	//pGet->link = NULL;
//	//pTail->link = pGet;
//	//pTail = pGet;
//}

void BulletList::Clear() {
	for (int i = 0; i < _totCount; i++)
	{
		pGet = pHead;
		if (pGet != NULL) {
			pHead = pGet->_nextlink;
			delete pGet;
			i++;
		}
	}
}

void BulletList::BulletDraw() {
	if (_shootCount > 0) {
		pUseGet = pUseHead;
		for (int i = 0; i < _shootCount; i++)
		{
			pUseGet->Draw();
			pUseGet = pUseGet->_nextlink;
		}
	}
}

void BulletList::BulletShoot(mat4 &mat) {
	if (_shootCount == 0)
	{
		pUseHead = pUseTail = NULL;
		pUseHead = pHead;	//當目前use槽沒東西，跟子彈池要子彈

		pGet = pHead;
		pHead = pHead->_nextlink;	
		pHead->_prelink = NULL;	//子彈從子彈池移出

		pUseHead->_prelink = NULL;
		pUseHead -> _nextlink = NULL;
		pUseHead -> _mxOri = mat;	//存取初始位置
		pUseTail = pUseHead;
	}
	else
	{
		pUseGet = pHead;

		pGet = pHead;
		pHead = pHead->_nextlink;
		pHead->_prelink = NULL;	//子彈從子彈池移出

		pUseGet->_prelink = pUseTail;
		pUseGet->_nextlink = NULL;
		pUseGet->_mxOri = mat;	//存取初始位置
		pUseTail->_nextlink = pUseGet;
		pUseTail = pUseGet;	//use槽
	}
	_shootCount++;
}

void BulletList::AutoTranslate(float timeDelta) {
	if (_shootCount > 0) {
		pUseGet = pUseHead;
		for (int i = 0; i < _shootCount; i++)
		{
			pUseGet->AutoTranslate(timeDelta);
			pUseGet = pUseGet->_nextlink;
		}
	}
}