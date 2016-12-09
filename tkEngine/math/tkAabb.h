/*!
 *@brief	AABB
 */

#pragma once


namespace tkEngine{
	/*!
	 *@brief	AABB
	 *@details
	 *	�����s�o�E���f�B���O�{�b�N�X�N���X�B</br>
	 *  �����o�Ƀo�E���f�B���O�{�b�N�X�̒��S�ʒu�A</br>
	 *  �T�C�Y�A�o�E���f�B���O�{�b�N�X���\������8���_�̍��W��ێ����Ă��܂��B
	 */
	class CAabb{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CAabb();
		/*!
		 *@brief	�������B
		 */
		void Init(const CVector3& centerPosition, const CVector3& halfSize);
		/*!
		 *@brief	�X�V�B
		 *@param[in]	centerPosition		���S���W�B
		 *@param[in]	halfSize			�o�E���f�B���O�{�b�N�X�̃n�[�t�T�C�Y�B
		 */
		void Update( const CVector3& centerPosition, const CVector3& halfSize );
	private:
		CVector3	m_centerPosition;		//!<���S���W�B
		CVector3	m_halfSize;				//!<�n�[�t�T�C�Y�B
		CVector3	m_vertexPosition[8];	//!<�o�E���f�B���O�{�b�N�X���\������8���_�̍��W�B
	};
}