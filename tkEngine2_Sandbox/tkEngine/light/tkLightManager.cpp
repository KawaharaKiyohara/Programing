/*!
 * @brief	���C�g�̊Ǘ��ҁB
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/light/tkLightManager.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/graphics/prerender/tkLightCulling.h"

namespace tkEngine{
	using namespace prefab;
	CLightManager::CLightManager()
	{
	}
	CLightManager::~CLightManager()
	{
	}
	void CLightManager::Init()
	{
		InitDirectionLightStructuredBuffer();
		InitPointLightStructuredBuffer();
		InitPointLightInTileStructuredBuffer();
		SetAmbientLight({ 0.5f, 0.5f, 0.5f });
		m_lightParamCB.Create(&m_lightParam, sizeof(m_lightParam));
		
	}
	void CLightManager::InitPointLightInTileStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		//�^�C���̐�
		int numTile = (GraphicsEngine().GetFrameBufferWidth() / CLightCulling::TILE_WIDTH)
			* (GraphicsEngine().GetFrameBufferHeight() / CLightCulling::TILE_WIDTH);
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;	//SRV��UAV�Ƀo�C���h�\�B
		desc.ByteWidth = sizeof(unsigned int) * MAX_POINT_LIGHT * numTile;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(unsigned int);
		m_pointLightsInTileSB.Create(NULL, desc);
	}
	void CLightManager::InitDirectionLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SDirectionLight);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h�\�B
		desc.ByteWidth = stride * MAX_DIRECTION_LIGHT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_directionLightSB.Create(NULL, desc);
	}
	void CLightManager::InitPointLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SPointLight);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h�\�B
		desc.ByteWidth = stride * MAX_POINT_LIGHT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_pointLightsSB.Create(NULL, desc);
	}
	void CLightManager::AddLight(CLightBase* light)
	{
		if (m_pointLights.size() >= MAX_POINT_LIGHT) {
			TK_WARNING("m_pointLights.size() is full!!");
			return;
		}
		if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
			TK_WARNING("m_directionLights.size() is full!!");
			return;
		}
		//���C�g�̐U�蕪���B
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CPointLight)) {
			//�o�^�ς݂����ׂ�B
			auto findIt = std::find(m_pointLights.begin(), m_pointLights.end(), light);
			if (findIt == m_pointLights.end()) {
				//�V�K�o�^�B
				m_pointLights.push_back(reinterpret_cast<CPointLight*>(light));
			}
			else {
				//���ɓo�^����Ă��B
				TK_LOG("This light was already added");
				return;
			}
		}
		else if (typeInfo == typeid(prefab::CDirectionLight)) {
			//�o�^�ς݂����ׂ�B
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light);
			if (findIt == m_directionLights.end()) {
				//�V�K�o�^�B
				m_directionLights.push_back(reinterpret_cast<CDirectionLight*>(light));
			}
			else {
				//���ɓo�^����Ă��B
				TK_LOG("This light was already added");
				return;
			}
		}
		SetDirty();
	}
	void CLightManager::RemoveLight(CLightBase* light)
	{
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CPointLight)) {
			m_pointLights.erase(
				std::remove(m_pointLights.begin(), m_pointLights.end(), light), 
				m_pointLights.end()
			);
		}
		else if (typeInfo == typeid(CDirectionLight)) {
			m_directionLights.erase(
				std::remove(m_directionLights.begin(), m_directionLights.end(), light),
				m_directionLights.end()
			);
		}
		SetDirty();
	}
	void CLightManager::Update()
	{
		if (!m_isDirty) {
			//�X�V�̕K�v�Ȃ��B
			return;
		}
		//�f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@���X�V�B
		int ligNo = 0;
		for (auto lig : m_directionLights) {
			m_rawDirectionLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		ligNo = 0;
		for (auto lig : m_pointLights) {
			m_rawPointLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		//�_�[�e�B�t���O�͂����ł͂��낳���ɁARender�֐��ł��낷�B
		m_lightParam.eyePos = MainCamera().GetPosition();
		m_lightParam.numDirectionLight = m_directionLights.size();
		m_lightParam.numPointLight = m_pointLights.size();
	}
	void CLightManager::Render(CRenderContext& renderContext)
	{
		if (m_isDirty) {
			//StructuredBuffer���X�V����B
			renderContext.UpdateSubresource(m_directionLightSB, m_rawDirectionLights);
			renderContext.UpdateSubresource(m_pointLightsSB, m_rawPointLights);
			//�_�[�e�B�t���O�������B
			m_isDirty = false;
		}
		renderContext.UpdateSubresource(m_lightParamCB, &m_lightParam);
		//PS�X�e�[�W��t���W�X�^��100�ԖڂɃf�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@��ݒ肷��B
		renderContext.PSSetShaderResource(100, m_directionLightSB.GetSRV());
		//PS�X�e�[�W��t���W�X�^��101�ԖڂɃ|�C���g���C�g�̃X�g���N�`���[�o�b�t�@��ݒ肷��B
		renderContext.PSSetShaderResource(101, m_pointLightsSB.GetSRV());
		//PS�X�e�[�W��t���W�X�^��102�ԖڂɃ^�C�����Ƃ̃|�C���g���C�g�̃C���f�b�N�X���X�g�̃X�g���N�`���[�o�b�t�@��ݒ肷��B
		renderContext.PSSetShaderResource(102, m_pointLightsInTileSB.GetSRV());
		//PS�X�e�[�W��c���W�X�^��1�ԖڂɃ��C�g�p�̒萔�o�b�t�@��ݒ肷��B
		renderContext.PSSetConstantBuffer(1, m_lightParamCB);
	}
	/*!
	*@brief�@�P�t���[���̕`��I�����ɌĂ΂�鏈���B
	*/
	void CLightManager::EndRender(CRenderContext& renderContext)
	{
		renderContext.PSUnsetShaderResource(100);
		renderContext.PSUnsetShaderResource(101);
		renderContext.PSUnsetShaderResource(102);
	}
}