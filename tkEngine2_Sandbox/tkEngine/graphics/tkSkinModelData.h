/*!
 *@brief	�X�L�����f���f�[�^�B
 */

#pragma once

#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine{
	class CAnimationClip;
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
	/*!
	*@brief	���f���G�t�F�N�g�B
	*/
	class CModelEffect : public DirectX::IEffect {
	protected:
		std::wstring m_materialName;	//!<�}�e���A�����B
		CShader m_vsShader;
		CShader m_psShader;
		CShader m_vsRenderToDepthShader;	//!<Z�l�������ݗp�̒��_�V�F�[�_�[�B
		CShader m_psRenderToDepthShader;	//!<Z�l�������ݗp�̃s�N�Z���V�F�[�_�[�B
		ID3D11ShaderResourceView* m_diffuseTex = nullptr;
		ID3D11ShaderResourceView* m_normalMap = nullptr;
		ID3D11ShaderResourceView* m_specularMap = nullptr;
		bool isSkining;
		/*!
		* @brief	�}�e���A���p�����[�^�B
		* @details 
		* ������ύX����ꍇ�́AmodelCB.h��MaterialParamCb���ύX����悤�ɁB
		*/
		struct MaterialParam {
			int hasNormalMap;		//!<�@���}�b�v����H
			int hasSpecularMap;		//!<�X�y�L�����}�b�v����H
			float anisotropic;		//!<�ٕ������ˁB
		};
		static const int NUM_POINT_LIGHT = 1024;
		MaterialParam m_materialParam;				//�}�e���A���p�����[�^�B
		CConstantBuffer m_materialParamCB;			//�}�e���A���p�����[�^�p�̒萔�o�b�t�@�B
		CRenderContext* m_renderContext = nullptr;	//�����_�����O�R���e�L�X�g�B
	public:
		CModelEffect()
		{
			m_materialParam.anisotropic = 0.5f;
			m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
			m_psShader.Load("Assets/shader/model.fx", "PSMain", CShader::EnType::PS);
			m_psRenderToDepthShader.Load("Assets/shader/model.fx", "PSMain_RenderDepth", CShader::EnType::PS);
		}
		void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;
		
		void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
		{
			*pShaderByteCode = m_vsShader.GetByteCode();
			*pByteCodeLength = m_vsShader.GetByteCodeSize();
		}
		void SetDiffuseTexture(ID3D11ShaderResourceView* tex)
		{
			m_diffuseTex = tex;
		}
		void SetNormalMap(ID3D11ShaderResourceView* tex)
		{
			m_normalMap = tex;
		}
		void SetSpecularMap(ID3D11ShaderResourceView* tex)
		{
			m_specularMap = tex;
		}
		void SetMatrialName(const wchar_t* matName)
		{
			m_materialName = matName;
		}
		void SetRenderContext(CRenderContext& rc)
		{
			m_renderContext = &rc;
		}
		bool EqualMaterialName(const wchar_t* name) const
		{
			return wcscmp(name, m_materialName.c_str()) == 0;
		}
	};
	/*!
	*@brief
	*  �X�L���Ȃ����f���G�t�F�N�g�B
	*/
	class CNonSkinModelEffect : public CModelEffect {
	public:
		CNonSkinModelEffect()
		{
			m_vsShader.Load("Assets/shader/model.fx", "VSMain", CShader::EnType::VS);
			m_vsRenderToDepthShader.Load("Assets/shader/model.fx", "VSMain_RenderDepth", CShader::EnType::VS);
			isSkining = false;
		}
	};
	/*!
	*@brief
	*  �X�L�����f���G�t�F�N�g�B
	*/
	class CSkinModelEffect : public CModelEffect {
	public:
		CSkinModelEffect()
		{
			m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", CShader::EnType::VS);
			m_vsRenderToDepthShader.Load("Assets/shader/model.fx", "VSMainSkin_RenderDepth", CShader::EnType::VS);
			isSkining = true;
		}
	};

	/*!
	 *@brief	�X�L�����f���f�[�^�B
	 */
	class CSkinModelData : Noncopyable{
	public:
		
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSkinModelData();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CSkinModelData();
		/*!
		 *@brief	���[�h�B
		 *@param[in]	filePath	�t�@�C���p�X�B
		 *@return	true���Ԃ��Ă����烍�[�h�����B
		 */
		bool Load( const wchar_t* filePath );
		DirectX::Model& GetBody()
		{
			return *m_modelDx;
		}
		/*!
		 *@brief	�X�P���g�����擾�B
		 */
		CSkeleton& GetSkeleton()
		{
			return m_skeleton;
		}
		typedef std::function<void(std::unique_ptr<DirectX::ModelMeshPart>&)>		OnFindMesh;
		typedef std::function<void(CModelEffect*)>	OnFindModelEffect;
		/*!
		 *@brief	���b�V���̌����B
		 *@param[in]	findMesh		���b�V�������������ɌĂ΂��R�[���o�b�N�֐�
		 */
		void FindMesh(OnFindMesh findMesh);
	private:
		
		std::unique_ptr<DirectX::Model> m_modelDx;
		CSkeleton	m_skeleton;
	};
}