//#include "../OpenGL_HW/Header/Angel.h"
//
//#define BPoint_NUM 12
//#define BColor_NUM 2
//
//typedef Angel::vec4  color4;
//typedef Angel::vec4  point4;
//
//class PBoat
//{
//private:
//	vec4 _Points[BPoint_NUM];
//	vec4 _Colors[BPoint_NUM];
//	GLuint _uiVao;
//	GLuint _uiBuffer;
//	GLuint _uiProgram;
//	GLuint _uiModelView, _uiProjection;
//
//	mat4 _mxView, _mxProjection;
//	mat4 _mxMVFinal, _mxTRS;
//
//	void CreateBufferObject();
//public:
//	PBoat();
//
//	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
//	GLuint GetShaderHandle() { return _uiProgram; }
//	void SetViewMatrix(mat4 &mat);
//	void SetProjectionMatrix(mat4 &mat);
//
//	void Draw();
//};