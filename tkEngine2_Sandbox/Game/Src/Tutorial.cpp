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
#include "Player/Player.h"
#include "Background.h"
#include "GameCamera.h"
#include "enemy\Enemy.h"
#include "tkEngine/graphics/2D/tkSprite.h"

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
		m_directionLight[0]->SetColor({100.5f, 100.5f, 100.5f, 1.0f });

		
		//�t�H���g���������B
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));

		// �|�C���g���C�g�̔z�u�������[�h�B
		CSkeleton ligLoc;
		ligLoc.Load(L"lig/pointLightLoc.tks");
		for (int i = 1; i < ligLoc.GetNumBones(); i++) {
			CBone* bone = ligLoc.GetBone(i);
			prefab::CPointLight* ptLig = NewGO<prefab::CPointLight>(0);
			const CMatrix& mat = bone->GetBindPoseMatrix();
			CVector3 pos;
			pos.x = mat.m[3][0];
			pos.y = mat.m[3][2];
			pos.z = -mat.m[3][1];
			ptLig->SetPosition(pos);
			ptLig->SetColor({
				3000.0f,
				2000.0f,
				1200.0f,
				1.0f
			});
			ptLig->SetAttn({
				150.0f,
				3.0f,
				0.1f
			});
			m_pointLight.push_back(ptLig);
		}
		//�G�̔z�u�������[�h�B
		CSkeleton enemyLoc;
		enemyLoc.Load(L"lig/enemyLoc.tks");
		for (int i = 1; i < enemyLoc.GetNumBones(); i++) {
			//�擪�̓_�~�[�B
			CBone* bone = enemyLoc.GetBone(i);
			Enemy* enemy = NewGO<Enemy>(0, "Enemey");
			const CMatrix& mat = bone->GetBindPoseMatrix();
			CVector3 pos;
			pos.x = mat.m[3][0];
			pos.y = mat.m[3][2];
			pos.z = -mat.m[3][1];
			enemy->SetPosition(pos);
		}
		LightManager().SetAmbientLight({5.5f, 5.5f, 5.5f});
		m_player = NewGO<Player>(0, "Player");
		NewGO<Background>(0);
		NewGO<GameCamera>(0, "GameCamera");
		GraphicsEngine().GetPostEffect().GetTonemap().SetLuminance(0.22f);
		
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

