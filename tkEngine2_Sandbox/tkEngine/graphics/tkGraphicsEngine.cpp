/*!
 *@brief	�`��G���W���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkGraphicsEngine.h"

namespace tkEngine{
	CGraphicsEngine::CGraphicsEngine()
	{
	}
	CGraphicsEngine::~CGraphicsEngine()
	{
	}
	void CGraphicsEngine::Release()
	{

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		if (m_userAnnoation) {
			m_userAnnoation->Release();
			m_userAnnoation = nullptr;
		}
#endif
		if (m_backBufferRT) {
			m_backBufferRT->Release();
			m_backBufferRT = nullptr;
		}
		if (m_pImmediateContext) {
			m_pImmediateContext->ClearState();
			m_pImmediateContext = nullptr;
		}
		m_mainRenderTarget[0].Release();
		m_mainRenderTarget[1].Release();
		if (m_pSwapChain) {
			m_pSwapChain->Release();
			m_pSwapChain = nullptr;
		}
		if (m_pImmediateContext) {
			m_pImmediateContext->Release();
			m_pImmediateContext = nullptr;
		}
		if (m_pd3dDevice) {
			m_pd3dDevice->Release();
			m_pd3dDevice = nullptr;
		}
	}
	bool CGraphicsEngine::Init(HWND hwnd, const SInitParam& initParam)
	{
		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		m_frameBufferWidth = initParam.frameBufferWidth;
		m_frameBufferHeight = initParam.frameBufferHeight;
		//�X���b�v�`�F�C�����쐬�B
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;							//�X���b�v�`�F�C���̃o�b�t�@���B�ʏ�͂P�B
		sd.BufferDesc.Width = m_frameBufferWidth;	//�t���[���o�b�t�@�̕��B
		sd.BufferDesc.Height = m_frameBufferHeight;	//�t���[���o�b�t�@�̍����B
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�t���[���o�b�t�@�̃t�H�[�}�b�g�BR8G8B8A8��32bit�B
		sd.BufferDesc.RefreshRate.Numerator = 60;			//���j�^�̃��t���b�V�����[�g�B(�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���^�C�~���O�ƂȂ�B)
		sd.BufferDesc.RefreshRate.Denominator = 1;			//@todo �Ȃ��낱��H���Ԃ�Q�ɂ�����30fps�ɂȂ�B���ƂŎ����B
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�T�[�t�F�X�܂��̓��\�[�X���o�̓����_�[ �^�[�Q�b�g�Ƃ��Ďg�p���܂��B
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;							//�s�N�Z���P�ʂ̃}���`�T���v�����O�̐��BMSAA�͂Ȃ��B
		sd.SampleDesc.Quality = 0;							//MSAA�Ȃ��B
		sd.Windowed = TRUE;

		//���ׂẴh���C�o�^�C�v�ŃX���b�v�`�F�C���̍쐬�������B
		HRESULT hr = E_FAIL;
		for (auto driverType : driverTypes) {
			m_driverType = driverType;
			hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
			if (SUCCEEDED(hr)) {
				//�X���b�v�`�F�C�����쐬�ł����̂Ń��[�v�𔲂���B
				break;
			}
		}
		if (FAILED(hr)) {
			//�X���b�v�`�F�C�����쐬�ł��Ȃ������B
			return false;
		}

		//�������ݐ�ɂȂ郌���_�����O�^�[�Q�b�g���쐬�B
		ID3D11Texture2D* pBackBuffer = NULL;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_backBufferRT);
		if (FAILED(hr)) {
			return false;
		}
		DXGI_SAMPLE_DESC multiSampleDesc;
		ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		bool ret = m_mainRenderTarget[0].Create(
			m_frameBufferWidth,
			m_frameBufferHeight,
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			multiSampleDesc
		);
		ret = m_mainRenderTarget[1].Create(
			m_frameBufferWidth,
			m_frameBufferHeight,
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			multiSampleDesc
		);
		if (!ret) {
			return false;
		}
		//�����_�����O�R���e�L�X�g�̏������B
		m_renderContext.Init(m_pImmediateContext);
		CRenderTarget* renderTargets[] = {
			&m_mainRenderTarget[0]
		};
		m_renderContext.OMSetRenderTargets(1, renderTargets);
		//�r���[�|�[�g��ݒ�B
		m_renderContext.RSSetViewport(0.0f, 0.0f, (FLOAT)m_frameBufferWidth, (FLOAT)m_frameBufferHeight);
		//PreRender�̏������B
		m_preRender.Create(initParam.graphicsConfing);
		//PostEffect�̏������B
		m_postEffect.Create(initParam.graphicsConfing);
		//���C�g�Ǘ��҂̏������B
		m_lightManager.Init();

		//�R�s�[�p�̃V�F�[�_�[�����[�h�B
		m_copyVS.Load("Assets/shader/copy.fx", "VSMain", CShader::EnType::VS);
		m_copyPS.Load("Assets/shader/copy.fx", "PSMain", CShader::EnType::PS);

		
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		m_pImmediateContext->QueryInterface(__uuidof(ID3DUserDefinedAnnotation), (void**)&m_userAnnoation);
#endif
		return true;

	}
	void CGraphicsEngine::BeginRender()
	{
	}
	void CGraphicsEngine::EndRender()
	{
		m_lightManager.EndRender(m_renderContext);
		//�o�b�N�o�b�t�@�Ƀ��C�������_�����O�^�[�Q�b�g�̓��e���R�s�[�B
		ID3D11Texture2D* pBackBuffer = NULL;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		ID3D11RenderTargetView* rts[] = {
			m_backBufferRT 
		};
		m_pImmediateContext->OMSetRenderTargets(1, rts, nullptr);
		m_renderContext.VSSetShader(m_copyVS);
		m_renderContext.PSSetShader(m_copyPS);
		//���̓��C�A�E�g��ݒ�B
		m_renderContext.IASetInputLayout(m_copyVS.GetInputLayout());
		m_renderContext.PSSetShaderResource(0, m_mainRenderTarget[m_currentMainRenderTarget].GetRenderTargetSRV());
		//�|�X�g�G�t�F�N�g�̃t���X�N���[���`��̋@�\���g���B
		m_postEffect.DrawFullScreenQuad(m_renderContext);
		pBackBuffer->Release();
		m_renderContext.PSUnsetShaderResource(0);
		//�t���[�b�V��
		m_pSwapChain->Present(0, 0);
	}
}