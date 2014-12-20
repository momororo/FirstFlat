//
//  GameScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "GameScene.h"
#include <string.h>
#include "LoadScene.h"
#include "NativeCodeLauncher.h"

#define selfFrame Director::getInstance() -> getWinSize()
//30点まではイージーモード
#define easyMode 30
//100点まではノーマルモード
#define normalMode 50


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
    
    //雲の作成
    this->setCloud();
    
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
    
    

    //雲の生成
    auto callback = CallFunc::create(CC_CALLBACK_0(GameScene::setDrops,this));
    auto action = Sequence::create(callback, NULL);
    //実行
    this -> runAction(action);

    
    
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
                    
                    //黄色と紫の時、非表示の場合はそのままreturn;
                    if(umbrella -> getName() == "yellow" || umbrella -> getName() == "purple"){
                        if(umbrella -> isVisible() == false){
                            return;
                        }
                    }
                    
                    
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
    

    if(this -> getChildByName("retryBt") != NULL){

        for (auto iterator : touches) {
            
            
            Touch* touch = iterator;

            //ポイントの取得
            Point touchPoint = Vec2(touch->getLocation());

            //retry
            if(this -> getChildByName("retryBt") ->getBoundingBox().containsPoint(touchPoint)){
                
                //文字列の生成
                auto effectRing = Sprite::create("yellow_ring.png");
                effectRing -> setPosition(this -> getChildByName("retryBt")->getPosition());
                effectRing -> setScale(0.1);
                effectRing -> setTag(2);
                effectRing -> setOpacity(240);
                
                addChild(effectRing);
                
                
                auto ringScale = ScaleBy::create(2, 12);
                auto ringFadeOut = FadeOut::create(2);
                auto ringRemove = RemoveSelf::create(true);
                auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
                auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
                
                effectRing -> runAction(ringSequence);
                
                this -> getChildByName("retryBt") ->runAction(RotateBy::create(1, 360));
                

                
                //アニメーション付き
                float duration = 1.0f;  //開始→終了にかける時間
                Scene* nextScene = CCTransitionFade::create(duration, LoadScene::createScene("GameScene"));
                
                Director::getInstance()->replaceScene(nextScene);

                
                return;
            }
            
            //homeへ
            if(this -> getChildByName("homeBt") -> getBoundingBox().containsPoint(touchPoint)) {
                
                //文字列の生成
                auto effectRing = Sprite::create("purple_ring.png");
                effectRing -> setPosition(this -> getChildByName("homeBt")->getPosition());
                effectRing -> setScale(0.1);
                effectRing -> setTag(2);
                effectRing -> setOpacity(240);
                
                addChild(effectRing);
                
                
                auto ringScale = ScaleBy::create(2, 12);
                auto ringFadeOut = FadeOut::create(2);
                auto ringRemove = RemoveSelf::create(true);
                auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
                auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
                
                effectRing -> runAction(ringSequence);
                
                this -> getChildByName("homeBt") ->runAction(RotateBy::create(1, 360));


                //アニメーション付き
                float duration = 1.0f;  //開始→終了にかける時間
                Scene* nextScene = CCTransitionFade::create(duration, LoadScene::createScene("TitleScene"));
                
                Director::getInstance()->replaceScene(nextScene);

                
            }


        }
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
        
        //スコア加点
        score = score + 10;
        CCLOG("スコアは%d",score);
        //難易度調整ようのメソッドを呼ぶ
        this -> scoreManager();
        
        
        
         
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
        
        if(umbrella->getName() == "yellow" || umbrella->getName() == "purple"){
            
            umbrella -> setVisible(false);
            umbrella -> setOpacity(0);
            
        }
        
        this->addChild(umbrella);
        
        //配列に入れとく
        umbrellas -> pushBack(umbrella);

    }
 
    
}

void GameScene::setCloud(){
    
    for(int idx = 0; idx < colors->size() ; idx++){
        
        //色を抜き出し
        std::string color = *colors->at(idx);
        
        
        //文字列操作
        std::string pngName = color + "_cloud.png";
        //スプライト生成
        auto cloud = Sprite::create(pngName);
        
        cloud -> setScale(0.1);

        
        cloud -> setPosition(Vec2(selfFrame.width/((int)colors->size() + 1)*(idx + 1), selfFrame.height - (cloud->getContentSize().height * cloud->getScale())));


        //dropとの重なり順を考慮
        cloud -> setPositionZ(10);
        
        
        
        cloud -> setName(color + "_cloud");
        
        
        if(cloud->getName() == "yellow_cloud" || cloud->getName() == "purple_cloud"){
            
            cloud -> setVisible(false);
            cloud -> setOpacity(0);
            
        }

        
        
        this->addChild(cloud);
        
        
    }

    
}


#pragma mark-
#pragma mark タイトルに雨を降らせる動作



void GameScene::setDrops(){
    
    //ゲームオーバーの際は再帰せず終了
    if(gameOverFlag == true){
        return;
    }

    
    //対象の雲を決定
    int rnd;


    //難易度で出るドロップを振り分け
    //黄色の雲が見えていない場合はイージーと判定
    if(this -> getChildByName("yellow_cloud") -> getOpacity() != 255){
        
        //0、1、2をランダム
        auto rnd2 = arc4random_uniform(3);
        
        //それぞれの三原色の番号に変換
        switch (rnd2) {
            case 0:
                rnd = 0;
                break;
            case 1:
                rnd = 2;
                break;
            case 2:
                rnd = 4;
                break;
            default:
                break;
        }
        
    }else{
        
        rnd = arc4random_uniform((int)colors->size());
        
    }
    
    
    
    
    //配列から色を抜き取り
    std::string color = *colors->at(rnd);
    
    //サークルの画像名を生成
    std::string pngName = color + "_rain.png";

    auto drop = Sprite::createWithSpriteFrameName(pngName);
    drop -> setScale(0.03);
    drop -> setPosition(Vec2(this -> getChildByName(color + "_cloud")->getPosition().x, this -> getChildByName(color + "_cloud")->getPosition().y));
    
    //円に名前を設定
    drop -> setName(color);
    //タグは3
    drop -> setTag(3);
    
    //雲との重なりを考慮
    drop -> setPositionZ(0);

    //円に物理体を設定
    auto dropMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto dropBody = PhysicsBody::createCircle((drop->getContentSize().width/2)*drop->getScale(),dropMaterial);
    dropBody->setCategoryBitmask(0x02);
    //0にすることで衝突しない。
    dropBody->setCollisionBitmask(0);
    dropBody->setContactTestBitmask(0x01);
    drop->setPhysicsBody(dropBody);
    

    //非表示でかつ重力で落ちないように設定
    drop -> setVisible(false);
    dropBody->setDynamic(true); // 重力の影響を受けない

    
    //addChild(dropCircle);
    this -> addChild(drop);
    
    
    drops->pushBack(drop);
    
//雲のアクションを設定(拡大縮小)

    /*
     スコアに応じて速度を変えること
     if(score >= xx){
        antionTime = xx;
     }
     
     */
    auto actionTime = dropInterval;
    
    auto action1 = ScaleBy::create(actionTime,1.3);
    auto action2 = ScaleBy::create(actionTime,0.76923077);
    
    //拡大縮小のアクション終了後にドロップの設定を変更
    auto startDrop = CallFunc::create([this](){
        
        drops -> at( drops->size() - 1) -> setVisible(true);
        
        drops -> at( drops->size() - 1) -> getPhysicsBody() -> setDynamic(true);
        
    });
    
    //拡大縮小のアクション終了後にドロップの設定を変更
    auto call = CallFunc::create([this](){
        
        
        this -> setDrops();
        
    });

    
    //実行
    this->getChildByName(color + "_cloud") -> runAction(Sequence::create(action1,action2,startDrop,call,NULL));
    
    
    
    return;
    
}

//難易度調整
void GameScene::scoreManager(){
    
    CCLOG("%fだよ",dropInterval);
    auto tmp = 0.05;
    
    //イージーモード中
    if(score < easyMode ){
    
        //出現速度をあげる
        dropInterval = dropInterval - tmp;
        
        return;
    }
    
    
    //イージーモードからノーマルモードへ
    if(score == easyMode){
        
        
        //dropInterval = dropInterval - tmp;
        
        dropInterval = dropInterval - tmp;
        
        this -> getChildByName("yellow_cloud") -> setVisible(true);
        this -> getChildByName("yellow_cloud") -> runAction(FadeIn::create(2));
        
        this -> getChildByName("purple_cloud") -> setVisible(true);
        this -> getChildByName("purple_cloud") -> runAction(FadeIn::create(2));
        
        for(auto umbrella : *umbrellas){
            
            if(umbrella->getName() == "yellow" || umbrella->getName() == "purple"){
                
                umbrella -> setVisible(true);
                umbrella -> runAction(FadeIn::create(2));
                
            }
            
        }
        
        dropInterval = 0.15;

        
        return;
        
    }
    //ノーマルモード中
//    if(score < normalMode){
        
        
//        dropInterval = dropInterval - tmp;
//        return;
//    }
    
    //ノーマルモードからハードモードへ
    if(score == normalMode){


        return;
    }
    

    auto world = this -> getScene() -> getPhysicsWorld();
    auto gravity = world ->getGravity();
    if(gravity.y > -75){
        gravity.y = gravity.y - 1;
    }else{
        dropInterval = dropInterval - 0.005;
    }
    CCLOG("%f",gravity.y);
    world -> setGravity(gravity);


    
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
 
    //ゲームオーバーのフラグをtrue
    gameOverFlag = true;
    
    //落下物の動作停止
    this->stopAllActions();
    
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
    
    
    
    mgoCount = 0;
    
    //傘の処理(黒に変色後→点滅→削除)
    for (int idx = 0; idx < umbrellas->size();idx++) {

        umbrellas->at(idx)->setColor(Color3B::BLACK);
        this -> getChildByName(umbrellas->at(idx)->getName() + "_cloud")->setColor(Color3B::BLACK);
        
        
        auto blink = Blink::create(3, 3);
        
        auto fadeOut = FadeOut::create(1);
        
        auto remove = RemoveSelf::create();

        
        auto mgo = CallFunc::create([&](){
            
            mgoCount ++;
            CCLOG("%d",mgoCount);
            
            if (mgoCount == 5) {
            
                makeGameOver();
                
            }
            
        });
        
        auto seq = Sequence::create(blink,fadeOut,mgo,remove, NULL);
        auto seq2 = Sequence::create(blink->clone(),fadeOut->clone(),remove->clone(), NULL);
        
        umbrellas -> at(idx) -> runAction(seq);
 
        this -> getChildByName(umbrellas->at(idx)->getName() + "_cloud")-> runAction(seq2);
    }
    
    
    
    

}


void GameScene::makeGameOver(){
    
    //背景色の変更
    auto bgGradient = LayerGradient::create(Color4B(128,229,255,255), Color4B(95,211,188,255));
    this -> addChild(bgGradient);
    
    //ゲームオーバーテキスト
    auto gameOverLabel = Label::createWithSystemFont("ゲーム\nオーバー","jackeyfont", 120);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*3/4));
    gameOverLabel -> setColor(Color3B::BLACK);
    this -> addChild(gameOverLabel,10);
        
    //テキスト用の傘スプライト
    auto umbrella = Sprite::create("umbrella.png");
    //umbrella -> setAnchorPoint(Vec2(1,1));
    umbrella -> setColor(Color3B::BLACK);
    umbrella -> setScale(0.08);
    umbrella-> setPosition(Vec2(selfFrame.width*3/4,selfFrame.height*3/4+(umbrella->getContentSize().height/2)*umbrella->getScale()));
    addChild(umbrella);
    
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
    
    auto retryBt = Sprite::create("retryBt.png");
    retryBt -> setPosition(Vec2(selfFrame.width*3/4,selfFrame.height/3));
    retryBt -> setScale(0.2);
    retryBt -> setName("retryBt");
    this->addChild(retryBt,10);
    

    
    auto homeBt = Sprite::create("homeBt.png");
    homeBt ->  setPosition(Vec2(selfFrame.width*1/4,selfFrame.height/3));
    homeBt -> setScale(0.2);
    homeBt -> setName("homeBt");
    this -> addChild(homeBt,10);
    
    
    
    /******** ラベル＆リトライ＆ホームボタンの設定 終 *******/
    
    
    //MARK::スコア

    //スコアの取り出し
    UserDefault *userDef = UserDefault::getInstance();
    auto bestScore = userDef -> getIntegerForKey("bestScore");

    

    //宣言だけ
    Label *omedeto;
    
    if(bestScore < score){
        
        bestScore = score;
        
        //登録
        userDef->setIntegerForKey("bestScore", bestScore);

        omedeto = Label::createWithSystemFont("Best Score!!", "jackeyfont", 60);
        omedeto -> setPosition(Vec2(selfFrame.width/2,gameOverLabel->getPositionY() - gameOverLabel -> getContentSize().height/2 - omedeto -> getContentSize().height));
        omedeto ->setColor(Color3B::RED);
        this->addChild(omedeto);
        
        auto blink = Blink::create(1, 1);
        
        auto repeat = RepeatForever::create(blink);
        
        omedeto -> runAction(repeat);
        

       //スコア送信
        NativeCodeLauncher::postHighScore("RainDrop", bestScore);
    }
    
    
    auto resultLabel = Label::createWithSystemFont("SCORE", "jackeyfont", 70);
    resultLabel ->setPosition(Vec2(selfFrame.width/2,omedeto->getPositionY() - omedeto -> getContentSize().height/2 - resultLabel -> getContentSize().height/2));
    resultLabel -> setColor(Color3B::GRAY);
    this -> addChild(resultLabel);

    
    std::string scoreStr = StringUtils::format("%d",score);
    auto result = Label::createWithSystemFont(scoreStr/*.c_str()*/, "jackeyfont", 70);
    result ->setPosition(Vec2(selfFrame.width/2,resultLabel->getPositionY() - resultLabel -> getContentSize().height/2 - result -> getContentSize().height/2));
    result -> setColor(Color3B::BLACK);
    this -> addChild(result);
    
    

     
    /*
    //MARK::nend飛だし広告の表示
    NendInterstitialModule::showNADInterstitialView();
    setAppCCloud();
    
    */
    
}

void GameScene::removeGameOver(){
}



