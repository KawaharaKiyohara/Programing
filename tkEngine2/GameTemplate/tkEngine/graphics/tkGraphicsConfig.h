/*!
 * @brief	�O���t�B�b�N�X�R���t�B�O�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�G�b�W���o�����̃R���t�B�O
	 */
	struct SEdgeRenderConfig{
		bool isEnable;		//!<�G�b�W���o�������L�����ǂ����̃t���O�B
		int	idMapWidth;		//!<ID�}�b�v�̕��B
		int idMapHeight;	//!<ID�}�b�v�̍����B
	};
	
	/*!
	 * @brief	�e�����̃R���t�B�O�B
	 */
	struct SShadowRenderConfig{
		void Init()
		{
			isEnable = false;
			shadowMapWidth = 512;
			shadowMapHeight = 512;
			isEnableSoftShadow = false;
			nearPlane = TK_UNIT_M(10.0f);
			farPlane = TK_UNIT_M(100.0f);
			lightHeight = TK_UNIT_M(20.0f);
		}
		bool 	isEnable;				//!<�e�𗎂Ƃ��������L�����ǂ����̃t���O�B
		int		shadowMapWidth;			//!<�V���h�E�}�b�v�̕��B
		int		shadowMapHeight;		//!<�V���h�E�}�b�v�̍����B
		float	nearPlane;				//!<�ߕ��ʂ܂ł̋����B				
		float	farPlane;				//!<�����ʂ܂ł̋����B
		float	lightHeight;			//!<���C�g�̍����B
		bool	isEnableSoftShadow;		//!<�\�t�g�V���h�E���L�����ǂ����̃t���O�B
	};
	/*!
	* @brief	Bloom�̃R���t�B�O
	*/
	struct SBloomConfig {		
		bool	isEnable = false;		//!<�u���[�����L�����ǂ����̃t���O�B
	};
	/*!
	* @brief	���t���N�V�����}�b�v�̃R���t�B�O
	*/
	struct SReflectionMapConfig {
		bool	isEnable = false;				//!<���t���N�V�����}�b�v���L�����ǂ����̃t���O�B
		int		reflectionMapWidth;		//!<���t���N�V�����}�b�v�̕��B
		int		reflectionMapHeight;	//!<���t���N�V�����}�b�v�̍����B
	};
	/*!
	* @brief	��ʊE�[�x�̃R���t�B�O�B
	*/
	struct SDofConfig {
		bool isEnable = false;					//��ʊE�[�x���L�����ǂ����̃t���O�B
	};
	/*!
	* @brief	�A���`�G�C���A�X�̃R���t�B�O�B
	*/
	struct SAAConfig {
		bool isEnable = false;					//�A���`�G�C���A�X���L�����ǂ����̃t���O�B
	};
	/*!
	* @brief	���[�V�����u���[�̃R���t�B�O�B
	*/
	struct SMotionBlurConfig {
		bool isEnable = false;
	};
	/*!
	* @brief	�g�[���}�b�v�̃R���t�B�O�B
	*/
	struct STonemapConfig {
		void Init()
		{
			isEnable = false;
			luminance = 0.34f;
		}
		bool isEnable = false;
		float luminance = 0.34f;			//���邳�B�l���傫���قǖ��邭�Ȃ�܂��B
	};
	/*!
	* @brief	�f�B�U�����O�̃R���t�B�O�B
	*/
	struct SDitheringConfig {
		bool isEnable = false;
	};
	/*!
	 * @brief	�O���t�B�b�N�X�R���t�B�O�B
	 */
	struct SGraphicsConfig{
		SEdgeRenderConfig		edgeRenderConfig;		//!<�G�b�W���o�����̃R���t�B�O�B
		SShadowRenderConfig		shadowRenderConfig;		//!<�e�̏����̃R���t�B�O�B
		SBloomConfig			bloomConfig;			//!<Bloom�̃R���t�B�O�B
		SReflectionMapConfig	reflectionMapConfig;	//!<���t���N�V�����}�b�v�̃R���t�B�O�B
		SDofConfig				dofConfig;				//!<��ʊE�[�x�̃R���t�B�O�B
		SAAConfig				aaConfig;				//!<�A���`�G�C���A�X�̃R���t�B�O�B
		SMotionBlurConfig		motionBlurConfig;		//<!���[�V�����u���[�̃R���t�B�O�B
		STonemapConfig			tonemapConfig;			//!<�g�[���}�b�v�̃R���t�B�O�B
		SDitheringConfig		ditheringConfig;		//!<�f�B�U�����O�B
	};
}
