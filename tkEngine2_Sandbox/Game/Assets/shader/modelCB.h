/*!
 * @brief	モデル用の定数バッファ。
 */
/*!
 * @brief	頂点シェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4 screenParam;	// スクリーンパラメータ(near, far, screenWidth, screenHeight)
	int isZPrepass;		//Zプリパス？
};

/*!
 * @brief	ライト用の定数バッファ。
 */
cbuffer lightCb : register(b1)
{
	float3 eyePos;				//カメラの位置。
	int numDirectionLight;		//ディレクションライトの数。
};

cbuffer MaterialParamCb : register(b2){
	float roughness;	//粗さ。
	float metallic ;	//メタリック。
	float anisotropic;	//異方性反射
};