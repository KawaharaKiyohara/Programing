#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "Physics/SphereCollider.h"
#include "Physics/RigidBody.h"
#include "CharacterController.h"

/*!
 * @brief	ユニティちゃん
 */
class UnityChan : public IGameObject {
private:
	
	static const int NUM_BATTLE_SEAT = 8;		//シートの数。
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//立ち。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationJump,		//ジャンプ。
	};
public:
	//戦闘で使用するシート
	struct SBattleSeat {
		bool		isUse;			//使用中フラグ。
		int			seatNo;			//シート番号。
		CVector3	localPosition;	//ローカル座標。
		CVector3	position;		//ワールド座標。
	};
	enum EnState {
		enStateRun,			//走っている。
		enStateStand,		//立ち止まっている。
		enState_RideOnCar,	//車に乗っている
	};
	bool					isUpdateAnim;		//

	UnityChan() :
		position(CVector3::Zero),
		isUpdateAnim(false)
	{
		memset(battleSeats, 0, sizeof(battleSeats));
	}
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	* @brief	状態を取得。
	*/
	EnState GetState() const
	{
		return state;
	}
	/*!
	* @brief	ポイントライトの位置を取得。
	*/
	const CVector3& GetPointLightPosition() const
	{
		return pointLightPosition;
	}
	/*!
	* @brief	ポイントライトの色を取得。
	*/
	const CVector4& GetPointLightColor() const
	{
		return pointLightColor;
	}
	/*!
	* @brief	未使用のシートを検索。
	*@param[in]	pos		未使用のシートの中からこの座標に一番近いシートを返します。
	*@return		未使用のシートがない場合はNULLが返ってくる。
	*/
	SBattleSeat* FindUnuseSeat(const CVector3& pos) ;
private:
	/*!
	* @brief	ポイントライトの位置を更新。
	*/
	void UpdatePointLightPosition();
	/*!
	* @brief	アニメーションコントロール。
	*/
	void AnimationControl();
	/*!
	* @brief	アニメーション再生。
	*/
	void PlayAnimation(AnimationNo animNo);
	/*!
	* @brief	バトルで使用するシートを初期化。
	*/
	void InitBattleSeats();
	/*!
	* @brief	バトルで使用するシートを更新。
	*/
	void UpdateBattleSeats();
private:
	CSkinModelDataHandle	skinModelData;
	CSkinModel				skinModel;			//スキンモデル。
	CAnimation				animation;			//アニメーション。
	CLight					light;				//ライト。
	AnimationNo				currentAnimSetNo;
	CTexture				normalMap;			//法線マップ。
	CTexture				specMap;			//スペキュラマップ。
	CVector3				position;			//座標。
	CQuaternion				rotation;			//回転
	CVector3				toLightPos;			//
	CVector3				pointLightPosition;	//ポイントライトの位置。
	CVector4				pointLightColor;	//ポイントライトのカラー。
	CVector3				toLampLocalPos;		//ランプのローカル座標。
	EnState					state;				//状態。
	EnState					lastFrameState;		//前のフレームの状態。
	bool					isPointLightOn;		//ポイントライトのスイッチ。
	RigidBody				rigidBody;			//剛体。
	CharacterController		characterController;	//キャラクタコントローラ。
	SBattleSeat				battleSeats[NUM_BATTLE_SEAT];	//シート。

};