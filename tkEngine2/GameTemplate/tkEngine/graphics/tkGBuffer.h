/*!
 *@brief	G-Buffer
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	G-Buffer
	 *@details
	 * �f�B�t�@�[�h�n�̃����_�����O�G���W���Ŏg�p�����A
	 * G-Buffer�Ɠ������e�ł͂��邪�AtkEngine2�̃����_�����O��Forward+�Ȃ̂�
	 * ��Ƀ|�X�g�G�t�F�N�g�Ŏg�p�����B
	 * ����G-Buffer�̓��f���`��p�X��MRT�𗘗p���ďo�͂���Ă��܂��B
	 * �܂��A�[�x�e�N�X�`���ɂ��Ă�ZPrepass�ō쐬����Ă��邽�߁A���̃N���X�͕ێ����Ă��Ȃ��B
	 */
	class CGBuffer : Noncopyable{
	public:
		enum EnGBuffer{
			enGBufferNormal,	//!<�@���B
			enGBufferNum,		//!<G-Buffer�̐��B
		};
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CGBuffer();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CGBuffer();
		void Init();
		/*!
		 *@brief	G-Buffer���擾�B
		 *@param[in]	eGBuffer	�擾������G-Buffer���w�肷��B
		 */
		const CRenderTarget& GetGBuffer(EnGBuffer eGBuffer) const
		{
			/*if(eGBuffer >=enGBufferNum){
				return ;
			}*/
			return m_GBuffer[eGBuffer];
		}
	private:
		
		CRenderTarget m_GBuffer[enGBufferNum];	//!<G-Buffer
	};
}