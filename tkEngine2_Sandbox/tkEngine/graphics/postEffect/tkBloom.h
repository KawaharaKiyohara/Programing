/*!
 * @brief	�u���[��
 */
#pragma once

namespace tkEngine{
	class CPostEffect;
	/*!
	 * @brief	�u���[��
	 */
	class CBloom : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CBloom();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CBloom();
		/*!
		 * @brief	�J��
		 */
		void Release();
		/*!
		 * @brief	�������B
		 */
		void Init( const SGraphicsConfig& config );
		/*!
		 * @brief	�`��
		 */
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		static const int NUM_WEIGHTS = 8;
		static const int NUM_DOWN_SAMPLING_RT = 10;
		bool m_isEnable = false;		//!<�L���B
		CRenderTarget m_luminanceRT;	//!<�P�x�𒊏o���郌���_�����O�^�[�Q�b�g�B
		CRenderTarget m_combineRT;		//!<�ڂ��������p�̃����_�����O�^�[�Q�b�g�B
		CRenderTarget m_downSamplingRT[NUM_DOWN_SAMPLING_RT];	//!<�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
		float m_weights[NUM_WEIGHTS];	//!<�d�݃e�[�u���B
	};
}