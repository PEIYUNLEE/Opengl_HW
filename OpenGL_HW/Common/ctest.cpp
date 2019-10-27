//#include "ctest.h"
//
//PBoat::PBoat() {
//
//	//pBRSide
//	_Points[0] = vec4(0.075f, -0.06f, 0.0, 1.0f);
//	_Points[1] = vec4(0.115f, -0.06f, 0.0, 1.0f);
//	_Points[2] = vec4(0.075f, 0.01f, 0.0, 1.0f);
//
//	//pBLSide
//	_Points[3] = vec4(-0.075f, -0.06f, 0.0, 1.0f);
//	_Points[4] = vec4(-0.115f, -0.06f, 0.0, 1.0f);
//	_Points[5] = vec4(-0.075f, 0.01f, 0.0, 1.0f);
//
//	//pBBody
//	_Points[6] = vec4(-0.075f, -0.08f, 0.0, 1.0f);
//	_Points[7] = vec4(0.075f, -0.08f, 0.0, 1.0f);
//	_Points[8] = vec4(0.075f, 0.08f, 0.0, 1.0f);
//	_Points[9] = vec4(-0.075f, -0.08f, 0.0, 1.0f);
//	_Points[10] = vec4(0.075f, 0.08f, 0.0, 1.0f);
//	_Points[11] = vec4(-0.075f, 0.08f, 0.0, 1.0f);
//
//	//cBRSide
//	_Colors[0] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	_Colors[2] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//
//	//cBLSide
//	_Colors[3] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	_Colors[4] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	_Colors[5] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//
//	//cBBody
//	_Colors[6] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	_Colors[7] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	_Colors[8] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	_Colors[9] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	_Colors[10] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	_Colors[11] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//
//	CreateBufferObject();
//}
//
//void PBoat::CreateBufferObject() {
//
//	glGenVertexArrays(1, &_uiVao);
//	glBindVertexArray(_uiVao);
//
//	glGenBuffers(1, &_uiBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(_Points) + sizeof(_Colors), NULL, GL_STATIC_DRAW);
//
//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_Points), _Points);
//	glBufferSubData(GL_ARRAY_BUFFER, sizeof(_Points), sizeof(_Colors), _Colors);
//}
//
////void PBoat::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {
//void PBoat::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle) {
//
//	if(uiShaderHandle == MAX_UNSIGNED_INT) _uiProgram = InitShader("vsVtxColor.glsl", "fsVtxColor.glsl");
//	else _uiProgram = uiShaderHandle;
//
//	GLuint vPosition = glGetAttribLocation(_uiProgram, "vPosition");
//	glEnableVertexAttribArray(vPosition);
//	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//
//	GLuint vColor = glGetAttribLocation(_uiProgram, "vColor");
//	glEnableVertexAttribArray(vColor);
//	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(_Points)));
//
//	_uiModelView = glGetUniformLocation(_uiProgram, "ModelView");
//	_mxView = mxView;
//	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxView);
//
//	_uiProjection = glGetUniformLocation(_uiProgram, "Projection");
//	_mxProjection = mxProjection;
//	glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void PBoat::Draw() {
//	glUseProgram(_uiProgram);
//	glBindVertexArray(_uiVao);
//
//	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);
//
//	glDrawArrays(GL_TRIANGLES, 0, BPoint_NUM);
//}