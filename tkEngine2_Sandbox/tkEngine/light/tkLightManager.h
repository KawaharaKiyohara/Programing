/*!
 * @brief	���C�g�̊Ǘ��ҁB
 */

#pragma once
#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	namespace prefab {
		class CDirectionLight;
		class CPointLight;
		class CLightBase;
	}
	/*!
	 * @brief	���C�g�̊Ǘ���
	 * @details
	 *  �C���X�^���X�����ꂽCLightBase�̃C���X�^���X�͂��ׂ�CLightManager�ɓo�^����܂��B
	 *  ���̃N���X�̃C���X�^���X��CGraphicsEngine�N���X�݂̂��ێ����Ă���A���̑��̃N���X�ŃC���X�^���X�𐶐����邱�Ƃ͂ł��܂���B
	 */
	class CLightManager{
	friend class CGraphicsEngine;
	private:
		CLightManager();
		~CLightManager();
	public:
		void Init();
		/*!
		*@brief�@���C�g��ǉ��B
		*/
		void AddLight(prefab::CLightBase* light);
		/*!
		*@brief�@���C�g���폜�B
		*/
		void RemoveLight(prefab::CLightBase* light);
		/*!
		*@brief�@�X�V�B
		*/
		void Update();
		/*!
		*@brief�@�`��V�[�P���X����Ă΂�鏈���B
		* �X�g���N�`���[�o�b�t�@�̍X�V��A���I���C�g�̃V�F�[�_�[���\�[�X��ݒ肷��B
		*/
		void Render(CRenderContext& renderContext);
		/*!
		*@brief�@�_�[�e�B�t���O�𗧂Ă�B
		*/
		void SetDirty()
		{
			m_isDirty = true;
		}
	private:
		void InitDirectionLightStructuredBuffer();
		void InitPointLightStructuredBuffer();
		void InitLightParamConstantBuffer();
	private:
		static const int MAX_DIRECTION_LIGHT = 8;						//!<�f�B���N�V�������C�g�̍ő吔�B
		static const int MAX_POINT_LIGHT = 1024;						//!<�|�C���g���C�g�̍ő吔�B
		//GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�B
		struct SLightParam {
			CVector3 eyePos;			//�����̈ʒu�B
		};
		SLightParam							m_lightParam;
		CConstantBuffer						m_lightParamCB;			//!<GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�̒萔�o�b�t�@�B
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];
		SPointLight							m_rawPointLights[MAX_POINT_LIGHT];
		std::list<prefab::CDirectionLight*>	m_directionLights;		//!<���s�����̃��X�g�B
		CStructuredBuffer					m_directionLightSB;		//!<���s�����̃��X�g�̃X�g���N�`���[�o�b�t�@�B
		std::list<prefab::CPointLight*>		m_pointLights;			//!<�|�C���g���C�g�̃��X�g�B
		CStructuredBuffer					m_pointLightsSB;		//!<�|�C���g���C�g�̃��X�g�̃X�g���N�`���[�o�b�t�@�B
		bool								m_isDirty = false;		//!<�_�[�e�B�t���O�B
	};
}