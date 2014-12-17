//
//  GameScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "GameScene.h"
#include <string.h>

#define selfFrame Director::getInstance() -> getWinSize()
#define visibleSize Director::getInstance()->getVisibleSize();


USING_NS_CC;
using namespace CocosDenshion;



Scene *GameScene::createScene(){
    
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene -> addChild(layer);
    
    //物理オブジェクトにを可視的にしてくれるデバックモード
 //   scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
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
    
    //色の配列への格納
    colors->push_back(new std::string("green"));
    colors->push_back(new std::string("aqua"));
    colors->push_back(new std::string("yellow"));
    colors->push_back(new std::string("blue"));
    colors->push_back(new std::string("white"));
    colors->push_back(new std::string("purple"));
    colors->push_back(new std::string("red"));
    
    
    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(255,255,255,255), Color4B(255,255,255,255));
    this -> addChild(bgGradient);
    

    //ボタンの生成
    this->setButton();
    
    
    
    SimpleAudioEngine::getInstance()->preloadEffect("bFlat.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("c.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("d.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("cp03.mp3");
    
    //BGM
    SimpleAudioEngine::getInstance()->playBackgroundMusic("cp03.mp3",true);
    //音量
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);



    
    
    
    
    
    
    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchAllAtOnce::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan,this);
/*
    listener -> onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
*/
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    

    /*************　  衝突イベント設定   ****************/
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener -> onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);

    _eventDispatcher -> addEventListenerWithSceneGraphPriority(contactListener,this);
    
    /*************　  衝突イベント設定  終 ****************/
    
    

    //テスト用
    this -> schedule(schedule_selector(GameScene::setDrops), 0.2);
    
    //スコア機能の実装

    //1フレーム毎の動き
    this->scheduleUpdate();
    
    
    
    
    return true;
}

void GameScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    

//硬直中か判定
if(rigidTappedFlag == true){

    //硬直時間
    if(rigidTappedTime >= 0){
        
        //初期化
        rigidTappedTime = 0;
        rigidTappedFlag = false;
        
    }else{
        //リターン
        return;
    }
}
//硬直中か判定終

 
    
    
    //同じものがタップされないように小細工
    std::string tappedName = "";
    
    //ダブルタップのカウント
    unsigned long tappedCount = 0;
    
    
    //イテレーター
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    //ループ
    while (tappedCount != 2 && iterator != touches.end()) {
        
        Touch* touch = (Touch*)(*iterator);
        //ポイントの取得
        Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
        
        //アクアリングの処理
        if (greenCircle->getBoundingBox().containsPoint(touchPoint))
            
        {
            //前回タップと同じ色か確認(同じならreturn)
            if(tappedName == "green"){
                return;
            }
            
            auto effectRing = Sprite::create("green_ring.png");
            effectRing -> setPosition(Vec2(greenCircle->getPosition().x,greenCircle->getPosition().y));
            effectRing -> setScale(0.1);
            effectRing -> setName("green");
            effectRing -> setTag(2);
            effectRing -> setOpacity(240);
            
            //物理体の生成
            auto greenMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
            auto greenRingBody = PhysicsBody::createCircle((effectRing->getContentSize().width/2)*effectRing->getScale(),greenMaterial);
            greenRingBody->setDynamic(false); // 重力の影響を受けない
            greenRingBody->setEnable(true);
            
            greenRingBody->setCategoryBitmask(0x01);
            greenRingBody->setCollisionBitmask(0);
            greenRingBody->setContactTestBitmask(0x02);
            effectRing->setPhysicsBody(greenRingBody);
            
            addChild(effectRing);
            
            
            auto ringScale = ScaleBy::create(2, 12);
            auto ringFadeOut = FadeOut::create(2);
            auto ringRemove = RemoveSelf::create(true);
            auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
            auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
            
            effectRing -> runAction(ringSequence);
            
            greenCircle ->runAction(RotateBy::create(1, 360));
            
            tappedName ="green";
            
        }
        
        //オレンジリングの処理
        if (blueCircle->getBoundingBox().containsPoint(touchPoint))
            
        {
            
            //前回タップと同じ色か確認(同じならreturn)
            if(tappedName == "blue"){
                return;
            }
            
            
            auto effectRing = Sprite::create("blue_ring.png");
            effectRing -> setPosition(Vec2(blueCircle->getPosition().x,blueCircle->getPosition().y));
            effectRing -> setScale(0.1);
            effectRing -> setName("blue");
            effectRing -> setTag(2);
            effectRing -> setOpacity(240);
            
            
            //物理体の生成
            auto blueMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
            auto blueRingBody = PhysicsBody::createCircle((effectRing->getContentSize().width/2)*effectRing->getScale(),blueMaterial);
            blueRingBody->setDynamic(false); // 重力の影響を受けない
            blueRingBody->setEnable(true);
            
            blueRingBody->setCategoryBitmask(0x01);
            blueRingBody->setCollisionBitmask(0);
            blueRingBody->setContactTestBitmask(0x02);
            
            effectRing->setPhysicsBody(blueRingBody);
            
            addChild(effectRing);
            
            auto ringScale = ScaleBy::create(2, 12);
            auto ringFadeOut = FadeOut::create(2);
            auto ringRemove = RemoveSelf::create(true);
            auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
            auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
            
            effectRing -> runAction(ringSequence);
            
            blueCircle->runAction(RotateBy::create(1, 360));
            
            tappedName = "blue";
            
            
        }
        
        
        
        //イエローリングの処理
        if (redCircle->getBoundingBox().containsPoint(touchPoint))
            
        {
            
            //前回タップと同じ色か確認(同じならreturn)
            if(tappedName == "red" ){
                return;
            }
            
            
            auto effectRing = Sprite::create("red_ring.png");
            effectRing -> setPosition(Vec2(redCircle->getPosition().x,redCircle->getPosition().y));
            effectRing -> setScale(0.1);
            effectRing -> setName("red");
            effectRing -> setTag(2);
            effectRing -> setOpacity(240);
            
            
            //物理体の生成
            auto redMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
            auto redRingBody = PhysicsBody::createCircle((effectRing->getContentSize().width/2)*effectRing->getScale(),redMaterial);
            redRingBody->setDynamic(false); // 重力の影響を受けない
            redRingBody->setEnable(true);
            
            redRingBody->setCategoryBitmask(0x01);
            redRingBody->setCollisionBitmask(0);
            redRingBody->setContactTestBitmask(0x02);
            
            effectRing->setPhysicsBody(redRingBody);
            
            addChild(effectRing);
            
            auto ringScale = ScaleBy::create(2, 12);
            auto ringFadeOut = FadeOut::create(2);
            auto ringRemove = RemoveSelf::create(true);
            auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
            auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
            
            effectRing -> runAction(ringSequence);
            
            redCircle->runAction(RotateBy::create(1, 360));
            
            tappedName = "red";
            
        }
        tappedCount++;
        iterator++;
    }
 
    rigidTappedFlag = true;
    

    
    return;
    
}
/*
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
*/

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact){
    
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    
    //本体に衝突したか判定する
    if(nodeA->getTag() == 1 || nodeB->getTag() == 1){
        
        //ゲームオーバーの処理
        CCLOG("本体に衝突");
        //ゲームオーバーの処理
        this->setGameover();
        
        return true;
    }
    
    //サークルとドロップの衝突と判断
    if(nodeA->getName() == nodeB->getName()){
     
        //一致(スコアアップ、サークル発生)
        CCLOG("一致しました");
        CCLOG("%s",nodeA->getName().c_str());
        CCLOG("%s",nodeB->getName().c_str());
        
        
        Sprite *dropCircle;
        Sprite *ring;
        
        //タグが3ならドロップはnodeA
        if(nodeA->getTag() == 3){
            
            dropCircle = (Sprite*)nodeA;
            ring = (Sprite*)nodeB;
            
            
        }else{
            dropCircle = (Sprite*)nodeB;
            ring = (Sprite*)nodeA;
        }
        
        
        if (nodeA->getName() == "green") {
        
            SimpleAudioEngine::getInstance()->playEffect("c.mp3");
        
        }else if(nodeA-> getName() == "blue"){
            
            SimpleAudioEngine::getInstance()->playEffect("bFlat.mp3");
        
        }else if(nodeA->getName() == "red"){
            
            //再生する
            SimpleAudioEngine::getInstance()->playEffect("d.mp3");
        
        }
        
        //物理体を削除
        dropCircle->getPhysicsBody()->setEnable(false);
        ring->getPhysicsBody()->setEnable(false);
        
        
        auto string = dropCircle->getName() + "_ring.png";
        
        //輪の設定
        auto dropRing = Sprite::create(string);
        dropRing -> setScale(0.01);
        dropRing -> setPosition(Vec2(dropCircle->getPosition().x , dropCircle->getPosition().y));
        addChild(dropRing);

        
        
        
        //オブジェクトの拡大
        auto scale = ScaleBy::create(2, 12);
        //オブジェクトの削除
        auto remove = RemoveSelf::create(true);
        //オブジェクトのフェードアウト
        auto fadeOut = FadeOut::create(2);
        
        //拡大・フェードアウト同時アクション
        auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
        //移動後拡大のアクション
        auto moveScale = Sequence::create(scaleFadeOut,remove,NULL);
        //移動後削除のアクション
        auto moveRemove = Sequence::create(remove,NULL);
        
        dropCircle -> runAction(moveRemove);
        dropRing -> runAction(moveScale);
        
        
         
        return true;
        
         
    }else{
        
        //不一致(ゲームオーバー)

        this->setGameover();
        
        return true;
    }
    
    return true;
}


void GameScene::setButton(){
    
    
    for(int idx = 0; idx < colors->size() ; idx++){
        
        //色を抜き出し
        std::string color = *colors->at(idx);
        
        
        //文字列操作
        std::string pngName = "";
        pngName.append(color);
        pngName.append("_umbrella.png");
        //スプライト生成
        auto circle = Sprite::create(pngName);
        
        circle -> setPosition(Vec2(selfFrame.width/8*(idx + 1), selfFrame.height/6));

        circle -> setScale(0.05);
        
        circle -> setName(color);
        
        circle -> setTag(1);

        PhysicsMaterial circleMaterial;
        
        //auto greenMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto circleBody = PhysicsBody::createCircle((circle->getContentSize().width/2)*circle->getScale(),circleMaterial);
        circleBody->setDynamic(false); // 重力の影響を受けない
        circleBody->setEnable(true);
        
        circleBody->setCategoryBitmask(0x01);
        circleBody->setCollisionBitmask(0);
        circleBody->setContactTestBitmask(0x02);
        
        circle->setPhysicsBody(circleBody);
        
        this->addChild(circle);

    }

/*
    //グリーンボタン
    greenCircle = Sprite::create("green_umbrella.png");
    greenCircle -> setPosition(Vec2(selfFrame.width/6*1, selfFrame.height/6));
    greenCircle -> setScale(0.1);
    greenCircle -> setName("Circle");
    greenCircle -> setTag(1);
    //物理体の生成
    PhysicsMaterial greenMaterial;

        //auto greenMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto greenCircleBody = PhysicsBody::createCircle((greenCircle->getContentSize().width/2)*greenCircle->getScale(),greenMaterial);
        greenCircleBody->setDynamic(false); // 重力の影響を受けない
        greenCircleBody->setEnable(true);

        greenCircleBody->setCategoryBitmask(0x01);
        greenCircleBody->setCollisionBitmask(0);
        greenCircleBody->setContactTestBitmask(0x02);

    greenCircle->setPhysicsBody(greenCircleBody);
    addChild(greenCircle);
*/
/*
    greenRing = Sprite::create("green_ring.png");
    greenRing -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/6));
    greenRing -> setScale(0.1);
    addChild(greenRing);
  */
/*
    //ブルーボタン
    blueCircle = Sprite::create("blue_umbrella.png");
    blueCircle -> setPosition(Vec2(selfFrame.width/6*3,selfFrame.height/6));
    blueCircle -> setScale(0.1);
    blueCircle -> setName("Circle");
    blueCircle -> setTag(1);

    //物理体の生成
    auto blueMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto blueCircleBody = PhysicsBody::createCircle((blueCircle->getContentSize().width/2)*blueCircle->getScale(),blueMaterial);
    blueCircleBody->setDynamic(false); // 重力の影響を受けない
    blueCircleBody->setEnable(true);
    blueCircleBody->setCategoryBitmask(0x01);
    blueCircleBody->setCollisionBitmask(0);
    blueCircleBody->setContactTestBitmask(0x02);
    blueCircle->setPhysicsBody(blueCircleBody);
    addChild(blueCircle);
*/
/*
    blueRing = Sprite::create("blue_ring.png");
    blueRing -> setPosition(Vec2(60,selfFrame.height/4));
    blueRing -> setScale(0.1);
    addChild(blueRing);
*/
/*
    //レッドボタン
    redCircle = Sprite::create("red_umbrella.png");
    redCircle -> setPosition(Vec2(selfFrame.width/6*5,selfFrame.height/6));
    redCircle -> setScale(0.1);
    redCircle -> setName("Circle");
    redCircle -> setTag(1);

    //物理体の生成
        auto redMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto redCircleBody = PhysicsBody::createCircle((redCircle->getContentSize().width/2)*redCircle->getScale(),redMaterial);
        redCircleBody->setDynamic(false); // 重力の影響を受けない
        redCircleBody->setEnable(true);

        redCircleBody->setCategoryBitmask(0x01);
        redCircleBody->setCollisionBitmask(0);
        redCircleBody->setContactTestBitmask(0x02);

        redCircle->setPhysicsBody(redCircleBody);
    addChild(redCircle);
*/
/*
    redRing = Sprite::create("red_ring.png");
    redRing -> setPosition(Vec2(selfFrame.width-60,selfFrame.height/4));
    redRing -> setScale(0.1);
    addChild(redRing);
 */
    
}

#pragma mark-
#pragma mark タイトルに雨を降らせる動作


void GameScene::setDrops(float time){
    
    auto rnd = arc4random_uniform(6);
    
    
    std::string pngCircle;
    std::string pngRing;
    std::string dropName;
    Vec2 dropPosition;
    
    //円の設定

    //パターンの割り振り
    if (rnd == 0) {
        
        pngCircle = "green_circle.png";
        dropName = "green";
        dropPosition = Vec2(selfFrame.width/6/1, selfFrame.height*1.5);
        
        
    }else if(rnd == 1){

        pngCircle = "blue_circle.png";
        dropName = "blue";
        dropPosition = Vec2(selfFrame.width/6*3, selfFrame.height*1.5);



    }else if(rnd == 2){
        
        
        pngCircle = "red_circle.png";
        dropName = "red";
        dropPosition = Vec2(selfFrame.width/6*5,selfFrame.height*1.5);


        
    }else if(rnd == 3){
        
        pngCircle = "aqua_circle.png";
        dropName = "aqua";
        dropPosition = Vec2(selfFrame.width/6*2,selfFrame.height*1.5);
        
    }else if (rnd == 4){
        
        pngCircle = "yellow_circle.png";
        dropName = "yellow";
        dropPosition = Vec2(selfFrame.width/6*3,selfFrame.height*1.5);

    }else if (rnd == 5){
    
        pngCircle = "purple_circle.png";
        dropName = "purple";
        dropPosition = Vec2(selfFrame.width/6*4,selfFrame.height*1.5);
    
    }



    auto dropCircle = Sprite::create(pngCircle);
    dropCircle -> setScale(0.03);
    
    //auto moveY = (-selfFrame.height);
    
//    dropCircle -> setPosition(Vec2( arc4random_uniform(selfFrame.width*3/5)+selfFrame.width/5, selfFrame.height+ dropCircle->getContentSize().height/2));
    dropCircle -> setPosition(dropPosition);
    
    //円に名前を設定
    dropCircle -> setName(dropName);
    dropCircle -> setTag(3);

    //円に物理体を設定
    auto dropMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto dropCircleBody = PhysicsBody::createCircle((dropCircle->getContentSize().width/2)*dropCircle->getScale(),dropMaterial);
    dropCircleBody->setDynamic(true); // 重力の影響を受けない
    dropCircleBody->setCategoryBitmask(0x02);
    //0にすることで衝突しない。
    dropCircleBody->setCollisionBitmask(0);
    dropCircleBody->setContactTestBitmask(0x01);
    dropCircle->setPhysicsBody(dropCircleBody);
    //addChild(dropCircle);
    this -> addChild(dropCircle);
    
    
    //オブジェクトの移動
    //auto moveCircle = MoveTo::create(6, Vec2(dropRing->getPosition().x,moveY));
    
    //auto moveRing = MoveTo::create(6, Vec2(dropRing->getPosition().x,moveY));
    

    
    //dropCircle -> runAction(moveCircle);
    //dropRing -> runAction(moveRing);
    
    
    drops->pushBack(dropCircle);
    
    
    
    
    
}


//1フレーム毎の処理
void GameScene::update(float delta){
    
/*
    //フレームをカウントする。
    if(rigidTappedFlag == true){
        rigidTappedTime++;
    }
    
    if(drops->size() != 0){
        
        //画面上から消えたドロップを削除
        if(drops->at(0)->getParent() == NULL){
            drops->erase(0);
            CCLOG("消したよ");
        }
    }
*/
    
}

#pragma mark-
#pragma mark:ゲームオーバー設定
void GameScene::setGameover(){
/*
 
 
    //落下物の動作停止
    this->unschedule(schedule_selector(GameScene::setDrops));
    
    //すべてのアクションの停止
    this->stopAllActions();
    
    //落下物すべて削除
    for(int idx = 0; idx < drops->size();idx++){

        drops->at(idx)->removeFromParent();
        
    }
    
*/
}


void GameScene::makeGameOver(){
}

void GameScene::removeGameOver(){
}



