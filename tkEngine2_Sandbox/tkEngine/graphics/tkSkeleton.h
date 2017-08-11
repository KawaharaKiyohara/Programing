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
		*/
		CBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			const CMatrix& localMatrix
		) :
			m_boneName(boneName),
			m_bindPose(bindPose),
			m_invBindPose(invBindPose),
			m_localMatrix(localMatrix)
		{
		}

	private:
		std::wstring	m_boneName;
		CMatrix			m_bindPose;		//!<�o�C���h�|�[�Y�B
		CMatrix			m_invBindPose;	//!<�o�C���h�|�[�Y�̋t�s��B
		CMatrix			m_localMatrix;	//!<���[�J���s��B
		CMatrix			m_worldMatrix = CMatrix::Identity;	//!<���[���h�s��B
	};
	/*!
	 *@brief	�X�P���g���B
	 */
	class CSkeleton : Noncopyable{
	public:
		CSkeleton();
		~CSkeleton();
		/*!
		*@brief	�{�[����ǉ��B
		*@param[in]	boneName		�{�[���̖��O�B
		*@param[in]	bindPose		�o�C���h�|�[�Y�̍s��B
		*@param[in] invBindPose		�o�C���h�|�[�Y�̋t�s��B
		*@param[in] localMatrix		���[�J���s��B
		*/
		void AddBone(
			const wchar_t* boneName, 
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			const CMatrix& localMatrix
		);
	private:
		static const int BONE_MAX = 512;	//!<�{�[���̍ő吔�B
		typedef std::unique_ptr<CBone>	CBonePtr;
		std::vector<CBonePtr>	m_bones;	//!<�{�[���̔z��B
	};
}