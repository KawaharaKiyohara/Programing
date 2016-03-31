/*!
 *@brief	形状の基本クラス。
 */
#ifndef _TKSHAPEBASE_H_
#define _TKSHAPEBASE_H_

namespace tkEngine{
	/*!
	 *@brief	形状の基本クラス。
	 */
	class CShapeBase{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CShapeBase();
		/*!
		 *@brief	デストラクタ。
		 */
		virtual ~CShapeBase();
		/*!
		*@brief	ワールド行列の取得。
		*/
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	回転行列を取得。
		*/
		const CMatrix& GetRotationMatrix() const
		{
			return m_rotationMatrix;
		}
		/*!
		*@brief	座標を設定。
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/*!
		*@brief	回転を設定。
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		/*!
		*@brief	プリミティブを取得。
		*/
		CPrimitive* GetPrimitive()
		{
			return m_pPrimitive;
		}
		/*!
		 * @brief	リリース。
		 */
		void Release();
		/*!
		*@brief	更新
		*/
		void UpdateWorldMatrix();
		/*!
		*@brief	描画。
		*@param[in]	renderContext	レンダリングコンテキスト。
		*/
		void Render(CRenderContext& renderContext);
	protected:
		bool m_isCreatePrimitive;		//!<内部でプリミティブを作成したかどうかのフラグ。
		CPrimitive*	m_pPrimitive;		//!<プリミティブ。
		CVector3	m_position;			//!<座標。
		CQuaternion	m_rotation;			//!<回転。
		CMatrix		m_worldMatrix;		//!<ワールド行列。
		CMatrix		m_rotationMatrix;	//!<ワールド回転行列。
	};
	struct SMergeInfo{
		u32	delVertNo;
		u32 replaceVertNo;
		u32 decReplaceVertNo;
	};
	struct SPolygonInfo {
		CVector3	normal;		//!<面法線
		u32			vertNos[3];		//!<面を構成する頂点。
	};
	/*!
	*@brief	頂点バッファの法線を作成。
	*@param[out]	vertexBuffer	頂点バッファ。
	*@param[in]		indexBuffer		インデックスバッファ。
	*@param[in]		primType		プリミティブタイプ
	*/
	template<class TVertex, class TIndex>
	void CreateVertexNormal(
		std::vector<TVertex>& vertexBuffer, 
		const std::vector<TIndex>& indexBuffer,
		CPrimitive::EType primType )
	{	
		//面法線を求める。
		TK_ASSERT( primType == CPrimitive::eTriangleList, "not implement TraiangleStrip yet...");
		u32 numFace = indexBuffer.size() / 3;
		std::unique_ptr<SPolygonInfo[]> polygonInfo;
		std::vector<std::list<SPolygonInfo>>	polygoninfos;
		polygoninfos.resize(vertexBuffer.size());
		for (u32 i = 0; i < numFace; i++) {
			CVector3 pos[3];
			u32 t = i * 3;
			SPolygonInfo polyInfo;
			polyInfo.vertNos[0] = indexBuffer.at(t);
			polyInfo.vertNos[1] = indexBuffer.at(t+1);
			polyInfo.vertNos[2] = indexBuffer.at(t+2);
			CVector3 normal(0.0f, 0.0f, 0.0f);
			CVector3 vertPos[3];
			for (u32 k = 0; k < 3; k++) {
				const TVertex& vtx = vertexBuffer.at(polyInfo.vertNos[k]);
				vertPos[k].Set(	vtx.pos[0], vtx.pos[1], vtx.pos[2] );
			}
			CVector3 t0, t1;
			t0.Subtract(vertPos[1], vertPos[0]);
			t1.Subtract(vertPos[2], vertPos[0]);
			t0.Normalize();
			t1.Normalize();
			polyInfo.normal.Cross(t0, t1);
			polygoninfos.at(polyInfo.vertNos[0]).push_back(polyInfo);
			polygoninfos.at(polyInfo.vertNos[1]).push_back(polyInfo);
			polygoninfos.at(polyInfo.vertNos[2]).push_back(polyInfo);
		}
		//頂点法線を求める。
		for (u32 vertNo = 0; vertNo < vertexBuffer.size(); vertNo++) {
			std::list<SPolygonInfo>& polygonInfo = polygoninfos.at(vertNo);
			CVector3 normal(0.0f, 0.0f, 0.0f);
			for (const auto& p : polygonInfo) {
				normal.Add(p.normal);
			}
			normal.Div(s_cast<f32>(polygonInfo.size()));
			f32* pNormal = vertexBuffer.at(vertNo).normal;
			pNormal[0] = normal.x;
			pNormal[1] = normal.y;
			pNormal[2] = normal.z;
			pNormal[3] = 1.0f;
		}

	}
	/*!
	 *@brief	頂点マージ。
	 *@details
	 * 計算量は頂点数をNとしたときにO(N^2)になるので、頂点数が増えると遅くなる。</br>
	 * 速度が問題になったら二分木検討。
	 *@param[in, out]	vertexBuffer		マージ対象の頂点バッファ。
	 *@param[in, out]	indexBuffer			マージ対象のインデックスバッファ。
	 *@param[in]		margeLenThreshold	マージする頂点同士の距離の閾値。この値以下の頂点はマージされます。
	 */
	template<class TVertex, class TIndex>
	void MergeVertex( std::vector<TVertex>& vertexBuffer, std::vector<TIndex>& indexBuffer, f32 margeLenThreshold )
	{
	#if 1	//こっちはマージされた頂点は削除する。
		f32 margeLenThresholdSq = margeLenThreshold * margeLenThreshold;
		typedef std::pair<u32, u32>	SMergeInfo;			//マージ情報。削除する頂点番号と、置き換える頂点番号のペア情報。
		typename std::vector<bool> deleteVertexFlags;	//頂点削除のフラグのリスト。
		typename std::vector<u32>  deleteCount;			//自身より小さい番号の頂点がいくつ削除されたかのカウントする
		std::list<SMergeInfo> mergeInfos;				//削除する頂点番号のリスト。
		deleteVertexFlags.resize( vertexBuffer.size() );
		deleteCount.resize( vertexBuffer.size() );
		for (auto& p : deleteVertexFlags) {
			p = false;
		}
		for (auto& p : deleteCount) {
			p = 0;
		}
		u32 vertNo = 0;
		for( u32 vertNo = 0; vertNo != vertexBuffer.size(); vertNo++ ){
			if(deleteVertexFlags[vertNo]){
				//削除予定の頂点なので調べる必要なし。
				continue;
			}
			const TVertex& v0 = vertexBuffer[vertNo];
			CVector3 vPos0;
			CVector3 vLen;
			vPos0.Set( v0.pos[0], v0.pos[1], v0.pos[2] );
			for( u32 delVertNo = 0; delVertNo < vertexBuffer.size(); delVertNo++ ){
				if(vertNo != delVertNo && !deleteVertexFlags[delVertNo]){
					//頂点同士の距離を調べる。
					const TVertex& v1 = vertexBuffer[delVertNo];
					vLen.Set( v1.pos[0], v1.pos[1], v1.pos[2] );
					vLen.Subtract(vPos0, vLen);
					f32 lenSq = vLen.LengthSq();
					if(lenSq < margeLenThresholdSq ){
						deleteVertexFlags[delVertNo] = true;	//削除する印をつける。
						//マージ情報を作成する。
						SMergeInfo mergeInfo;
						mergeInfo.first = delVertNo;
						mergeInfo.second = vertNo;
						mergeInfos.push_back(mergeInfo);
					}
				}
			}
		}
		for( auto& mergeInfoIt : mergeInfos ){
			for( TIndex index = mergeInfoIt.first+1; index < deleteCount.size(); index++ ){
				deleteCount[index]++;
			}
		}
		std::vector<TVertex> vertexBufferTmp = vertexBuffer;
		vertexBuffer.clear();
		for( u32 i = 0; i < vertexBufferTmp.size(); i++ ){
			if( !deleteVertexFlags[i] ){
				vertexBuffer.push_back(vertexBufferTmp[i]);
			}
		}
		//頂点を削除したのでインデックスバッファを調整。
		{
			for( auto& mergeInfoIt : mergeInfos ){
				//インデックスバッファから削除対象の頂点を探しつつ、削除対象の頂点より番号が大きいものは減算する。。
				for( auto& indexIt : indexBuffer ){
					if( mergeInfoIt.first == indexIt ){
						//削除対象
						indexIt = mergeInfoIt.second;
					}
				}
			}
		}
		for( auto& indexIt : indexBuffer ){
			indexIt -= deleteCount[indexIt];
		}
	#else	//こっちはマージした頂点は削除しないで、インデックスバッファを使用してマージするだけ
		f32 margeLenThresholdSq = margeLenThreshold * margeLenThreshold;
		typedef std::pair<u32, u32>	SMergeInfo;			//マージ情報。削除する頂点番号と、置き換える頂点番号のペア情報。
		typename std::vector<bool> deleteVertexFlags;	//頂点削除のフラグのリスト。
		std::list<SMergeInfo> mergeInfos;				//削除する頂点番号のリスト。
		deleteVertexFlags.resize(vertexBuffer.size());
		for (auto& p : deleteVertexFlags) {
			p = false;
		}
		u32 vertNo = 0;
		for( u32 vertNo = 0; vertNo != vertexBuffer.size(); vertNo++ ){
			if(deleteVertexFlags[vertNo]){
				//削除予定の頂点なので調べる必要なし。
				continue;
			}
			const TVertex& v0 = vertexBuffer[vertNo];
			CVector3 vPos0;
			CVector3 vLen;
			vPos0.Set( v0.pos[0], v0.pos[1], v0.pos[2] );
			for( u32 delVertNo = 0; delVertNo < vertexBuffer.size(); delVertNo++ ){
				if(vertNo != delVertNo && !deleteVertexFlags[delVertNo]){
					//頂点同士の距離を調べる。
					const TVertex& v1 = vertexBuffer[delVertNo];
					vLen.Set( v1.pos[0], v1.pos[1], v1.pos[2] );
					vLen.Subtract(vPos0, vLen);
					f32 lenSq = vLen.LengthSq();
					if(lenSq < margeLenThresholdSq ){
						deleteVertexFlags[delVertNo] = true;	//削除する印をつける。
						//マージ情報を作成する。
						SMergeInfo mergeInfo;
						mergeInfo.first = delVertNo;
						mergeInfo.second = vertNo;
						mergeInfos.push_back(mergeInfo);
					}
				}
			}
		}
		//頂点を削除したのでインデックスバッファを調整。
		{
			for( auto& mergeInfoIt : mergeInfos ){
				//インデックスバッファから削除対象の頂点を探しつつ、削除対象の頂点より番号が大きいものは減算する。。
				for( auto& indexIt : indexBuffer ){
					if( mergeInfoIt.first == indexIt ){
						//削除対象
						indexIt = mergeInfoIt.second;
					}
				}
			}
		}
	#endif
	}
}
#endif //_TKSHAPEBASE_H_