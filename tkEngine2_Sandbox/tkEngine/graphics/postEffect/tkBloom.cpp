/*!
 * @brief	�u���[��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkBloom.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CBloom::CBloom()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CBloom::~CBloom()
	{
		Release();
	}
	/*!
	 * @brief	�J��
	 */
	void CBloom::Release()
	{
	}
	/*!
	 * @brief	�������B
	 */
	void CBloom::Init( const SGraphicsConfig& config )
	{
		Release();
		
		if(!config.bloomConfig.isEnable){
			return ;
		}
		m_isEnable = config.bloomConfig.isEnable;
		int w = Engine().GetGraphicsEngine().GetFrameBufferWidth();
		int h = Engine().GetGraphicsEngine().GetFrameBufferHeight();

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬�B
		DXGI_SAMPLE_DESC multiSampleDesc;
		ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		m_luminanceRT.Create(
			w, 
			h, 
			1, 
			1, 
			DXGI_FORMAT_R16G16B16A16_FLOAT, 
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);

	}
	/*!
	 * @brief	�`��
	 */
	void CBloom::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
	}
}