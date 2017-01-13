/*!
 * @brief	�J�[�h�B
 */

#pragma once

#include "Common/CardConst.h"

class Card : public IGameObject{
public:
	Card();
	~Card();
	/*!
	 * @brief	�������B
	 *@param[in]	type	�J�[�h�̎�ށBEnCardType�Q�ƁB
	 *@param[in]	no		�J�[�h�̔ԍ��B1�`13�̐������w�肳��Ă���B
	 */
	void Init(EnCardType type, int no);
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext);
	/*!
	* @brief	�J�[�h�̃T�C�Y���擾�B
	*/
	static const CVector2& GetSize() 
	{
		static const CVector2 size(96.0f, 144.0f);
		return size;
	}
	/*!
	* @brief	���W�̎擾�B
	*/
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	* @brief	���W�̐ݒ�B
	*/
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
	/*!
	* @brief	��]��ݒ�B
	*/
	void SetRotation(const CQuaternion& rotation)
	{
		this->rotation = rotation;
	}
	/*!
	* @brief	�J�[�h�ԍ����擾�B
	*/
	int GetNo() const
	{
		return no;
	}
	/*!
	* @brief	���C�g��ݒ�B
	*/
	void SetLight(CLight& light)
	{
		model.SetLight(&light);
	}
private:
	/*!
	 * @brief	�������X�e�b�v�B
	 */
	enum EnInitStep{
		enInitStep_StartModelLoad,	//!<���f���̓ǂݍ��݊J�n�X�e�b�v�B
		enInitStep_WaitModelLoad,	//!<���f���̓ǂݍ��ݑ҂��X�e�b�v�B
	};
	CTexture* 				texture;			//!<�e�N�X�`���B
	CSkinModelData			modelData;			//!<���f���f�[�^�B
	CSkinModel				model;				//!<�X�L�����f���B
	EnCardType				type;				//!<�J�[�h�̎�ށB
	int						no;					//!<�J�[�h�i���o�[�B
	CVector3				position = CVector3::Zero;			//!<���W�B
	CQuaternion				rotation = CQuaternion::Identity;	//!<��]�B
	EnInitStep				initStep = enInitStep_StartModelLoad;
	float					angle = 0;			//!<��]�p�x�B�P�ʃ��W�A���B
};