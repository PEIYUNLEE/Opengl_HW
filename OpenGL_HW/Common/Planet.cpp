#include "Planet.h"

Planet::Planet(float radius, int colorType,float fspeed, float fduration, int pointsNum) {

	_pointsNum = pointsNum+(pointsNum+1) + (pointsNum + 1);
	_fspeed = fspeed;
	_fduration = fduration;

	_points = new vec4[_pointsNum];
	_colors = new vec4[_pointsNum];

	
	for (int i = 0; i < pointsNum; i++) {
		_points[i].x = radius * cosf(M_PI*2.0f*i / pointsNum); //2拍乘以該點分之總點
		_points[i].y = radius * sinf(M_PI*2.0f*i / pointsNum);
		_points[i].w = 1.0f;
		_colors[i] = SetColor(colorType);
	}

	for (int i = pointsNum; i < pointsNum*2 + 1; i++) {
		_points[i].x = (radius + 0.05f) * cosf(M_PI*2.0f*(i- pointsNum) / pointsNum); //2拍乘以該點分之總點
		_points[i].y = (radius + 0.05f) * sinf(M_PI*2.0f*(i - pointsNum) / pointsNum);
		_points[i].w = 1.0f;
		_colors[i] = SetColor(colorType);
	}

	for (int i = pointsNum*2 + 1; i < _pointsNum; i++) {
		_points[i].x = (radius + 0.125f) * cosf(M_PI*2.0f*(i- (pointsNum * 2 + 1)) / pointsNum); //2拍乘以該點分之總點
		_points[i].y = (radius + 0.125f) * sinf(M_PI*2.0f*(i - (pointsNum * 2 + 1)) / pointsNum);
		_points[i].w = 1.0f;
		_colors[i] = SetColor(colorType);
	}

	CreateBufferObject();
	_bUpdateProj = false;
}

Planet::~Planet() {
	delete [] _points;
	delete [] _colors;
	delete [] _vsh;
}

vec4 Planet::SetColor(int type) {
	vec4 color;

	if (type == 1) color = vec4(0.4f, 0.56f, 0.8f, 1.0f); //淡藍
	else if (type == 2)  color = vec4(0.7f, 0.4f, 0.8f, 1.0f);  //淡綠
	else if (type == 3) color = vec4(0.4f, 0.7f, 0.68f, 1.0f); //淡紫
	else color = vec4(0.84f, 0.85f, 0.61f, 1.0f); //淡藍紫

	return color;
}

void Planet::CreateBufferObject() {

	glGenVertexArrays(1, &_uiVao);
	glBindVertexArray(_uiVao);

	glGenBuffers(1, &_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*_points)*_pointsNum + sizeof(*_colors)*_pointsNum, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*_points)*_pointsNum, *_points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(*_points)*_pointsNum, sizeof(*_colors)*_pointsNum, *_colors);
}

void Planet::SetVShaderName(char* vsh) {
	int *pix = new int;
	*pix = strlen(vsh)+1;
	_vsh = new char[*pix];
	memcpy(_vsh,vsh,*pix);
	delete pix;
}

void Planet::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {

	if (uiShaderHandle == MAX_UNSIGNED_INT) _uiProgram = InitShader(_vsh, "fsVtxColor.glsl");
	else _uiProgram = uiShaderHandle;

	GLuint vPosition = glGetAttribLocation(_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(_uiProgram, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(*_points)*_pointsNum));

	_uiModelView = glGetUniformLocation(_uiProgram, "ModelView");
	_mxView = mxView;
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxView);

	_uiProjection = glGetUniformLocation(_uiProgram, "Projection");
	_mxProjection = mxProjection;
	glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//float g_Tottime = 0.0;
GLfloat tx = 0.0f;
GLfloat ty = 0.0f;

void Planet::AutoTranslate(float dt) {
	mat4 mxTra;

	_ftottime += dt;
	if (_ftottime >= _fduration) _ftottime -= _fduration;
	ty = _ftottime*_fspeed;
	mxTra = Translate(tx, ty,0.0f);

	SetTRSMatrix(mxTra);
}

void Planet::SetTRSMatrix(mat4 &mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void Planet::Draw() {
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);

	//更新
	if (_bUpdateMV) {
		_mxMVFinal = _mxView*_mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 500);
	glDrawArrays(GL_LINE_LOOP, 500, 501);
	glDrawArrays(GL_LINE_LOOP, 1001, 501);
}