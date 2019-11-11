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

GLfloat btx = 0.0f;
GLfloat bty = 0.0f;

void Bullet::AutoTranslate(float dt) {
	mat4 mxTra;

	_ftottime += dt;
	bty = _ftottime*_fspeed;
	mxTra = Translate(btx, bty, 0.0f);

	SetTRSMatrix(mxTra);
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

//BulletList
BulletList::BulletList(int count) {

	_totCount = count; //目前所有

	//bulid bullet
	pHead = pTail = NULL;
	pHead = new Bullet;
	pHead->index = 0;
	pHead->link = NULL;
	pTail = pHead;
	for (int i= 1; i < count; i++)
	{
		pGet = new Bullet;
		pHead->index = i;
		pGet->link = NULL;
		pTail->link = pGet;
		pTail = pGet;
	}
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
	pGet = pHead;
	for (int i = 0; i < _totCount; i++)
	{
		if (pGet != NULL) {
			printf("%d個是%d", i, pGet->index);
			pHead = pGet->link;
			delete pGet;
			i++;
		}
	}
}

void BulletList::BulletDraw(mat4 g_mxModelView, mat4 g_mxProjection) {
	pGet->SetShader(g_mxModelView, g_mxProjection);
	pGet = pGet->link;
}
