
enchant();

const SCREEN_WIDTH 	= 512;					//�X�N���[���̕��B
const SCREEN_HEIGHT = 512;					//�X�N���[���̍����B
const SPRITE_SIZE 	= 32;					//�X�v���C�g�̕�
const MOVE_SPEED 		= SPRITE_SIZE / 4;	//�v���C���[�̈ړ����x�B
const ENEMY_MOVE_SPEED 	= SPRITE_SIZE / 8;	//�G�̈ړ����x�B
const ENEMY_IDLE_TIME   = 10;				//�G�̑ҋ@���ԁB(�P�ʂ̓t���[���B)
const NUM_CLEAR_ITEM	= 3;				//�N���A�A�C�e���̐��B
//�}�b�v��`�B
var map = [
	[16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16],
	[16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16], 
	[16, 0,16,16,16,16,16,16,16,16,16, 0,16, 0, 0,16],
	[16, 0, 4, 4,16, 0,-2,16,16, 0,16, 0,16,16, 0,16],
	[16, 0, 4, 4,16, 0,16,16,16, 0,16, 0, 0, 0, 0,16],
	[16, 0, 4, 4, 0, 0, 0,-1, 0, 0,16, 0, 0,16, 0,16],
	[16, 0, 4, 4,16, 0, 4, 0, 0, 0,16, 0,-1,16, 0,16],
	[16, 0,16, 0,16, 0, 4, 0,16, 0,16,-2, 0,16, 0,16],
	[16, 0, 0, 0, 0, 0, 0, 0,16, 4,16,16,16,16, 0,16],
	[16, 0, 0, 0, 0,16,16,16,16, 4, 4, 4, 4, 4, 4,16],
	[16, 0, 0,16,16,16, 0, 0, 0, 4, 0, 0, 0, 4, 4,16],
	[16, 0, 0,16,-2,16, 0,16,16, 4, 0,16, 0, 0, 4,16],
	[16, 0, 0,16, 0, 0, 0,16,16, 0, 0,16, 0, 0, 4,16],
	[16, 0, 0,16, 0, 0, 0,16, 0, 0, 0,16, 0, 0, 4,16],
	[16, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0,16],
	[16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16],
];
    
window.onload = function(){
	/*!-------------------------------------------------------------------------------------------------
     *@brief	�G���g���|�C���g�B
     -------------------------------------------------------------------------------------------------*/
    var game = new Core(SCREEN_WIDTH, SCREEN_HEIGHT);
    var bear;
    var enemyArray 		= new Array();
	var clearItemArray 	= new Array();
    game.fps = 15;
    game.preload("image/chara1.png");
    game.preload("image/map.png");
    game.preload("image/enemy.png");
    game.preload("image/item.png");
    game.onload = function(){
        var mapArray 		= new Array();
        var gamManager		= new CGameManager();
        //�}�b�v���쐬�B
        for( var i = 0; i < map.length; i++ ){
			for( var j = 0; j < map[0].length; j++ ){
				var mapId = map[j][i];
				if(map[j][i] == -1 || map[j][i] == -2){
					//�G�ƃA�C�e�����u����Ă���Ƃ���͒n�ʂ͕���ɂ���B
					mapId = 0;	//�G������Ƃ���̃}�b�v�͂O�Ԗڂɂ���B
				}
				mapArray.push( new CMap(SPRITE_SIZE * i, SPRITE_SIZE * j, mapId) );
			}
		}
		//�G�ƃN���A�A�C�e�������B
		for( var i = 0; i < map.length; i++ ){
			for( var j = 0; j < map[0].length; j++ ){
				var mapId = map[j][i];
				if(map[j][i] == -1){
					//�G���쐬�B
					enemyArray.push( new CEnemy( SPRITE_SIZE * i, SPRITE_SIZE * j ) );
				}else if(map[j][i] == -2){
					//�N���A�A�C�e�����쐬�B
					clearItemArray.push( new CClearItem( SPRITE_SIZE * i, SPRITE_SIZE * j, i, j ) );
				}
			}
		}
		//�F�쐬�B
		bear = new CBear(32, 32);
    };
    game.start();
    /*!-------------------------------------------------------------------------------------------------
     *@brief	�F�N���X�B
     -------------------------------------------------------------------------------------------------*/
    var CBear = enchant.Class.create(enchant.Sprite, {
	    /*!
	     * @brief	�Q�[���J�n���Ɉ�x�����Ă΂�鏈���B
	     */
        initialize: function(x, y) {
            enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
            this.x = x;
            this.y = y;
            this.image = game.assets['image/chara1.png'];
            this.frame = 5;
            game.rootScene.addChild(this);
            this.scale.x = 1;
        },
        /*!
         * @brief	���t���[���Ă΂�鏈���B
         */
        onenterframe : function()
        {
			//�ړ��B
			this.move();
			//�A�j���[�V����
			this.animation();
		},
		/*!
		 * @brief	�ړ������B
		 */
		move : function()
		{
			var isMove = false;
			var rectHalfW = SPRITE_SIZE * 0.1;
            var rectHalfH = SPRITE_SIZE * 0.3;
			//x�����̈ړ������B
			{
				var x = this.x;
				var y = this.y;
				if(game.input.left){
					x -= MOVE_SPEED;
				}else if(game.input.right){
					x += MOVE_SPEED;
				}
				var center_x = x + SPRITE_SIZE / 2;
	            var center_y = y + SPRITE_SIZE / 2;
				var hitFlag = CheckIntersectRectToMap(
					center_x - rectHalfW,
					center_x + rectHalfW,
					center_y - rectHalfH,
					center_y + rectHalfH
				);

				if(!hitFlag){
					//�؂ɂ������Ă��Ȃ��B
					this.x = x;
				}
			}
			//y�����̈ړ������B
			{
				var x = this.x;
				var y = this.y;
				if(game.input.up){
					y -= MOVE_SPEED;
				}else if(game.input.down){
					y += MOVE_SPEED;
				}
				var center_x = x + SPRITE_SIZE / 2;
	            var center_y = y + SPRITE_SIZE / 2;
				var hitFlag = CheckIntersectRectToMap(
					center_x - rectHalfW,
					center_x + rectHalfW,
					center_y - rectHalfH,
					center_y + rectHalfH
				);
				if(!hitFlag){
					//�������Ă��Ȃ��B
					this.y = y;
				}
			}
		},
		/*!
		 * @brief	�A�j���[�V���������B
		 */
		animation : function()
		{
			if(game.input.left && this.scale.x != -1){
				this.scale.x = -1
				this.scale(-1, 1.0);
			}else if( game.input.right && this.scale.x != 1 ){
				this.scale.x = 1
				this.scale(-1, 1.0);
			}
			if( game.input.left 	||
				game.input.right 	||
				game.input.up 		||
				game.input.down
			){
				this.frame = 5 + this.age % 2;
			}
		}
    });
    /*!-------------------------------------------------------------------------------------------------
     *@brief	�}�b�v�N���X�B
     --------------------------------------------------------------------------------------------------*/
	var CMap = enchant.Class.create(enchant.Sprite, {
		/*!
	     * @brief	�Q�[���J�n���Ɉ�x�����Ă΂�鏈���B
	     */
        initialize: function(x, y, frame) {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
            this.x = x;
            this.y = y;
            this.image = game.assets['image/map.png'];
            this.frame = frame;
            this.moveCount = 0;
            game.rootScene.addChild(this);
		}
	});
	/*!-------------------------------------------------------------------------------------------------
     *@brief	�G�N���X�B
    -------------------------------------------------------------------------------------------------*/
     var CEnemy = enchant.Class.create(enchant.Sprite, {
        initialize: function(x, y) {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
			this.initPos_x = x;				//������X���W�B�B�B�߂��Ă���Ƃ��Ɏg���\��E�E�E�B
			this.initPos_y = y;				//������Y���W�E�E�E�߂��Ă���Ƃ��Ɏg���\��E�E�E�B
			this.x = x;
            this.y = y;
            this.moveDir = -1;				//�i�s�����B
            this.enemyState = "�ҋ@";		//�G�̏�ԁB
            this.idelCount = ENEMY_IDLE_TIME;
            this.image = game.assets['image/enemy.png'];
            this.frame = 0;
            this.baseFrame = 0;
            game.rootScene.addChild(this);
		},
		/*!
         * @brief	�G�̖��t���[���Ă΂�鏈���B
         */
        onenterframe : function()
        {
			if(this.enemyState == '�ҋ@'){
				//�G���ҋ@��ԁB
				this.idelCount++;
				if( this.idelCount > ENEMY_IDLE_TIME ){
					//�ړ���ԂɑJ�ڂ���B
					this.enemyState = "�ړ�";
					this.moveDir = parseInt( (Math.random() * 10) % 4 );
					if( this.moveDir == 0){
						//�E�ړ��B
						this.baseFrame = 6;
					}else if( this.moveDir == 1){
						//���ړ�
						this.baseFrame = 3;
					}else if( this.moveDir == 2){
						//��ړ��B
						this.baseFrame = 9;
					}else if( this.moveDir == 3){
						//���ړ��B
						this.baseFrame = 0;
					}
					this.idelCount = 0;
				}
			}else if(this.enemyState == '�ړ�'){
				if((this.age % 10) == 0 || this.moveDir == -1 ){
					//�ҋ@��Ԃɑ@�ۂ���
					this.enemyState = '�ҋ@';
					return ;
				}
				//�ړ������B
				this.move();
				this.frame = this.baseFrame + this.age % 2;
			}
		},
		/*!
		 * @brief	�G�̈ړ������B
		 */
		move : function()
		{
			var rectHalfW = SPRITE_SIZE * 0.2;
            var rectHalfH = SPRITE_SIZE * 0.4;
			var x = this.x;
			var y = this.y;
			if(this.moveDir == 0){
				//�E�ɓ������B
				x += ENEMY_MOVE_SPEED;
			}else if( this.moveDir == 1 ){
				//���ɓ������B
				x -= ENEMY_MOVE_SPEED;
			}
			//�Փ˔���B
			var center_x = x + SPRITE_SIZE / 2;
            var center_y = y + SPRITE_SIZE / 2;
			var hitFlag = CheckIntersectRectToMap(
				center_x - rectHalfW,
				center_x + rectHalfW,
				center_y - rectHalfH,
				center_y + rectHalfH
			);
			if( !hitFlag ){
				//�؂ɂ������Ă��Ȃ��B
				this.x = x;
			}
			if( this.moveDir == 2 ){
				//��ɓ������B
				y -= ENEMY_MOVE_SPEED;
			}else if( this.moveDir == 3){
				//���ɓ������B
				y += ENEMY_MOVE_SPEED;
			}
			//�Փ˔���B
			var center_x = x + SPRITE_SIZE / 2;
            var center_y = y + SPRITE_SIZE / 2;
			var hitFlag = CheckIntersectRectToMap(
				center_x - rectHalfW,
				center_x + rectHalfW,
				center_y - rectHalfH,
				center_y + rectHalfH
			);
			if( !hitFlag ){
				//�؂ɂ������Ă��Ȃ��B
				this.y = y;
			}
		}
	});
	/*!--------------------------------------------------------
	 * @brief	�N���A�̂��߂̃A�C�e���B
	 --------------------------------------------------------*/
	var CClearItem = enchant.Class.create(enchant.Sprite, {
		/*!
	     * @brief	�Q�[���J�n���Ɉ�x�����Ă΂�鏈���B
	     */
        initialize: function(x, y, mapCol, mapRow) {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
            this.x = x;
            this.y = y;
            this.image = game.assets['image/item.png'];
            this.frame = 34;
            this.mapCol = mapCol;
            this.mapRow = mapRow;
            game.rootScene.addChild(this);
		},
		/*!
		 * @brief	���t���[���Ă΂�鏈���B
		 */
		onenterframe : function()
        {
			this.scaleX = Math.sin(this.age * 0.2);		//x���Ɋg��k��������ƂQ�����ł͉�]���Ă���悤�Ɍ�����Ƃ����g���b�N���g���B
		}
	});
	/*!--------------------------------------------------------
	 * @brief	�Q�[���̐i�s�Ǘ��B
	 --------------------------------------------------------*/
	var CGameManager = enchant.Class.create( enchant.Sprite,{
		initialize: function() {
			enchant.Sprite.call(this, SPRITE_SIZE, SPRITE_SIZE);
			this.getClearItemCount = 0;		//�N���A�A�C�e�����Q�b�g�������B
			game.rootScene.addChild(this);
		},
		onenterframe : function()
        {
			var mapCol = parseInt( bear.x / SPRITE_SIZE );
			var mapRow = parseInt( bear.y / SPRITE_SIZE );
			if( map[mapRow][mapCol] == -2 ){
				//�A�C�e���Q�b�g�B
				this.getClearItemCount++;
				map[mapRow][mapCol] = 0;	//�A�C�e���擾�ς݂ɂ���B
				//�Q�b�g�����A�C�e�����폜
				for( var i = 0; i < clearItemArray.length; i++ ){
					if(clearItemArray[i].mapCol == mapCol
					 	&& clearItemArray[i].mapRow == mapRow 
					){
						game.rootScene.removeChild(clearItemArray[i]);
						clearItemArray.splice(i,1);
						break;
					}
				}
			}
			if(this.getClearItemCount == NUM_CLEAR_ITEM){
				//�Q�[���N���A
				game.end(0, '�N���A');
			}
		}
	});
};
/*!
 * @brief	�n�`�Ƃ̏Փ˔���
 */
function CheckIntersectRectToMap( left, right, top, bottom )
{
	//����
	var mapCol = parseInt( left / SPRITE_SIZE );
	var mapRow = parseInt( top / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//�������Ă���B
		return 1;
	}
	//����
	mapCol = parseInt( left / SPRITE_SIZE );
	mapRow = parseInt( bottom / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//�������Ă���B
		return 1;
	}
	//�E��
	var mapCol = parseInt( right / SPRITE_SIZE );
	var mapRow = parseInt( top / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//�������Ă���B
		return 1;
	}
	//�E��
	var mapCol = parseInt( right / SPRITE_SIZE );
	var mapRow = parseInt( bottom / SPRITE_SIZE );
	if( map[mapRow][mapCol] == 16 ){
		//�������Ă���B
		return 1;
	}
	return 0;
}
