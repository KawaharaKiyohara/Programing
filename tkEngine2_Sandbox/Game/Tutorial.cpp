/*!
 *@brief	PBR�T���v���B
 */
#include "stdafx.h"
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/timer/tkStopwatch.h"
#include <time.h>

using namespace tkEngine;



class PBRSample : public IGameObject {
	//�}�e���A���p�����[�^�̐��B
	static const int NUM_MATERIAL_PARAM = 3;
	//���_�B
	struct SSimpleVertex {
		CVector4 pos;
		CVector2 tex;
	};

	//���C�g�\���́B
	struct SLight {
		CVector4 diffuseLightDir;		//�f�B�t���[�Y���C�g�̕����B
		CVector4 diffuseLightColor;		//�f�B�t���[�Y���C�g�̐F�B
		CVector4 ambientLight;			//�A���r�G���g���C�g�B
		CVector4 eyePos;				//�����̈ʒu�B
	};
	
	/*!
	 * @brief	�}�e���A���p�����[�^�B
	 */
	struct MaterialParam{
		float roughness;		//!<�e��
		float metallic;			//!<���^���b�N�B
		float anisotropic;		//!<�ٕ������ˁB
	};
	
	SLight m_light;								//���C�g�B
	CConstantBuffer m_lightCB;					//���C�g�p�̒萔�o�b�t�@�B
	MaterialParam m_materialParam;				//�}�e���A���p�����[�^�B
	CConstantBuffer m_materialParamCB;			//�}�e���A���p�����[�^�p�̒萔�o�b�t�@�B
	CSkinModelData skinModelData;
	CSkinModel bgModel;
	std::unique_ptr<DirectX::SpriteFont>	m_font;
	std::unique_ptr<DirectX::SpriteBatch>	m_bach;
	int m_cursorPos = 0;
public:

	bool Start() override
	{
		skinModelData.Load(L"Assets/modelData/background.cmo");
		bgModel.Init(skinModelData);
		//�J�������������B
		CCamera& mainCamera = MainCamera();
		mainCamera.SetPosition({ 0.0f, 40.0f, 50.0f });
		mainCamera.SetTarget({ 0.0f, 0.0f, 0.0f });
		mainCamera.SetUp({ 0.0f, 1.0f, 0.0f });
		mainCamera.Update();
		

		//���C�g�̒萔�o�b�t�@���쐬�B
		m_light.diffuseLightDir.Set({ 1.0f, 0.0f, 0.0f, 0.0f });
		m_light.diffuseLightColor.Set({ 1.0f, 1.0f, 1.0f, 1.0f });
		m_light.eyePos = mainCamera.GetPosition();
		m_lightCB.Create(&m_light, sizeof(m_light));
		
		//�}�e���A���p�����[�^���������B
		m_materialParam.roughness = 0.5f;
		m_materialParam.metallic = 0.5f;
		m_materialParam.anisotropic = 0.5f;
		m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
			
		//�t�H���g���������B
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"Assets/font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));
		return true;
	}
	void Update() override
	{
		bgModel.Update({0.5f, 0.0f, 0.0f}, CQuaternion::Identity, CVector3::One);
		//�}�e���A���p���[���[�^���X�V�B
		if (Pad(0).IsTrigger(enButtonUp)) {
			m_cursorPos--;
		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			m_cursorPos++;
		}
		
		m_cursorPos = min(NUM_MATERIAL_PARAM-1, m_cursorPos);
		m_cursorPos = max(0, m_cursorPos);

		float* params[] = {
			&m_materialParam.roughness,
			&m_materialParam.metallic,
			&m_materialParam.anisotropic
		};
		if (Pad(0).IsPress(enButtonLeft)) {
			*params[m_cursorPos] += 0.001f;
		}
		else if (Pad(0).IsPress(enButtonRight)) {
			*params[m_cursorPos] -= 0.001f;
		}
		*params[m_cursorPos] = max(*params[m_cursorPos], 0.0f);
		*params[m_cursorPos] = min(*params[m_cursorPos], 1.0f);
	}
	/*!------------------------------------------------------------------
	* @brief	�V�[���̕`��B
	------------------------------------------------------------------*/
	void RenderScene(CRenderContext& rc)
	{	
		rc.UpdateSubresource(m_materialParamCB, m_materialParam);
		rc.PSSetConstantBuffer(1, m_lightCB);
		rc.PSSetConstantBuffer(2, m_materialParamCB);
		bgModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
	
	/*!------------------------------------------------------------------
	* @brief	�}�e���A���p�����[�^��\���B
	------------------------------------------------------------------*/
	void RenderMaterialParam(CRenderContext& rc)
	{
		wchar_t fps[256];
		wchar_t cursor[NUM_MATERIAL_PARAM] = { L' ', L' ', L' ' };
		cursor[m_cursorPos] = L'>';
		wchar_t* fomat = L"%croughness %f\n"
						  "%cmetallic %f\n"
						  "%canisotropic %f\n";
		swprintf_s(fps, fomat, 
			cursor[0], m_materialParam.roughness, 
			cursor[1], m_materialParam.metallic,
			cursor[2], m_materialParam.anisotropic
		);
		CRenderTarget* rts[] = {
			&GraphicsEngine().GetMainRenderTarget()
		};
		rc.OMSetRenderTargets(1, rts);
		m_bach->Begin();

		m_font->DrawString(
			m_bach.get(),
			fps,
			DirectX::XMFLOAT2(0, 0),
			DirectX::Colors::White,
			0,
			DirectX::XMFLOAT2(0, 0),
			3.0f
		);
		m_bach->End();
	}
	/*!------------------------------------------------------------------
	* @brief	�`��B
	------------------------------------------------------------------*/
	void Render(CRenderContext& rc) override
	{
		//�V�[���̕`��B
		RenderScene(rc);
		//�}�e���A���p���[���[�^��\���B
		RenderMaterialParam(rc);
	}
};

/*!
 *@brief	���C���֐��B
 */
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
	srand((unsigned)time(NULL));
    //tkEngine2�̏������p�����[�^��ݒ肷��B
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	//�G���W�����������B
	if (Engine().Init(initParam) == true) {
		//�������ɐ����B
		NewGO<PBRSample>(0);
		//�Q�[�����[�v�����s�B
		Engine().RunGameLoop();
	}
	//�G���W���̏I�������B
	Engine().Final();
	
    return 0;
}

