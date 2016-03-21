/*!
 *@brief	CGameObject�̃}�l�[�W���[�B
 */

#ifndef _CGAMEOBJECTMANAGER_H_
#define _CGAMEOBJECTMANAGER_H_

#include "tkEngine/gameObject/tkGameObject.h"

namespace tkEngine{
	struct SRenderContextMap;
	/*!
	 *@brief	CGameObject�̃}�l�[�W��
	 */
	class CGameObjectManager : Noncopyable{
	private:
		CGameObjectManager() :
			m_gameObjectPriorityMax(0)
		{
		}
		~CGameObjectManager()
		{
		}
	public:
		/*!
		 *@brief	�C���X�^���X�̎擾�B
		 */
		static CGameObjectManager& GetInstance()
		{
			static CGameObjectManager instance;
			return instance;
		}
		/*!
		*@brief	���s�B
		*@param[in]	renderContext		�����_�����O�R���e�L�X�g�B
		*@param[in]	numRenderContext	�����_�����O�R���e�L�X�g�̐��B
		*@param[in]	renderContextMap	�����_�����O�R���e�L�X�g�̃}�b�v�B
		*/
		void Execute( CRenderContext* renderContext, u32 numRenderContext, const SRenderContextMap* renderContextMap );
		/*!
		 *@brief	�������B
		 *@param[in]	gameObjectPrioMax	�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B(255�܂�)
		 */
		void Init( u32 gameObjectPrioMax );
		/*!
		 *@brief	�Q�[���I�u�W�F�N�g��new
		 *@param	prio	���s�D�揇�ʁB
		 */
		template<class T>
		T* NewGameObject(GameObjectPrio prio )
		{
			TK_ASSERT( prio <= m_gameObjectPriorityMax, "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
			T* newObject = new T();
			newObject->Awake();
			m_gameObjectListArray.at(prio).push_back(newObject);
			return newObject;
		}
		/*!
		 *@brief	�Q�[���I�u�W�F�N�g�̍폜�B
		 */
		void DeleteGameObject( IGameObject* gameObject )
		{
			gameObject->OnDestroy();
			m_deleteObjectArray.at(gameObject->GetPriority()).push_back(gameObject);
		}
	private:
		/*!
		 *@brief	�Q�[���I�u�W�F�N�g�̍폜�����s�B
		 */
		void ExecuteDeleteGameObjects();
	private:
		typedef std::list<IGameObject*>	GameObjectList;
		std::vector<GameObjectList>	m_gameObjectListArray;	//!<�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
		std::vector<GameObjectList>	m_deleteObjectArray;	//!<�폜����I�u�W�F�N�g�̃��X�g�B
		GameObjectPrio				m_gameObjectPriorityMax;		//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
		static const u8 			GAME_OBJECT_PRIO_MAX = 255;		//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B
	};
}
#endif // _CGAMEOBJECTMANAGER_H_
 