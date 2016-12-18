/*!
 * @brief	�G�l�~�[�}�l�[�W���B
 */

#pragma once


class Enemy;

/*!
 * @brief	�G����̃}�l�[�W���[�B
 *@details
 * Facade�p�^�[���B
 */
class EnemyManager : public IGameObject{
public:
	EnemyManager();
	~EnemyManager();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
	const std::vector<Enemy*>& GetEnemyList() const
	{
		return enemyList;
	}
private:
	std::vector<Enemy*>		enemyList;		//!<�G�l�~�[�̃��X�g�B
};