/*!
 *@brief	PBR�T���v���B
 */
#include "stdafx.h"
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/timer/tkStopwatch.h"
#include <time.h>
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/physics/tkMeshCollider.h"

using namespace tkEngine;



class PBRSample : public IGameObject {
	//�}�e���A���p�����[�^�̐��B
	static const int NUM_MATERIAL_PARAM = 3;
	//���_�B
	struct SSimpleVertex {
		CVector4 pos;
		CVector2 tex;
	};
	/*!
	 * @brief	�}�e���A���p�����[�^�B
	 */
	struct MaterialParam{
		float roughness;		//!<�e��
		float metallic;			//!<���^���b�N�B
		float anisotropic;		//!<�ٕ������ˁB
	};
	static const int NUM_POINT_LIGHT = 1024;
	MaterialParam m_materialParam;				//�}�e���A���p�����[�^�B
	CConstantBuffer m_materialParamCB;			//�}�e���A���p�����[�^�p�̒萔�o�b�t�@�B
	
	
	
	CSkinModelData skinModelData;
	CSkinModel skinModel;
	CAnimationClip animClip;
	CAnimation animation;
	prefab::CDirectionLight* m_directionLight[3] = { nullptr };
	prefab::CPointLight* m_pointLight[NUM_POINT_LIGHT] = {nullptr};
	
	std::unique_ptr<DirectX::SpriteFont>	m_font;
	std::unique_ptr<DirectX::SpriteBatch>	m_bach;
	int m_cursorPos = 0;
public:

	bool Start() override
	{
		
		
		skinModelData.Load(L"Assets/modelData/skinTest");
		skinModel.Init(skinModelData);
		//�A�j���[�V�����N���b�v�̃��[�h�B
		animClip.Load(L"Assets/animData/test.tka", L"Test");
		animClip.SetLoopFlag(true);
		CAnimationClip* animClipList[] = {
			&animClip
		};
		animation.Init(skinModelData, animClipList, 1);

		//�J�������������B
		CCamera& mainCamera = MainCamera();
		mainCamera.SetPosition({ 0.0f, 15.0f, -200.0f });
		mainCamera.SetTarget({ 0.0f, 15.0f, 0.0f });
		mainCamera.SetUp({ 0.0f, 1.0f, 0.0f });
		mainCamera.SetNear(0.1f);
		mainCamera.Update();
		
		//�f�B���N�V�������C�g���V�[���ɒǉ��B
		m_directionLight[0] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[0]->SetDirection({ 1.0f, 0.0f, 0.0f});
		m_directionLight[0]->SetColor({ 1.0f, 1.0f, 1.0f });

		//�}�e���A���p�����[�^���������B
		m_materialParam.roughness = 0.5f;
		m_materialParam.metallic = 0.5f;
		m_materialParam.anisotropic = 0.5f;
		m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
			
		//�t�H���g���������B
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"Assets/font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));

		// �|�C���g���C�g���������B
		static const int QuantizationSize = 1000;	//�ʎq���T�C�Y�B
		
		{
			for (int i = 0; i < 256; i++) {
				m_pointLight[i] = NewGO<prefab::CPointLight>(0);
				int ix = rand() % QuantizationSize;
				int iy = rand() % QuantizationSize;
				int iz = rand() % QuantizationSize;

				//0�`999�܂ł̐�����0.0�`1.0�͈̔͂ɕϊ�����B
				float fnx = (float)ix / QuantizationSize;
				float fny = (float)iy / QuantizationSize;
				float fnz = (float)iz / QuantizationSize;
				//x��y��-1.0�`1.0�͈̔͂ɕϊ�����B
				fnx = (fnx - 0.5f) * 2.0f;
				fnz = (fnz - 0.5f) * 2.0f;
				//�|�C���g���C�g�̈ʒu�������_���Ɍ���B
				m_pointLight[i]->SetPosition({ 50.0f * fnx , 5.0f * fny,  50.0f * fnz });

				int ir = rand() % QuantizationSize;
				int ig = rand() % QuantizationSize;
				int ib = rand() % QuantizationSize;

				//0�`999�܂ł̐�����0.0�`1.0�͈̔͂ɐ��K�����āA�|�C���g���C�g�̃J���[�������_���Ɍ���B
				m_pointLight[i]->SetColor({ 
					(float)ir / QuantizationSize , 
					(float)ig / QuantizationSize,
					(float)ib / QuantizationSize
				});
				
				m_pointLight[i]->SetAttn({
					5.0f,
					0.01f,
					0.01f
				});
				
			}
			m_pointLight[0]->SetPosition({0.0f, 10.0f, 0.0f});
		}
		return true;
	}
	void Update() override
	{
		//nonSkinModel.Update({0.0f, 0.0f, 0.0f}, CQuaternion::Identity, CVector3::One);
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisX,CMath::PI * -0.5f);
		skinModel.Update({ 0.0f, 0.0f, 0.0f }, qRot, CVector3::One);
		animation.Update(1.0f / 60.0f);
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

		//�_�������񂵂Ă݂�B
		qRot.SetRotationDeg(CVector3::AxisY, 0.2f);
		for (auto& ptLight : m_pointLight) {
			if (ptLight == NULL) {
				break;
			}
			CVector3 pointLightPos = ptLight->GetPosition();
			qRot.Multiply(pointLightPos);
			ptLight->SetPosition(pointLightPos);
		}

	}
	/*!------------------------------------------------------------------
	* @brief	�V�[���̕`��B
	------------------------------------------------------------------*/
	void RenderScene(CRenderContext& rc)
	{	
		rc.UpdateSubresource(m_materialParamCB, &m_materialParam);
		rc.PSSetConstantBuffer(2, m_materialParamCB);
		//nonSkinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
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

