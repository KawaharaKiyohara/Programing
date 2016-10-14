/*!
 *@brief	�G�̃p�����[�^�e�[�u���B
 */

#pragma once

/*!
 *@brief	�G�̃p�����[�^�B
 */
struct EnemyParam{
	const char* name;					//���O�B
	const char* bloodEffectBoneName;	//�����Ԃ��G�t�F�N�g��\������{�[���̖��O�B
	CVector3 bloodEffectOffsetPosition;	//�����Ԃ��G�t�F�N�g��\������I�t�Z�b�g���W�B
};
static const EnemyParam g_enemyParamTable[] = {
	//enemy00
	{
		"enemy_00",
		"Bip001_Neck",
	},
	//enemy00
	{
		"enemy_01",
		"spine",
	},
	//�f�t�H���g�B
	{
		"default",
		""
	},
};