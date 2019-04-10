#pragma once
#define YY_MMD_API extern "C" __declspec(dllexport)

#include <Windows.h>
#include <vector>

#define TEXTURE_WIDTH	 1280
#define TEXTURE_HEIGHT   720

// ������kinect
struct BoneData
{
	wchar_t* name;
	float x;
	float y;
	float z;
};

namespace YYMMD
{
	class IYYMMD
	{
	public:
		// ��ʼ��dll����������߰汾��
		virtual bool init(const char* version) = 0;
		// ������־��ӡ·��
		virtual void setLogPath(const char* logPath) = 0;

		// д��ģ���ļ�,��д���˶��ļ�����������˶��ļ�����������ģ�ͣ���Ϊ�գ�������updateBoneDataд��Ĺ�������
		virtual void setModelPath(const char* modePath, const char* motionPath, const char* musicPath) = 0;

		//������������ػ�ж��mmdģ��
		virtual void setBoneAnimationFlag(bool flag) = 0;

		// ��Ⱦ
		virtual void render() = 0;

		// д���������
		virtual void updateBoneData(const BoneData* item, const int len) = 0;

		// ������������texture
		virtual void copyOfTextureData(unsigned char* dst) = 0;

		// ����ʼ��dll
		virtual bool unInit() = 0;
	};

	//��ȡIYYMMDָ��
	YY_MMD_API IYYMMD* GetInstance();
}