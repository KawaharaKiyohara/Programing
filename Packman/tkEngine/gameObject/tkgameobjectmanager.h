/*!
 *@brief	CGameObject�̃}�l�[�W���[�B
 */

#ifndef _CGAMEOBJECTMANAGER_H_
#define _CGAMEOBJECTMANAGER_H_

#include "tkEngine/gameObject/tkGameObject.h"

namespace tkEngine{
	/*!
	 *@brief	CGameObject�̃}�l�[�W���N���X�B
	 */
	class CGameManager : Noncopyable{
	private:
		CGameManager() :
			m_gameObjectPriorityMax(0)
		{
		}
		~CGameManager()
		{
		}
	public:
		/*!
		 *@brief	�C���X�^���X�̎擾�B
		 */
		static CGameManager& GetInstance()
		{
			static CGameManager instance;
			return instance;
		}
		/*!
		 *@brief	�������B
		 *@param[in]	gameObjectPrioMax	�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
		 */
		void Init( u32 gameObjectPrioMax )
		{
			m_gameObjectPriorityMax = gameObjectPrioMax;
		}
		/*!
		 *@brief	�Q�[���I�u�W�F�N�g��new
		 *@param	prio	���s�D�揇�ʁB
		 */
		template<class T>
		T* NewGameObject( u32 prio )
		{
			T* newObject = new T();
			newObject->Awake();
		}
		/*!
		 *@brief	�Q�[���I�u�W�F�N�g�̍폜�B
		 */
		void DeleteGameObject( IGameObject* gameObject )
		{
			gameObject->OnDestroy();
		}
	private:
		std::list<IGameObject*>	m_gameObjectList;	//!<�Q�[���I�u�W�F�N�g�̃��X�g�B
		std::list<IGameObject*>	m_deleteObjectList;	//!<�폜����I�u�W�F�N�g�̃��X�g�B
		u32 m_gameObjectPriorityMax;	//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
	};
}
#endif // _CGAMEOBJECTMANAGER_H_
 