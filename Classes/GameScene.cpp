//
//  GameScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "GameScene.h"

#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;

Scene *GameScene::createScene(){
    
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene -> addChild(layer);
    
    return scene;
    
}

bool GameScene::init(){
    
    if (!Layer::init())
    {
        return false;
    }
    
    
    //画面サイズの取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    /**************　メイン画面設定  ******************/
    auto background = LayerColor::create(Color4B::RED, selfFrame.width, selfFrame.height);
    this -> addChild(background,0);
    /**************　メイン画面設定　おわり  ******************/
    
    
    
    
    
    /**************　プレイヤー設定  ******************/
    player = Sprite::create();
    
    player->setTextureRect(Rect(0, 0, visibleSize.width/8, visibleSize.width/8));
    
    player->setColor(Color3B::GREEN);
    
    player->setPosition(Vec2(selfFrame.width/2, selfFrame.height/7));
    
    this -> addChild(player);
    /**************　プレイヤー設定　おわり  ******************/
    
    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  おわり ****************/

    
    
    
    
    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    

    
    
    //プレイヤーの移動
    Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    player->setPosition(Vec2(touchPoint.x, selfFrame.height/7));
    
    
    
    return true;
    
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    
    
    
    
    
    
    
    //プレイヤーの移動
    Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    player->setPosition(Vec2(touchPoint.x, selfFrame.height/7));
    
    return;
    
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    
    

    //プレイヤーの移動
    Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    player->setPosition(Vec2(touchPoint.x, selfFrame.height/7));

    
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    //タッチキャンセル
    CCLOG("touchCancelled");
    
}


