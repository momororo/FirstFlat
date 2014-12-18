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
    
    auto world = scene -> getPhysicsWorld();
    cocos2d::Vect gravity;
    gravity.setPoint(0, -30);
    world -> setGravity(gravity);
    
    
    
    
    
    
    
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
    colors->push_back(new std::string("yellow"));
    colors->push_back(new std::string("blue"));
    colors->push_back(new std::string("purple"));
    colors->push_back(new std::string("red"));
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("rainAndCircle.plist");
        
    
    
    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(255,255,255,255), Color4B(255,255,255,255));
    this -> addChild(bgGradient);
    

    //ボタンの生成
    this->setUmbrella();
    
    gameOverFlag = false;
    
    
    
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
    this -> schedule(schedule_selector(GameScene::setDrops), 1);
    
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
    
    
    
    if (gameOverFlag == false) {
        
        //ループ(マルチタップ用)
        for (auto iterator : touches) {
            
            
            Touch* touch = iterator;
            //ポイントの取得
            Point touchPoint = Vec2(touch->getLocation());
            
            //アンブレラ配列の中から走査
            for (auto umbrella : *umbrellas) {
                
                if(umbrella->getBoundingBox().containsPoint(touchPoint)){
                    
                    //ダブルタップの制限を超えたら処理せず終
                    if(tappedCount >= 2){
                        tappedCount = 0;
                        return;
                    }
                    
                    
                    //リングを広げる処理へ
                    //前回タップと同じ色か確認(同じならreturn)
                    if(tappedName == umbrella -> getName()){
                        return;
                    }
                    
                    //文字列の生成
                    std::string pngName = umbrella->getName() + "_ring.png";
                    auto effectRing = Sprite::create(pngName);
                    effectRing -> setPosition(umbrella->getPosition());
                    effectRing -> setScale(0.1);
                    effectRing -> setName(umbrella->getName());
                    effectRing -> setTag(2);
                    effectRing -> setOpacity(240);
                    
                    
                    //物理体の生成
                    auto ringMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
                    auto ringBody = PhysicsBody::createCircle((effectRing->getContentSize().width/2)*effectRing->getScale(),ringMaterial);
                    ringBody->setDynamic(false); // 重力の影響を受けない
                    ringBody->setEnable(true);
                    
                    ringBody->setCategoryBitmask(0x01);
                    ringBody->setCollisionBitmask(0);
                    ringBody->setContactTestBitmask(0x02);
                    effectRing->setPhysicsBody(ringBody);
                    
                    addChild(effectRing);
                    
                    
                    auto ringScale = ScaleBy::create(2, 12);
                    auto ringFadeOut = FadeOut::create(2);
                    auto ringRemove = RemoveSelf::create(true);
                    auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
                    auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
                    
                    effectRing -> runAction(ringSequence);
                    
                    umbrella ->runAction(RotateBy::create(1, 360));
                    
                    tappedName = effectRing->getName();
                    
                    rigidTappedFlag = true;
                    tappedCount++;
                    
                }//if文
                
                
            }//for文
            
        }//while文
    }
    
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
        gameOverFlag = true;
        this->setGameover();
        
        return true;
    }
    
    //サークルとドロップの衝突と判断
    if(nodeA->getName() == nodeB->getName()){
     
        //一致(スコアアップ、サークル発生)
        CCLOG("一致しました");
        
        
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
        
        
        auto pngName = dropCircle->getName() + "_ring.png";
        
        //輪の設定
        auto dropRing = Sprite::createWithSpriteFrameName(pngName);
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
        //配列から削除
        dropRing -> runAction(moveScale);
        
        
         
        return true;
        
         
    }else{
        
        //不一致(ゲームオーバー)
        CCLOG("ゲームオーバー");
        
        gameOverFlag = true;

        this->setGameover();
        
        
        return true;
    }
    
    return true;
}


void GameScene::setUmbrella(){
    
    
    for(int idx = 0; idx < colors->size() ; idx++){
        
        //色を抜き出し
        std::string color = *colors->at(idx);
        
        
        //文字列操作
        std::string pngName = color + "_umbrella.png";
        //スプライト生成
        auto umbrella = Sprite::create(pngName);
        
        umbrella -> setPosition(Vec2(selfFrame.width/((int)colors->size() + 1)*(idx + 1), selfFrame.height/6));

        umbrella -> setScale(0.1);
        
        
        umbrella -> setName(color);
        
        umbrella -> setTag(1);

        PhysicsMaterial umbrellaMaterial;
        
        //auto greenMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto umbrellaBody = PhysicsBody::createCircle((umbrella->getContentSize().width/2)*umbrella->getScale(),umbrellaMaterial);
        umbrellaBody->setDynamic(false); // 重力の影響を受けない
        umbrellaBody->setEnable(true);
        
        umbrellaBody->setCategoryBitmask(0x01);
        umbrellaBody->setCollisionBitmask(0);
        umbrellaBody->setContactTestBitmask(0x02);
        
        umbrella->setPhysicsBody(umbrellaBody);
        
        this->addChild(umbrella);
        
        //配列に入れとく
        umbrellas -> pushBack(umbrella);

    }
 
    
}

#pragma mark-
#pragma mark タイトルに雨を降らせる動作


void GameScene::setDrops(float time){
    
    auto rnd = arc4random_uniform((int)colors->size());
    
    //配列から色を抜き取り
    std::string color = *colors->at(rnd);
    
    //サークルの画像名を生成
    std::string pngName = color + "_rain.png";

    auto dropCircle = Sprite::createWithSpriteFrameName(pngName);
    dropCircle -> setScale(0.03);
    dropCircle -> setPosition(Vec2(selfFrame.width/((int)colors->size() + 1) * (rnd + 1 ), selfFrame.height*1.5));
    
    //円に名前を設定
    dropCircle -> setName(color);
    //タグは3
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
    
    
    drops->pushBack(dropCircle);
    
    
}


//1フレーム毎の処理
void GameScene::update(float delta){
  
    
    //不要なスプライトの除去
    removeSprite();

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

void GameScene::removeSprite(){
    
    //ドロップの消去
    if(drops->size() > 0 && gameOverFlag == false){
        
        //途中で消された残骸用
        if(drops->at(0)->getParent() == NULL){

            //配列から削除
            drops->erase(0);
            
            
        }

        //デバッグ用
        /*if(drops->at(0)->getPositionY() < 0){
            
            auto drop = drops->at(0);
            
            //配列から削除
            drops->erase(0);

            //親から削除
            drop->removeFromParentAndCleanup(true);
            
        }*/
        
    }
    
}

#pragma mark-
#pragma mark:ゲームオーバー設定
void GameScene::setGameover(){
 
    //落下物の動作停止
    this->unschedule(schedule_selector(GameScene::setDrops));
    
    //最後にぶつかったdropsの輪のエフェクトオブジェクト
    auto dropRing = Sprite::create("red_ring.png");
    dropRing -> setPosition(Vec2(drops->at(0)->getPosition().x,drops->at(0)->getPosition().y));
    dropRing -> setColor(Color3B::BLACK);
    dropRing -> setScale(0.01);
    addChild(dropRing);
    
    //オブジェクトの拡大
    auto scale = ScaleBy::create(2, 12);
    //オブジェクトの削除
    auto remove = RemoveSelf::create(true);
    //オブジェクトのフェードアウト
    auto fadeOut = FadeOut::create(2);
    
    //拡大・フェードアウト同時アクション
    auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
    //拡大→削除のアクション
    auto moveScale = Sequence::create(scaleFadeOut,remove,NULL);
    //アクション開始
    dropRing -> runAction(moveScale);
    
    
    //落下物すべて削除
    for(int idx = 0; idx < drops->size();idx++){

        drops->at(idx)->removeFromParent();
                
    }
    
    int count = 0;
    //傘の処理(黒に変色後→点滅→削除)
    for (int idx = 0; idx < umbrellas->size();idx++) {

        umbrellas->at(idx)->setColor(Color3B::BLACK);
        
        auto blink = Blink::create(3, 3);
        
        auto fadeOut = FadeOut::create(1);
        
        auto remove = RemoveSelf::create();

        
        auto mgo = CallFunc::create([&](){
            
            count ++;
            
            if (count == 5) {
            
                makeGameOver();
                
            }
            
        });
        
        auto seq = Sequence::create(blink,fadeOut,mgo,remove, NULL);
        
        umbrellas -> at(idx) -> runAction(seq);
 
    }
    
    
    
    

}


void GameScene::makeGameOver(){
    
    /******** ラベル＆リトライ＆ホームボタンの設定 *******/
    
    auto gameOverLabel = Label::createWithSystemFont("GAME OVER","DragonQuestFC", 120);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverLabel -> setColor(Color3B::BLACK);
    this -> addChild(gameOverLabel,10);
    
    CCLOG("テキストx:%f, y:%f",gameOverLabel->getPosition().x,gameOverLabel->getPosition().y);
    
    
    /*********************************************/
    /*
    gameOverRing = Sprite::create("titleRing.png");
    gameOverRing -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/5));
    gameOverRing -> setColor(blue);
    gameOverRing -> setScale(1.7);
    
    this -> addChild(gameOverRing,0);
    
    auto tintpurple = TintTo::create(1,229, 128, 255);
    auto tintRed = TintTo::create(1,255, 85, 85);
    auto tintYellow = TintTo::create(1,255, 221, 85);
    auto tintGreen = TintTo::create(1,85, 255, 85);
    auto tintAqoa = TintTo::create(1,42, 212, 255);
    auto tintBlue = TintTo::create(1,42, 127, 255);
    
    auto sequence = Sequence::create(tintpurple,tintRed,tintYellow,tintGreen,tintAqoa,tintBlue, NULL);
    
    auto repeat = RepeatForever::create(sequence);
    
    gameOverRing ->runAction(repeat);
    */
    /*******************************************************************/
    
    auto retryBt = Sprite::create("yellow_umbrella.png");
    retryBt -> setPosition(Vec2(selfFrame.width*3/4,selfFrame.height/3));
    retryBt -> setScale(0.1);
    this->addChild(retryBt,10);
    
    auto homeBt = Sprite::create("purple_umbrella.png");
    homeBt ->  setPosition(Vec2(selfFrame.width*1/4,selfFrame.height/3));
    homeBt -> setScale(0.1);
    this -> addChild(homeBt,10);
    
    
    
    /******** ラベル＆リトライ＆ホームボタンの設定 終 *******/
    
    
    //MARK::スコア登録
    /*
    if(bestScore < score){
        
        bestScore = score;
        
        //登録
        userDef->setIntegerForKey("bestScore", bestScore);
        omedeto = Label::createWithSystemFont("Best Score!!", KODOMO_FONT, 60);
        omedeto -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
        omedeto ->setColor(red);
        this->addChild(omedeto);
        
        auto blink = Blink::create(1, 1);
        
        auto repeat = RepeatForever::create(blink);
        
        omedeto -> runAction(repeat);
        
        newRecord = true;
        
        GameCenterBridge::postHighScore("RGB.BestScore", bestScore);
    }
    
    std::string scoreStr = StringUtils::format("%d",score);
    result = Label::createWithSystemFont(scoreStr.c_str(), KODOMO_FONT, 100);
    result ->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    result -> setColor(Color3B::GRAY);
    this -> addChild(result);
    
    
    resultLabel = Label::createWithSystemFont("SCORE", KODOMO_FONT, 100);
    resultLabel ->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2+result->getContentSize().height));
    resultLabel -> setColor(Color3B::GRAY);
    this -> addChild(resultLabel);
    
    gameOver = true;
    */
     
    /*
    //MARK::nend飛だし広告の表示
    NendInterstitialModule::showNADInterstitialView();
    setAppCCloud();
    
    */
    
}

void GameScene::removeGameOver(){
}



