#ifndef VIEWER_H
#define VIEWER_H

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GL/glfw.h>

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>
#include <map>
#include <string>
#include "IYYMMD.h"
#include "QcCriticalLock.h"

#define BUFFER_OFFSET(offset) ((void *) (offset))

enum VAO_IDs { Vertices, NumVAOs };
enum Buffer_IDs { VertexArrayBuffer, VertexIndexBuffer, RecordBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vUV, vNormal, vBoneIndices, vBoneWeights, vWeightFormula };
enum Uniform_IDs { 
	uAmbient,uDiffuse,uSpecular,uShininess,
	uIsEdge,uEdgeColor,uEdgeSize,
	uHalfVector,uLightDirection,
	uSphereMode,
	uTextureSampler,uSphereSampler,uToonSampler,
	NumUniforms };

namespace ClosedMMDFormat
{
	struct PMXInfo;
	struct VMDInfo;
}
class VMDMotionController;
class BulletPhysics;
class MMDPhysics;
class VertexData;
class Ground;


class Viewer
{
public:
	Viewer(std::string modelPath, std::string motionPath, std::string musicPath="", bool dllCall = false);
	~Viewer();
	void init();
	void run();	
	void copyOfTextureData(unsigned char* dst);
	void setBoneAnimationFlag(bool flag);
	void updateBoneData(const BoneData* item, const int len);
	void unint();

private:
	void initGLFW();
	void hackShaderFiles(); //modify #version lines in shader files to match GL version
	void initUniformVarLocations();
	void loadTextures();
	void initBuffers();
	
	void handleEvents();
	void handleLogic();
	void updateViewMatrix();
	void render();
	void fpsCount();
	
	void setCamera(GLuint MVPLoc);
	void holdModelInBindPose();
	
	void drawModel(bool drawEdges);
	
private:
	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];
	GLuint uniformVars[NumUniforms];

	GLuint MVP_loc;

	ClosedMMDFormat::PMXInfo *pmxInfo;
	ClosedMMDFormat::VMDInfo *vmdInfo;
	VMDMotionController *motionController;

	BulletPhysics *bulletPhysics;
	MMDPhysics *mmdPhysics;

	std::vector<GLuint> textures;
	
	//The OpenGL Version hints used that successfully opened the window
	int GLVersionHintMajor,GLVersionHintMinor;
	//The actual OpenGL Version recieved
	int GLVersionMajor,GLVersionMinor,GLVersionRevision;
	
	std::string vertShaderPath,fragShaderPath;
	GLuint shaderProgram;
	std::string bulletVertPath,bulletFragPath;
	
	//***Timing Variables
	double startTime;
	int ticks;
	
	glm::vec3 modelTranslate;
	GLfloat fov;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	Ground* m_ground;

	std::string m_motionPath;	// 控制传入mmp的运动路径，若为空，则直接用传入的bonedata,若不为空，则采用motionpath
	bool		m_dllCall;		// 控制是否创建glfw窗口

	GLuint				m_imageFBO;
	GLuint				m_offscreenTexture;
	GLuint				m_depthTextureID;

	std::map<std::wstring, glm::vec3> m_boneDatas;
	QcCriticalLock					  m_boneDataLock;
	bool							  m_boneAnimationFlag;
};


#endif
