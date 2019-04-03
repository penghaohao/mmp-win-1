#pragma once

#include <string>
#include <map>
#include <vector>
#include <glm/gtc/matrix_transform.hpp> 

struct KinectListItem
{
	std::wstring name;	// mmd�й�������������ƣ�unicode����
	std::wstring child; // Kinect�ӽڵ�����
	int index;			// mmd�й����������
};

// Kinect��19���������mmd�е�ӳ���ϵ
extern std::map<std::wstring, KinectListItem> kinectBoneList;

// Kinect�豸ģ������
extern std::vector<std::map<std::wstring, glm::vec3>> bodyInfoList;