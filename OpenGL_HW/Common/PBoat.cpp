#include "PBoat.h"

PBoat::PBoat() {

	//pBRSide
	_points[0] = vec4(0.150f, -0.12f, 0.0, 1.0f);
	_points[1] = vec4(0.230f, -0.12f, 0.0, 1.0f);
	_points[2] = vec4(0.150f, 0.02f, 0.0, 1.0f);

	//pBLSide
	_points[3] = vec4(-0.150f, -0.12f, 0.0, 1.0f);
	_points[4] = vec4(-0.230f, -0.12f, 0.0, 1.0f);
	_points[5] = vec4(-0.150f, 0.02f, 0.0, 1.0f);

	//pBBody
	_points[6] = vec4(-0.150f, -0.16f, 0.0, 1.0f);
	_points[7] = vec4(0.150f, -0.16f, 0.0, 1.0f);
	_points[8] = vec4(0.150f, 0.16f, 0.0, 1.0f);
	_points[9] = vec4(-0.150f, -0.16f, 0.0, 1.0f);
	_points[10] = vec4(0.150f, 0.16f, 0.0, 1.0f);
	_points[11] = vec4(-0.150f, 0.16f, 0.0, 1.0f);

	//cBRSide
	_colors[0] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[2] = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	//cBLSide
	_colors[3] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[4] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_colors[5] = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	//cBBody
	_colors[6] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_colors[7] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_colors[8] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_colors[9] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_colors[10] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_colors[11] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	CreateBufferObject();
}

void PBoat::CreateBufferObject() {

	glGenVertexArrays(1, &_uiVao);
	glBindVertexArray(_uiVao);

	glGenBuffers(1, &_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_points) + sizeof(_colors), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_points), _points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_points), sizeof(_colors), _colors);
}

//void PBoat::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {
void PBoat::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {

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

void PBoat::Draw() {
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);

	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	glDrawArrays(GL_TRIANGLES, 0, BPOINT_NUM);
}