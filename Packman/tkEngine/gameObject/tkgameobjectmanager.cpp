/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/gameObject/tkgameobjectmanager.h"

namespace tkEngine{
	void CGameObjectManager::Execute(const CRenderContext& renderContext )
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreUpdate();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->Update();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostUpdate();
			}
		}

		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreRender(renderContext);
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->Render(renderContext);
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostRender(renderContext);
			}
		}

	}
	void CGameObjectManager::Init( u32 gameObjectPrioMax )
	{
		TK_ASSERT( gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
		m_gameObjectPriorityMax = gameObjectPrioMax;
		m_gameObjectListArray.resize(gameObjectPrioMax);
	}
}