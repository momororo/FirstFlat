//
//  TitleScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "TitleScene.h"
#include "GameScene.h"

#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;


Scene *TitleScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene -> addChild(layer);
    
    return scene;
    
}

bool TitleScene::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    
    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(128,229,255,255), Color4B(95,211,188,255));
    this -> addChild(bgGradient);

    
    //initTitleBk();
    initStart();
    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(TitleScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(TitleScene::onTouchCancelled,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/

    
    
    
    
    
    return true;
    
    
}

void TitleScene::initStart(){
    
    start = Sprite::create();
    
    start -> setTextureRect(Rect(0,0,200,200));
    
    start -> setColor(Color3B::BLUE);
    
    start -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    
    this -> addChild(start,0);
    
}


bool TitleScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    /*
     //target : ターゲットのスプライト
     auto target = (Sprite*)event->getCurrentTarget();
     //targetBox : タッチされたスプライトの領域
     Rect targetBox = target->getBoundingBox();
     
     */
    
    
    
    
    Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    
    if (start->getBoundingBox().containsPoint(touchPoint))
    {
        CCLOG("スタートボタンをタップ");
        
        
        
        //アニメーション付き
        float duration = 1.0f;  //開始→終了にかける時間
        Scene* nextScene = CCTransitionFade::create(duration, GameScene::createScene());
        Director::getInstance()->replaceScene(nextScene);
        return true;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    return true;
    
}

void TitleScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    
    
}

void TitleScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
}

void TitleScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    //タッチキャンセル
    CCLOG("touchCancelled");
    
}

