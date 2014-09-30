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

DrawNode *circle;

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
    
    
    //スタートボタン作成
    initStart();
    
    /*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create();
    sprite->setTextureRect(Rect(0, 0, 200, 100));
    sprite->setColor(Color3B::GRAY);
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    sprite->setOpacity(0);
    addChild(sprite);
    
    //1秒かけてフェードイーン
    auto action = FadeIn::create(1);
    sprite->runAction(action);
    */
    
    
    
    
    
    /*
    //白いスプライトを作成
    Size s = Director::getInstance()->getVisibleSize();
    auto spr = Sprite::create();
    spr->setPosition(Vec2(s.width*.5, s.height*.5));
    spr->setTextureRect(Rect(0, 0, 200, 200));
    spr->setColor(Color3B::WHITE);
    addChild(spr);
    
    //1秒かけて青に変わるアニメーション（秒数：1、R値：51、G値：75、B値：112）
    spr->runAction(TintTo::create(1, 51, 75, 112));
    */
    
    
    circle = DrawNode::create();
    circle -> drawDot(Point(selfFrame.width/2, selfFrame.height/2), 20, Color4F::WHITE);
    addChild(circle, 0);
    
    
    //auto move = MoveBy::create(2, Vec2(0, -400));
    
    auto scaleAction = ScaleBy::create(2, 2);
    
    //auto seq = Sequence::create(move, scaleAction,NULL);
    
    //circle -> runAction(seq);
    
    circle -> runAction(scaleAction);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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



// スタートボタン作成
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
    
    
    
    //スタートボタンタップ時の操作
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

