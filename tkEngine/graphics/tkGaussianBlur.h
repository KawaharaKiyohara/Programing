/*!
 * @brief	�K�E�V�A���u���[�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�K�E�V�A���u���[�B
	 */
	class CGaussianBlur{
	public:
		CGaussianBlur();
		~CGaussianBlur();
		void Init( int w, int h, const CTexture& srcTexture );
		void Draw(CRenderContext& renderContext);
		const CTexture* GetTexture() const
		{
			return m_rt[1].GetTexture();
		}

		void SetDispersion(float dispersion)
		{
			m_dispersion = dispersion;
			UpdateWeight();
		}
	private:
		/*!
		* @brief	�K�E�X�t�B���^�̏d�݂��X�V�B
		*/
		void UpdateWeight();
	private:
		static const int NUM_WEIGHTS = 8;
		float				m_weights[NUM_WEIGHTS];
		CRenderTarget		m_rt[2];			//!<�K�E�V�A���u���[�̌��ʂ�`�����ރ����_�����O�^�[�Q�b�g�B
		const CTexture*		m_srcTexture;		//!<�\�[�X�ƂȂ�e�N�X�`���B
		CPrimitive			m_prim;				//!<�v���~�e�B�u�B
		CEffect*			m_effect;			//!<�G�t�F�N�g�B
		int					m_srcTexWH[2];
		float				m_dispersion;		//!<
	};
}