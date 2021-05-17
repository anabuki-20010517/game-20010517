#ifndef CMATERIAL_H
#define CMATERIAL_H
#include"CTexture.h"
class CMaterial{
public:
	char mName[64];
	float mDiffuse[4];
	CMaterial();
	void Enabled();
	CTexture mTexture;
	void Disabled();
	int mVertexNum;
};
#endif