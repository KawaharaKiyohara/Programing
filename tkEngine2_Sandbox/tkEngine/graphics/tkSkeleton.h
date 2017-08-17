/*!
 *@brief	�X�P���g��
 */
#pragma once


namespace tkEngine{
	/*!
	*@brief	�{�[���B
	*/
	class CBone : Noncopyable{
	public:
		/*!
		*@brief	�R���X�g���N�^�B
		*@param[in]	boneName		�{�[���̖��O�B
		*@param[in]	bindPose		�o�C���h�|�[�Y�̍s��B
		*@param[in] invBindPose		�o�C���h�|�[�Y�̋t�s��B
		*@param[in]	parentId		�e�̃{�[���ԍ��B
		*/
		CBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			int parentId
		) :
			m_boneName(boneName),
			m_bindPose(bindPose),
			m_invBindPose(invBindPose),
			m_parentId(parentId)
		{
		}
		/*!
		 *@brief	���[�J���s���ݒ�
		 */
		void SetLocalMatrix(const CMatrix& m)
		{
			m_localMatrix = m;
		}
		/*!
		 *@brief	���[�J���s����擾�B
		 */
		const CMatrix& GetLocalMatrix() const
		{
			return m_localMatrix;
		}
		/*!
		*@brief	���[���h�s���ݒ�B
		*/
		void SetWorldMatrix(const CMatrix& m)
		{
			m_worldMatrix = m;
		}
		/*!
		 *@brief	���[���h�s����擾�B
		 */
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	�o�C���h�|�[�Y�̍s����擾�B
		*/
		const CMatrix& GetBindPoseMatrix() const
		{
			return m_bindPose;
		}
		/*!
		 *@brief	�o�C���h�|�[�Y�̋t�s����擾�B
		 */
		const CMatrix& GetInvBindPoseMatrix() const
		{
			return m_invBindPose;
		}
		/*!
		 *@brief	�e�̃{�[���s����擾�B
		 */
		int GetParentId() const
		{
			return m_parentId;
		}
		/*!
		*@brief	�q����ǉ��B
		*/
		void AddChild(CBone* bone) 
		{
			m_children.push_back(bone);
		}
		/*!
		*@brief	�q�����擾�B
		*/
		std::list<CBone*>& GetChildren()
		{
			return m_children;
		}
		const CMatrix& GetOffsetLocalMatrix() const
		{
			return m_offsetLocalMatrix;
		}
		/*!
		 *@brief	���O�̎擾�B
		 */
		const std::wstring& GetName() const
		{
			return m_boneName;
		}
	private:
		std::wstring	m_boneName;
		int				m_parentId = -1;	//!<�e�̃{�[���ԍ��B
		CMatrix			m_bindPose;		//!<�o�C���h�|�[�Y�B
		CMatrix			m_invBindPose;	//!<�o�C���h�|�[�Y�̋t�s��B
		CMatrix			m_localMatrix = CMatrix::Identity;	//!<���[�J���s��B
		CMatrix			m_worldMatrix = CMatrix::Identity;	//!<���[���h�s��B
		CMatrix			m_offsetLocalMatrix;
		std::list<CBone*>	m_children;		//!<�q���B
	};
	/*!
	 *@brief	�X�P���g���B
	 */
	class CSkeleton : Noncopyable {
	public:
		CSkeleton();
		~CSkeleton();
		
		/*!
		 *@brief	�{�[���̃��[�J���s���ݒ�B
		 *@param[in]	boneNo		�{�[���ԍ�
		 *@param[in]	m			�s��B
		 */
		void SetBoneLocalMatrix(int boneNo, const CMatrix& m)
		{
			if (boneNo > (int)m_bones.size() - 1) {
				TK_WARNING("boneNo is over m_bones.size() ");
				return;
			}
			m_bones[boneNo]->SetLocalMatrix(m);
		}
		/*!
		 *@brief	�{�[���̐����擾�B
		 */
		int GetNumBones() const
		{
			return static_cast<int>(m_bones.size());
		}
		/*!
		*@brief	���[�h�B
		*@param[in]	filePath	�t�@�C���p�X�B
		*/
		bool Load(const wchar_t* filePath);
		/*!
		 *@brief	�{�[���̖��O����{�[��ID�������B
		 */
		int FindBoneID(const wchar_t* boneName) const
		{
			for (int i = 0; i < m_bones.size(); i++) {
				if (m_bones[i]->GetName() == boneName) {
					return i;
				}
			}
			//������Ȃ������B
			return -1;
		}
	public:
		
		/*!
		 *@brief	�X�V�B
		 */
		void Update(const CMatrix& mWorld);
		/*!
		 *@brief	�`�揈������Ă΂�鏈���B
		 */
		void Render(CRenderContext& rc);
	private:
		/*!
		*@brief	���ׂł̃{�[���̒ǉ������������Ƃ��ɌĂяo���K�v�����鏈���B
		*/
		void OnCompleteAddedAllBones();
	private:
		static const int BONE_MAX = 512;	//!<�{�[���̍ő吔�B
		typedef std::unique_ptr<CBone>	CBonePtr;
		std::vector<CBonePtr>	m_bones;	//!<�{�[���̔z��B
		std::unique_ptr<CMatrix[]>	m_boneMatrixs;	//!<�{�[���s��B
		CStructuredBuffer			m_boneMatrixSB;	//!<�{�[���s��̃X�g���N�`���[�o�b�t�@�B
	};
}