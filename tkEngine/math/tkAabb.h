/*!
 *@brief	AABB
 */

#pragma once


namespace tkEngine{
	/*!
	 *@brief	AABB
	 *@details
	 *	軸平行バウンディングボックスクラス。</br>
	 *  メンバにバウンディングボックスの中心位置、</br>
	 *  サイズ、バウンディングボックスを構成する8頂点の座標を保持しています。
	 */
	class CAabb{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CAabb();
		/*!
		 *@brief	初期化。
		 */
		void Init(const CVector3& centerPosition, const CVector3& halfSize);
		/*!
		 *@brief	更新。
		 *@param[in]	centerPosition		中心座標。
		 *@param[in]	halfSize			バウンディングボックスのハーフサイズ。
		 */
		void Update( const CVector3& centerPosition, const CVector3& halfSize );
	private:
		CVector3	m_centerPosition;		//!<中心座標。
		CVector3	m_halfSize;				//!<ハーフサイズ。
		CVector3	m_vertexPosition[8];	//!<バウンディングボックスを構成する8頂点の座標。
	};
}