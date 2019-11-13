#include "../Header/Angel.h"
#include "Struct.h"

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
	mat4  _mxTRS;
	mat4 _mxOri;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();

	float _fspeed =0.7f;
	float _ftottime;

	//node
	Bullet *_prelink;
	Bullet *_nextlink;
	struct Collider _collider;
public:
	mat4 _mxMVFinal;

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
	Bullet *pUseTail, *pUseHead;
	Bullet *pHead, *pTail, *pNewGet;
	Bullet *pColliGet, *pGet, *pClearGet,*pDrawGet, *pNewBulletGet, *pTraGet, *getPre;

	int _totCount;

public:
	int _shootCount = 0;
	int _storeCount = 0;

	BulletList(mat4 g_mxModelView, mat4 g_mxProjection,int count);
	~BulletList();
	void PrintList();			// �L�Xlist���Ҧ����
	void PushHead();		// �blist�����ڷs�Wnode
	void PushTail();		// �blist�����ڷs�Wnode
	void Delete(int index);			// �R��list����index
	void Clear();					// ����list�R��
	void BulletShoot(mat4 &mat);
	void BulletDraw();
	void AutoTranslate(float timeDelta);

	void Collision();	//�P�w���S���I��ĤH�ζW�X�d��
	void DestoryBullet();	//�N�l�u��^�l�u��
};