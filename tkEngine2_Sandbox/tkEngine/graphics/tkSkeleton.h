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
		*@param[in] localMatrix		���[�J���s��B
		*@param[in]	parentId		�e�̃{�[���ԍ��B
		*/
		CBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			const CMatrix& localMatrix,
			int parentId
		) :
			m_boneName(boneName),
			m_bindPose(bindPose),
			m_invBindPose(invBindPose),
			m_localMatrix(localMatrix),
			m_parentId(parentId)
		{
			if (m_parentId == -1) {
				m_offsetLocalMatrix.Inverse(m_localMatrix);
				m_offsetLocalMatrix.Mul(m_offsetLocalMatrix, m_bindPose);
			}
			
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
	private:
		std::wstring	m_boneName;
		int				m_parentId = -1;	//!<�e�̃{�[���ԍ��B
		CMatrix			m_bindPose;		//!<�o�C���h�|�[�Y�B
		CMatrix			m_invBindPose;	//!<�o�C���h�|�[�Y�̋t�s��B
		CMatrix			m_localMatrix;	//!<���[�J���s��B
		CMatrix			m_worldMatrix = CMatrix::Identity;	//!<���[���h�s��B
		CMatrix			m_offsetLocalMatrix;
		std::list<CBone*>	m_children;		//!<�q���B
	};
	/*!
	 *@brief	�X�P���g���B
	 */
	class CSkeleton : Noncopyable {
	public: //�G���W�������ł̂݌Ăяo���K�v�̂���֐�
		CSkeleton();
		~CSkeleton();
		/*!
		*@brief	�{�[����ǉ��B
		*@param[in]	boneName		�{�[���̖��O�B
		*@param[in]	bindPose		�o�C���h�|�[�Y�̍s��B
		*@param[in] invBindPose		�o�C���h�|�[�Y�̋t�s��B
		*@param[in] localMatrix		���[�J���s��B
		*@param[in] parentId		�e�̃{�[���ԍ��B
		*/
		void AddBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			const CMatrix& localMatrix,
			int parentId
		);
		
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
	public:
		/*!
		*@brief	���ׂł̃{�[���̒ǉ������������Ƃ��ɌĂяo���K�v�����鏈���B
		*/
		void OnCompleteAddedAllBones();
		/*!
		 *@brief	�X�V�B
		 */
		void Update(const CMatrix& mWorld);
		/*!
		 *@brief	�`�揈������Ă΂�鏈���B
		 */
		void Render(CRenderContext& rc);
	private:
		static const int BONE_MAX = 512;	//!<�{�[���̍ő吔�B
		typedef std::unique_ptr<CBone>	CBonePtr;
		std::vector<CBonePtr>	m_bones;	//!<�{�[���̔z��B
		std::unique_ptr<CMatrix[]>	m_boneMatrixs;	//!<�{�[���s��B
		CStructuredBuffer			m_boneMatrixSB;	//!<�{�[���s��̃X�g���N�`���[�o�b�t�@�B
	};
}