#include "../Header/Angel.h"

#define POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

//class BulletList;

class Bullet
{
private:
	//data
	vec4 _points[POINT_NUM];
	vec4 _colors[POINT_NUM];
	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;

	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();

	int index;
	float _fspeed =0.7f;
	float _ftottime;

	//node
	Bullet *link;


public:
	Bullet();

	void SetPoint();
	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }
	void AutoTranslate(float dt);
	void SetTRSMatrix(mat4 &mat);
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);

	void Draw();

	//list
	friend class BulletList;
};

class BulletList{
private:
	Bullet *pHead, *pTail, *pGet;
	int _totCount;

public:
	BulletList(int count);
	void PrintList();			// 印出list的所有資料
	void PushHead();		// 在list的尾巴新增node
	void PushTail();		// 在list的尾巴新增node
	void Delete(int index);			// 刪除list中的index
	void Clear();					// 把整串list刪除
	void BulletDraw(mat4 g_mxModelView, mat4 g_mxProjection);
};