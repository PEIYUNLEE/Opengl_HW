#include "../Header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Transform {
private:
	//data
	int _pointNum;
	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;

	mat4 _mxView, _mxProjection;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

public:
	mat4  _mxTRS;
	mat4 _mxMVFinal;
	vec4 *_points, *_colors;

	Transform(int pointNum);
	//~Transform();


	void CreateBufferObject();

	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }
	void AutoTranslate(float dt);
	void SetTRSMatrix(mat4 &mat);
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);


	void Draw();

};