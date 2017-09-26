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
	prefab::CPointLight* m_pointLight[NUM_POINT_LIGHT] = {nullptr};
	
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
		m_directionLight[0]->SetColor({ 0.2f, 0.2f, 0.2f, 0.0f });

		m_directionLight[1] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[1]->SetDirection({ 0.0f, -0.707f, -0.707f });
		m_directionLight[1]->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		
		m_directionLight[2] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[2]->SetDirection({ 1.0f, 0.0f, 0.0f });
		m_directionLight[2]->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });

			
		//�t�H���g���������B
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"Assets/font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));

		// �|�C���g���C�g���������B
		static const int QuantizationSize = 1000;	//�ʎq���T�C�Y�B
		
		{
			for (int i = 0; i < 32; i++) {
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
				m_pointLight[i]->SetPosition({ 200.0f * fnx , 100.0f,  200.0f * fnz });

				int ir = rand() % QuantizationSize;
				int ig = rand() % QuantizationSize;
				int ib = rand() % QuantizationSize;

				//0�`999�܂ł̐�����0.0�`1.0�͈̔͂ɐ��K�����āA�|�C���g���C�g�̃J���[�������_���Ɍ���B
				m_pointLight[i]->SetColor({ 
					(float)ir / QuantizationSize * 1.0f, 
					(float)ig / QuantizationSize * 1.0f,
					(float)ib / QuantizationSize * 1.0f,
					1.0f
				});
				
				m_pointLight[i]->SetAttn({
					150.0f,
					0.1f,
					0.1f
				});
				
			}
			//m_pointLight[0]->SetPosition({0.0f, 10.0f, 0.0f});
		}
		LightManager().SetAmbientLight({0.05f, 0.05f, 0.05f});
		m_player = NewGO<Player>(0, "Player");
		NewGO<Background>(0);
		NewGO<GameCamera>(0, "GameCamera");
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


		//�_�������񂵂Ă݂�B
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY, 0.6f);
		
		for (auto& ptLight : m_pointLight) {
			if (ptLight) {
				CVector3 pos = ptLight->GetPosition();
				qRot.Multiply(pos);
				ptLight->SetPosition(pos);
			}
		}

	}
	/*!------------------------------------------------------------------
	* @brief	�V�[���̕`��B
	------------------------------------------------------------------*/
	void RenderScene(CRenderContext& rc)
	{	

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
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.isEnableSoftShadow = true;

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

