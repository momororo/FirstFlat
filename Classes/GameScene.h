//
//  GameScene.h
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#ifndef __FitstPenguin_android__GameScene__
#define __FitstPenguin_android__GameScene__

#include "cocos2d.h"
#include "Player.h"
#include "Walls.h"


class GameScene : public cocos2d::Layer{
    
protected:
    
    //スタートラベル
    cocos2d::Label *start;
    //スコア表示看板
    cocos2d::Sprite *scoreNode;
    //スコア
    cocos2d::Label *scoreLabel;
    
    cocos2d::Sprite *player;
    
    //硬直時間
    int rigidTappedTime = 0;
    //硬直フラグ
    bool rigidTappedFlag = false;
    
    bool testFlag = false;
    
    
    //ボタン類の変数一覧
    cocos2d::Sprite *aquaCircle;
//    cocos2d::Sprite *aquaRing;
    cocos2d::Sprite *orangeCircle;
//    cocos2d::Sprite *orangeRing;
    cocos2d::Sprite *yellowCircle;
//    cocos2d::Sprite *yellowRing;
  
    //1フレーム毎の処理
    void update(float delta);
    
    
    public :
    
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    void setButton();
    
    //タップイベントの宣言
    void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
/*
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
*/
    //衝突イベント
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    
    virtual void setDrops(float time);


    
    
};








#endif /* defined(__FitstPenguin_android__GameScene__) */
