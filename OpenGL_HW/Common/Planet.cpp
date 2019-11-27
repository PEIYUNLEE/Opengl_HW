#include "Planet.h"

Planet::Planet(mat4 &mxView, mat4 &mxProjection) {
	_fspeed = -0.75f;
	_radius = 0.04f;
	_ftottime = 0.0f;
	SetPoint();
	_transform = new Transform(mxView, mxProjection, CPOINT_NUM, _points, _colors);
}

Planet::~Planet() {
	if (_transform != NULL) delete _transform;
	if (_points != NULL) delete _points;
	if (_colors != NULL) delete _colors;
}

void Planet::SetPoint() {
	_points = new vec4[CPOINT_NUM];
	_colors = new vec4[CPOINT_NUM];


	for (int i = 0; i < CPOINT_NUM; i++) {
		_points[i].x = _radius * cosf(M_PI*2.0f*i / CPOINT_NUM); //2拍乘以該點分之總點
		_points[i].y = _radius * sinf(M_PI*2.0f*i / CPOINT_NUM);
		_points[i].w = 1.0f;
		_colors[i] = _COLOR_WHITE;
	}
}

void Planet::AutoTranslate(float dt) {
	mat4 mxTra;
	GLfloat tx = 0.0f;
	GLfloat ty = 0.0f;

	_ftottime += dt;
	ty = _ftottime*_fspeed;
	mxTra = Translate(tx, ty,0.0f);

	if (_transform->_mxTRS._m[1].w <= -2.6f) {
		_ftottime = 0.0f;
		_transform->_mxOri._m[1].w = 2.6f;
		_transform->_mxTRS._m[1].w = 2.6f;
	}

	_transform->SetTRSMatrix(mxTra*_transform->_mxOri);
	
}

void Planet::Draw() {
	_transform->Draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, CPOINT_NUM);
}




///////////PlanetManager
PlanetManager::PlanetManager(mat4 &mxView, mat4 &mxProjection) {

	_planetCount = 18;
	PlanetGenerator(mxView, mxProjection);
}

PlanetManager::~PlanetManager() {
	Clear();
}

void PlanetManager::Clear() {
	for (int i = 0; i < _planetCount; i++)
	{
		_pGet = _pHead;
		if (_pGet != NULL) {
			_pHead = _pGet->_nextlink;
			delete _pGet;
			i++;
		}
	}
}

void PlanetManager::PlanetGenerator(mat4 &mxView, mat4 &mxProjection) {

	_pHead = _pTail = NULL;
	_pHead = new Planet(mxView, mxProjection);
	_pTail = _pHead;
	_pGet = _pHead;
	SetPosition(1.25f,2.0f);

	_pGet = NULL;
	for (int i = 1,y = 1; i < _planetCount; i++)
	{
		_pGet = new Planet(mxView, mxProjection);
		_pTail->_nextlink = _pGet;
		_pTail = _pGet;

		if (i == 1)
			SetPosition(1.75f, 1.25f);
		else if (i == 2)
			SetPosition(0.8f, 0.75f);
		else if (i == 3)
			SetPosition(0.3f, 1.5f);
		else if (i == 4)
			SetPosition(1.0f, -0.2f);
		else if (i == 5)
			SetPosition(0.0f, 0.25f);
		else if (i == 6)
			SetPosition(-0.65f, 1.0f);
		else if (i == 7)
			SetPosition(-0.85f, 2.0f);
		else if (i == 8)
			SetPosition(-1.5f, 1.5f);
		else if (i == 9)
			SetPosition(-2.2f, 0.5f);
		else if (i == 10)
			SetPosition(2.0f, 0.5f);
		else if (i == 11)
			SetPosition(-1.2f, 0.0f);
		else if (i == 12)
			SetPosition(-1.5f, -2.0f);
		else if (i == 13)
			SetPosition(-0.55f, -0.75f);
		else if (i == 14)
			SetPosition(0.3f, -1.25f);
		else if (i == 15)
			SetPosition(1.0f, -1.8f);
		else if (i == 16)
			SetPosition(1.65f, -0.7f);
		else if (i == 17)
			SetPosition(-2.0f, -1.3f);
		else if (i == 18)
			SetPosition(-0.2f, -2.5f);

	}
}

void PlanetManager::PlanetDraw() {
	Planet *pDrawGet;
	pDrawGet = _pHead;
	for (int i = 0; i < _planetCount; i++)
	{
		if (pDrawGet != NULL) {
			pDrawGet->Draw();
			pDrawGet = pDrawGet->_nextlink;
		}
	}
}

void PlanetManager::Update(float dt) {
	Planet *pUpdateGet;
	pUpdateGet = _pHead;
	for (int i = 0; i < _planetCount; i++)
	{
		if (pUpdateGet != NULL) {
			pUpdateGet->AutoTranslate(dt);
			pUpdateGet = pUpdateGet->_nextlink;
		}
	}
}

void PlanetManager::SetPosition(float X,float Y) {
	mat4 mat;

	mat._m[0].w = X;
	mat._m[1].w = Y;
	_pGet->_transform->_mxOri = mat;
	_pGet->_transform->_mxTRS = mat;
	_pGet->_transform->SetTRSMatrix(mat);

}

