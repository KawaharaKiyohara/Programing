/*!
 *@brief	PBR�T���v���B
 */
#include "stdafx.h"


#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/timer/tkStopwatch.h"
#include <time.h>
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/physics/tkMeshCollider.h"
#include "Player.h"
#include "Background.h"
#include "GameCamera.h"

class PBRSample : public IGameObject {
	//�}�e���A���p�����[�^�̐��B
	static const int NUM_MATERIAL_PARAM = 3;
	//���_�B
	struct SSimpleVertex {
		CVector4 pos;
		CVector2 tex;
	};
	
	static const int NUM_POINT_LIGHT = 1024;	
	
	
	prefab::CDirectionLight* m_directionLight[3] = { nullptr };
	std::vector<prefab::CPointLight*> m_pointLight;
	
	std::unique_ptr<DirectX::SpriteFont>	m_font;
	std::unique_ptr<DirectX::SpriteBatch>	m_bach;
	int m_cursorPos = 0;
	Player*		m_player;
	CSkeleton	m_ligLoc;
public:

	bool Start() override
	{
		CMatrix mRot;
		mRot.MakeRotationY(0.785f);
		CVector3 right = CVector3::Right;
		mRot.Mul(right);
		
		
		//�f�B���N�V�������C�g���V�[���ɒǉ��B
		m_directionLight[0] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[0]->SetDirection({ 0.707f, -0.707f, 0.0f});
		m_directionLight[0]->SetColor({0.1f, 0.1f, 0.1f, 1.0f });

	/*	m_directionLight[1] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[1]->SetDirection({ 0.0f, -0.707f, -0.707f });
		m_directionLight[1]->SetColor({ 1.2f, 1.2f, 1.2f, 1.0f });
		
		m_directionLight[2] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[2]->SetDirection({ 1.0f, 0.0f, 0.0f });
		m_directionLight[2]->SetColor({ 1.2f, 1.2f, 1.2f, 1.0f });
		*/
		
		//�t�H���g���������B
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"Assets/font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));

		// �|�C���g���C�g���������B
		static const int QuantizationSize = 1000;	//�ʎq���T�C�Y�B
		m_ligLoc.Load(L"Assets/lig/pointLightLoc.tks");
		for (int i = 1; i < m_ligLoc.GetNumBones(); i++) {
			CBone* bone = m_ligLoc.GetBone(i);
			prefab::CPointLight* ptLig = NewGO<prefab::CPointLight>(0);
			const CMatrix& mat = bone->GetBindPoseMatrix();
			CVector3 pos;
			pos.x = mat.m[3][0];
			pos.y = mat.m[3][2] * 0.354;
			pos.z = -mat.m[3][1];
			ptLig->SetPosition(pos);
			ptLig->SetColor({
				2000.0f,
				1000.0f,
				200.0f,
				1.0f
			});
			ptLig->SetAttn({
				150.0f,
				3.0f,
				0.1f
			});
			m_pointLight.push_back(ptLig);
		}
		LightManager().SetAmbientLight({0.1f, 0.1f, 0.1f});
		m_player = NewGO<Player>(0, "Player");
		NewGO<Background>(0);
		NewGO<GameCamera>(0, "GameCamera");
		GraphicsEngine().GetPostEffect().GetTonemap().SetLuminance(0.1f);
		return true;
	}
	void Update() override
	{
		//�}�e���A���p���[���[�^���X�V�B
		if (Pad(0).IsTrigger(enButtonUp)) {
			m_cursorPos--;
		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			m_cursorPos++;
		}
		
		m_cursorPos = min(NUM_MATERIAL_PARAM-1, m_cursorPos);
		m_cursorPos = max(0, m_cursorPos);


		//���C�g���񂷁B
		static CVector3 lightDir = {0.707, -0.707, 0.0f};
		/*qRot.SetRotationDeg(CVector3::AxisY, 1.0f);
		qRot.Multiply(lightDir);*/
		GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);

	}
	/*!------------------------------------------------------------------
	* @brief	�V�[���̕`��B
	------------------------------------------------------------------*/
	void RenderScene(CRenderContext& rc)
	{	
		(void)rc;
	}
	
	
	/*!------------------------------------------------------------------
	* @brief	�`��B
	------------------------------------------------------------------*/
	void Render(CRenderContext& rc) override
	{
		//�V�[���̕`��B
		RenderScene(rc);
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
	//�e�̐ݒ�B
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfing.shadowRenderConfig.isEnableSoftShadow = true;
	//�A���`
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;

	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);
	
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

