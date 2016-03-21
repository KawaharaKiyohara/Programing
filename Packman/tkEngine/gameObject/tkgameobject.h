/*!
 *@brief	�Q�[���I�u�W�F�N�g�̊��N���X�B
 */

#ifndef _CGAMEOBJECT_H_
#define _CGAMEOBJECT_H_


namespace tkEngine{
	class CGameObjectManager;
	class CRenderContext;
	typedef u8	GameObjectPrio;
	/*!
	 *@brief	�Q�[���I�u�W�F�N�g�B
	 */
	class IGameObject : Noncopyable{
	public:
		IGameObject() :
			m_priority(0)
		{
		}
		/*!
		 *@brief	�f�X�g���N�^
		 */
		virtual ~IGameObject()
		{
		}
	public:
		/*!
		 *@brief	�X�V
		 */
		virtual void Update() = 0;
		/*!
		 *@brief	�`��
		 */
		virtual void Render( CRenderContext& renderContext ) = 0;
		/*!
		 *@brief	�폜�����Ƃ��ɌĂ΂��B
		 *@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
		 * �f�X�g���N�^���O�Ɏ��s����܂��B
		 */
		virtual void OnDestroy(){} 
		/*!
		*@brief	���s�D��x���擾�B
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
	public:
		/*!
		 *@brief	�C���X�^���X���������ꂽ����ɌĂ΂��֐��B
		 *@details	�R���X�g���N�^���Ă΂ꂽ��ő��Ă΂�܂��B
		 */
		virtual void Awake(){}
		/*!
		 *@brief	Update�֐������s�����O�ɌĂ΂��X�V�֐��B
		 */
		virtual void PreUpdate() {}
		/*!
		 *@brief	Update�֐������s���ꂽ��ŌĂ΂��X�V�֐��B
		 */
		virtual void PostUpdate() {} 
		/*!
		 *@brief	Render�֐������s�����O�ɌĂ΂��`�揈���B
		 */
		virtual void PreRender( CRenderContext& renderContext ) {}
		/*!
		 *@brief	Render�֐������s���ꂽ��ŌĂ΂��`�揈��
		 */
		virtual void PostRender(CRenderContext& renderContext ) {}

		friend class CGameObjectManager;
	protected:
		GameObjectPrio	m_priority;		//!<���s�D��x�B
		
	};
}
#endif // _CGAMEOBJECT_H_