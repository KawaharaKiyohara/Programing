/*!
 * @brief	�v���R���p�C���ς݃w�b�_�[�B
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <windows.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "Physics\Physics.h"
using namespace tkEngine;
#include "GameCamera.h"


static const float GAME_DELTA_TIME = 1.0f / 60.0f;	//1�t���[���̌o�ߎ���(�P��:�b)�B�Œ�FPS�B
extern PhysicsWorld* g_physicsWorld ;
#endif // _STDAFX_H_