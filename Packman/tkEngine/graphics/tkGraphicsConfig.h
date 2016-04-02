/*!
 * @brief	�O���t�B�b�N�X�R���t�B�O�B
 */

#ifndef _TKGRAPHICSCONFIG_H_
#define _TKGRAPHICSCONFIG_H_

namespace tkEngine{
	/*!
	 * @brief	�G�b�W���o�����̃R���t�B�O
	 */
	struct SEdgeRenderConfig{
		bool isEnable;		//!<�G�b�W���o�������L�����ǂ����̃t���O�B
		u32	idMapWidth;		//!<ID�}�b�v�̕��B
		u32 idMapHeight;	//!<ID�}�b�v�̍����B
	};
	
	/*!
	 * @brief	�e�����̃R���t�B�O�B
	 */
	struct SShadowRenderConfig{
		bool 	isEnable;			//!<�e�𗎂Ƃ��������L�����ǂ����̃t���O�B
		u32		shadowMapWidth;		//!<�V���h�E�}�b�v�̕��B
		u32		shadowMapHeight;	//!<�V���h�E�}�b�v�̍����B
	};
	
	/*!
	 * @brief	�O���t�B�b�N�X�R���t�B�O�B
	 */
	struct SGraphicsConfig{
		SEdgeRenderConfig		edgeRenderConfig;		//!<�G�b�W���o�����̃R���t�B�O�B
		SShadowRenderConfig		shadowRenderConfig;		//!<�e�̏����̃R���t�B�O�B
	};
}

#endif //_TKGRAPHICSCONFIG_H_