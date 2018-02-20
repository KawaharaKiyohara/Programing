/*!
 * @brief	�G�t�F�N�g�G���W���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/effect/tkEffectEngine.h"

namespace tkEngine {
	CEffectEngine::CEffectEngine()
	{
	}
	CEffectEngine::~CEffectEngine()
	{
		Release();
	}

	void CEffectEngine::Release()
	{
		if (m_manager != nullptr) {
			m_manager->Destroy();
			m_manager = nullptr;
		}
		if (m_renderer != nullptr) {
			m_renderer->Destroy();
			m_renderer = nullptr;
		}
	}
	void CEffectEngine::Init()
	{
		Release();
		//�����_���[���������B
		m_renderer = EffekseerRendererDX11::Renderer::Create(
			GraphicsEngine().GetD3DDevice(),
			GraphicsEngine().GetD3DDeviceContext(),
			2000);
		//�G�t�F�N�g�}�l�[�W�����������B
		m_manager = Effekseer::Manager::Create(2000);

		// �`��p�C���X�^���X����`��@�\��ݒ�
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());

		CGraphicsEngine& ge = GraphicsEngine();
		//�[�x�l�������ݗp�̃����_�����O�^�[�Q�b�g�̍쐬�B

		m_addEffectBuffer.Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,	//Z�o�b�t�@�͍��Ȃ��B
			ge.GetMainRenderTargetMSAADesc()
		);
		//Z�o�b�t�@�̓��C�������_�����O�^�[�Q�b�g�̂��̂��g�p����B
		m_addEffectBuffer.SetDepthStencilView(
			ge.GetMainRenderTarget().GetDepthStencilView()
		);

		m_renderFlags.resize(1024);
	}
	
	Effekseer::Effect* CEffectEngine::CreateEffekseerEffect(const wchar_t* filePath)
	{
		return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
	}
	Effekseer::Handle CEffectEngine::Play(Effekseer::Effect* effect )
	{
		return m_manager->Play(effect, 0, 0, 0);
	}
	void CEffectEngine::Stop(Effekseer::Handle handle)
	{
		m_manager->StopEffect(handle);
	}
	void CEffectEngine::Update()
	{
		//�J�����s���ݒ�B
		m_renderer->SetCameraMatrix(MainCamera().GetViewMatrix());
		m_renderer->SetProjectionMatrix(MainCamera().GetProjectionMatrix());

		m_manager->Update(GameTime().GetFrameDeltaTime() / (1.0f / 60.0f));
	}
	void CEffectEngine::Render(CRenderContext& rc, CPostEffect* ps)
	{
		BeginGPUEvent(L"enRenderStep_RenderEffect");
		//�����_�����O�X�e�b�v��3D���f���̕`��ɁB
		rc.SetRenderStep(enRenderStep_RenderEffect);

		//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v����B
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);

		using namespace Effekseer;
		auto nodeCount = 0;
		m_manager->QueryNode([&](EffectNode* node) {
			EffectBasicRenderParameter param = node->GetBasicRenderParameter();
			m_renderFlags[nodeCount] = node->GetRenderFlag();	//���X�̕`��t���O���o�b�N�A�b�v����B
			nodeCount++;
		});

		{
			//���Z���ȊO�͒ʏ탌���_�����O�B
			nodeCount = 0;
			m_manager->QueryNode([&](EffectNode* node) {
				EffectBasicRenderParameter param = node->GetBasicRenderParameter();
				if (param.AlphaBlend == AlphaBlendType::Add) {
					//���Z���͕`�悵�Ȃ��B
					node->SetRenderFlag(false);
				}
			});

			m_renderer->BeginRendering();
			m_manager->Draw();
			m_renderer->EndRendering();
		}
		{
			//�����ĉ��Z���B
			nodeCount = 0;
			m_manager->QueryNode([&](EffectNode* node) {
				EffectBasicRenderParameter param = node->GetBasicRenderParameter();
				if (param.AlphaBlend == AlphaBlendType::Add) {
					//���Z���̕`��t���O��߂��B
					node->SetRenderFlag(m_renderFlags[nodeCount]);
				}
				else {
					//���Z���ȊO�͕`�悵�Ȃ��B
					node->SetRenderFlag(false);
				}
				nodeCount++;
			});

			//���Z���̓I�t�X�N���[�������_�����O���s���āA��ō�������B
			CRenderTarget* renderTargets[] = {
				&m_addEffectBuffer
			};
			rc.OMSetRenderTargets(1, renderTargets);
			float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; //red,green,blue,alpha
			rc.ClearRenderTargetView(0, ClearColor, false);

			//�����_�����O�X�e�b�v��3D���f���̕`��ɁB

			rc.SetRenderStep(enRenderStep_RenderEffect);

			//���Z����`�悷��B
			m_renderer->BeginRendering();
			m_manager->Draw();
			m_renderer->EndRendering();

			//�����_�����O�^�[�Q�b�g�������߂��B
			rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
			//MSAA���]���u�B
			m_addEffectBuffer.ResovleMSAATexture(rc);
		}

		//�m�[�h�̕`��t���O��S���߂��B
		nodeCount = 0;
		m_manager->QueryNode([&](EffectNode* node) {
			node->SetRenderFlag(m_renderFlags[nodeCount]);
			nodeCount++;
		});


		EndGPUEvent();
	}
}