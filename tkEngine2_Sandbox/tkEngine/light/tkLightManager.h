/*!
 * @brief	���C�g�̊Ǘ��ҁB
 */

#pragma once

namespace tkEngine{
	class CDirectionLight;
	class CPointLight;
	class CLightBase;
	/*!
	 * @brief	���C�g�̊Ǘ���
	 * @details
	 *  �C���X�^���X�����ꂽCLightBase�̃C���X�^���X�͂��ׂ�CLightManager�ɓo�^����܂��B
	 *  ���̃N���X�̃C���X�^���X��CEngine�N���X�݂̂��ێ����Ă���A���̑��̃N���X�ŃC���X�^���X�𐶐����邱�Ƃ͂ł��܂���B
	 */
	class CLightManager{
	friend class CEngine;
	private:
		CLightManager();
		~CLightManager();
	public:
		void Init();
		void AddLight(CLightBase* light);
		void RemoveLight(CLightBase* light);
		void Update();
	private:
		
		std::list<CDirectionLight*>		m_directionLights;		//!<���s�����̃��X�g�B
		CStructuredBuffer				m_directionLightSB;		//!<���s�����̃��X�g�̃X�g���N�`���[�o�b�t�@�B
		CShaderResourceView				m_directionLightSRV;	//!<���s�����̃��X�g��SRV�B
		std::list<CPointLight*>			m_pointLights;			//!<�|�C���g���C�g�̃��X�g�B
		CStructuredBuffer				m_pointLightsSB;		//!<�|�C���g���C�g�̃��X�g�̃X�g���N�`���[�o�b�t�@�B
		CShaderResourceView				m_pointLightsSRV;		//!<�|�C���g���C�g�̃��X�g��SRV�B
	};
}