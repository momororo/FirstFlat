//
//  GameScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "GameScene.h"

#define selfFrame Director::getInstance() -> getWinSize()
#define visibleSize Director::getInstance()->getVisibleSize();


USING_NS_CC;

Scene *GameScene::createScene(){
    
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene -> addChild(layer);
    
    //物理オブジェクトにを可視的にしてくれるデバックモード
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
    return scene;
    
}

bool GameScene::init(){
    
    if (!Layer::init())
    {
        return false;
    }
    
    
    
    
    if (!Layer::init()) {
        return false;
    }
    
    
    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(128,229,255,255), Color4B(95,211,188,255));
    this -> addChild(bgGradient);
    

    //ボタンの生成
    this->setButton();
    
    
    
    
    
    
    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    
    
    
    
    
    
    
    
    
    return true;
    
    
    
    
    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");

    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
    //アクアリングの処理
    if (aquaCircle->getBoundingBox().containsPoint(touchPoint))
        
    {
        auto effectRing = Sprite::create("aqua_ring.png");
        effectRing -> setPosition(Vec2(aquaCircle->getPosition().x,aquaCircle->getPosition().y));
        effectRing -> setScale(0.1);
        effectRing -> setName("aquaRing");
            //物理体の生成
            auto aquaMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
            auto aquaRingBody = PhysicsBody::createBox(aquaCircle->getContentSize(), aquaMaterial);
            aquaRingBody->setDynamic(false); // 重力の影響を受けない
            effectRing->setPhysicsBody(aquaRingBody);
        
        addChild(effectRing);

        
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        effectRing -> runAction(ringSequence);
        
        return true;
    }

    //オレンジリングの処理
    if (orangeCircle->getBoundingBox().containsPoint(touchPoint))
        
    {
        auto effectRing = Sprite::create("orange_ring.png");
        effectRing -> setPosition(Vec2(orangeCircle->getPosition().x,orangeCircle->getPosition().y));
        effectRing -> setScale(0.1);
        effectRing -> setName("orangeRing");
            //物理体の生成
            auto orangeMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
            auto orangeRingBody = PhysicsBody::createBox(orangeCircle->getContentSize(), orangeMaterial);
            orangeRingBody->setDynamic(false); // 重力の影響を受けない
            effectRing->setPhysicsBody(orangeRingBody);
            
        addChild(effectRing);
        
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        effectRing -> runAction(ringSequence);
        
        return true;
    }
    
    
    
    //イエローリングの処理
    if (yellowCircle->getBoundingBox().containsPoint(touchPoint))
        
    {
        CCLOG("スタートボタンをタップ");
        
        auto effectRing = Sprite::create("yellow_ring.png");
        effectRing -> setPosition(Vec2(yellowCircle->getPosition().x,yellowCircle->getPosition().y));
        effectRing -> setScale(0.1);
        effectRing -> setName("aquaRing");
            //物理体の生成
            auto yellowMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
            auto yellowRingBody = PhysicsBody::createBox(yellowCircle->getContentSize(), yellowMaterial);
            yellowRingBody->setDynamic(false); // 重力の影響を受けない
            effectRing->setPhysicsBody(yellowRingBody);
        
        addChild(effectRing);
        
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        effectRing -> runAction(ringSequence);
        
        return true;
    }

    
    
    
    
    
    return true;
    
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    
    
    
    
    
    
    
    return;
    
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    
    
    
    return;
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    //タッチキャンセル
    CCLOG("touchCancelled");
    
}

void GameScene::setButton(){
    
    //アクアボタン
    aquaCircle = Sprite::create("aqua_circle.png");
    aquaCircle -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/6));
    aquaCircle -> setScale(0.1);
    aquaCircle -> setName("aquaCircle");
    //物理体の生成
        auto aquaMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto aquaCircleBody = PhysicsBody::createBox(aquaCircle->getContentSize(), aquaMaterial);
        aquaCircleBody->setDynamic(false); // 重力の影響を受けない
    aquaCircle->setPhysicsBody(aquaCircleBody);
    addChild(aquaCircle);
/*
    aquaRing = Sprite::create("aqua_ring.png");
    aquaRing -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/6));
    aquaRing -> setScale(0.1);
    addChild(aquaRing);
  */
    //オレンジボタン
    orangeCircle = Sprite::create("orange_circle.png");
    orangeCircle -> setPosition(Vec2(60,selfFrame.height/4));
    orangeCircle -> setScale(0.1);
    orangeCircle -> setName("orangeCircle");
    //物理体の生成
    auto orangeMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto orangeCircleBody = PhysicsBody::createBox(aquaCircle->getContentSize(), orangeMaterial);
    orangeCircleBody->setDynamic(false); // 重力の影響を受けない
    orangeCircle->setPhysicsBody(orangeCircleBody);
    addChild(orangeCircle);
/*
    orangeRing = Sprite::create("orange_ring.png");
    orangeRing -> setPosition(Vec2(60,selfFrame.height/4));
    orangeRing -> setScale(0.1);
    addChild(orangeRing);
*/
    //イエローボタン
    yellowCircle = Sprite::create("yellow_circle.png");
    yellowCircle -> setPosition(Vec2(selfFrame.width-60,selfFrame.height/4));
    yellowCircle -> setScale(0.1);
    yellowCircle -> setName("yellowCircle");
    //物理体の生成
        auto yellowMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto yellowCircleBody = PhysicsBody::createBox(aquaCircle->getContentSize(), yellowMaterial);
        yellowCircleBody->setDynamic(false); // 重力の影響を受けない
        yellowCircle->setPhysicsBody(yellowCircleBody);
    addChild(yellowCircle);

/*
    yellowRing = Sprite::create("yellow_ring.png");
    yellowRing -> setPosition(Vec2(selfFrame.width-60,selfFrame.height/4));
    yellowRing -> setScale(0.1);
    addChild(yellowRing);
 */
    
}


