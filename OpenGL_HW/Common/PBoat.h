#include "../Header/Angel.h"
#include "Bullet.h"

#define BSPOINT_NUM 3 //side
#define BBPOINT_NUM 4 //body
#define BCPOINT_NUM 20 //center circle
#define BTPOINT_NUM 11 //top circle
#define BPPOINT_NUM 21 //©ßª«½u
#define BTOTPOINT_NUM BSPOINT_NUM*2+BBPOINT_NUM+BCPOINT_NUM+BTPOINT_NUM+BPPOINT_NUM*2+1

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class PBoat
{
private:
	vec4 _points[BTOTPOINT_NUM];
	vec4 _colors[BTOTPOINT_NUM];
	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;

	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

	BulletList *_bulletList= new BulletList(5);
	int _bulletCount=0;

	void CreateBufferObject();
public:
	PBoat();
	~PBoat();

	void SetPoint();
	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }
	void SetTRSMatrix(mat4 &mat);
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);

	void Shoot(mat4 mxModelView, mat4 mxProjection);

	void Draw();
};