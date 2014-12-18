//
//  TitleScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "TitleScene.h"
//#include "GameScene.h"
#include "LoadScene.h"
#include "NativeCodeLauncher.h"
//#include "NendModule.h"
//#include "NendInterstitialModule.h"
//#include "AppCCloudPlugin.h"


#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;

Sprite *circle;
Sprite *ring;
Label *titleLabel;

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
    
    //面倒なので配列多用
    menus->push_back(new std::string("start"));
    menus->push_back(new std::string("ranking"));
    menus->push_back(new std::string("tutorial"));

    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(128,229,255,255), Color4B(95,211,188,255));
    this -> addChild(bgGradient);
   
    
    this -> schedule(schedule_selector(TitleScene::setDrops), 1);
    
    presetSprite();
    
    //各種タイトルの設定
    setTitle();
    setStart();
    setRanking();
    setTutorial();

    auto umbrella = Sprite::create("umbrella.png");
    umbrella -> setAnchorPoint(Vec2(1,1));
    umbrella -> setScale(0.08);
    umbrella-> setPosition(Vec2(selfFrame.width*14/15,selfFrame.height*4/5));
    //umbrella -> setOpacity(0);
    this-> addChild(umbrella,10);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("low_bFlat.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("low_c.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("low_d.mp3");

 
 
    
    
    
    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(TitleScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(TitleScene::onTouchCancelled,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    
    
    //MARK::nendの設定
    //ネンドの呼び出し(ヘッダー)
    /*char apiKey[] = "5aa579f521da85a055c5076641efc68202d5e8e2";
     char spotID[] = "262876";
     NendModule::createNADViewBottom(apiKey, spotID);
     
     //ネンドの呼び出し(飛び出す)
     char interstitialApiKey[] = "6b027f392e0cf11d378908fc4027f1755d6422ad";
     char interstitialSpotID[] = "266067";
     NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
     */
    
    

    
    
    //GameCenterのログイン
    NativeCodeLauncher::loginGameCenter();
    
    
    return true;
    
    
}


//MARK::AppCCloudの設定と削除
/*
 void TitleScene::setAppCCloud(){
 
 appCCloudBt = Sprite::create("other.png");
 appCCloudBt -> setPosition(Vec2((selfFrame.width)-(appCCloudBt->getContentSize().width*2/3),(selfFrame.height)-(appCCloudBt->getContentSize().height*2/3)));
 this -> addChild(appCCloudBt);
 
 appFlag = true;
 
 }
 
 void TitleScene::removeAppCCloud(){
 
 appCCloudBt -> removeFromParent();
 
 appFlag = false;
 
 }
 */



#pragma mark-
#pragma mark touchBegan

bool TitleScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    
    //スタートボタンが存在するかで、ボタンがあるか表示されているか確認
     if (this->getChildByName(*menus->at(0))->isVisible() == false) {
        
        return true;
        
    }

    //ポイント取得
    Point touchPoint = Vec2(touch->getLocation());

    //メニューの押下処理(かさぐるぐる)
    for(auto menu : *menus){
        
        if (this->getChildByName(*menu)->getBoundingBox().containsPoint(touchPoint)){
 
            auto repeatForever = RepeatForever::create(RotateBy::create(1, 360));
            this ->getChildByName(*menu)->runAction(repeatForever);
 
            return true;
            
        }
        
    }
    
    return true;

}


#pragma mark-
#pragma mark touchMoved

void TitleScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スタートボタンが存在するかで、ボタンがあるか表示されているか確認
    if (this->getChildByName(*menus->at(0))->isVisible() == false) {
        
        return;
        
    }
    
    //ポイント取得
    Point touchPoint = Vec2(touch->getLocation());
    
    //ボタンが回転している(アクションがある)→ボタンの位置にいない→アクションを止める
    for(auto menu : *menus){

        if (this->getChildByName(*menu)->getNumberOfRunningActions() != 0){

            
            if (!this->getChildByName(*menu)->getBoundingBox().containsPoint(touchPoint)){
                
                this->getChildByName(*menu)->stopAllActions();

                
            }

            return;
            
        }
        
    }
    
    return;
    
}


#pragma mark-
#pragma mark touchEnded

void TitleScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //スタートボタンが存在するかで、ボタンがあるか表示されているか確認
    if (this->getChildByName(*menus->at(0))->isVisible() == false) {
        
        return;
        
    }
    
    //ポイント取得
    Point touchPoint = Vec2(touch->getLocation());
    
    //ボタンが回転している(アクションがある)→ボタンの位置にいる→画面遷移
    for(auto menu : *menus){
        
        if (this->getChildByName(*menu)->getNumberOfRunningActions() != 0){
            
            
            if (this->getChildByName(*menu)->getBoundingBox().containsPoint(touchPoint)){
                
                
                auto repeatForever = RepeatForever::create(RotateBy::create(1, 360));
                this ->getChildByName(*menu)->runAction(repeatForever);
                
                //押下後の処理へ
                tappedBt(*menu);

                
                
            }
            
            return;
            
        }
        
    }
    
}


#pragma mark-
#pragma mark touchCancelled

void TitleScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    //タッチキャンセル
    CCLOG("touchCancelled");
    
}

#pragma mark-
#pragma mark ボタンタップ後の処理

//ボタンタップ後の処理
void TitleScene::tappedBt(std::string &menu){
    
    //スタートの処理
    if(menu == "start"){
        

  
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        this -> getChildByName("startEffectRing") -> setVisible(true);
        this -> getChildByName("startEffectRing") -> runAction(ringSequence);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("low_c.mp3");
   
        
        //アニメーション付き
        float duration = 1.0f;  //開始→終了にかける時間
        Scene* nextScene = CCTransitionFade::create(duration, LoadScene::createScene());
        
        Director::getInstance()->replaceScene(nextScene);
      
        return;
        
    }

    //ランキングの処理
    if(menu == "ranking"){
        
        
        /**
         *  おそらくリングを再生成して、傘の動きを止める処理の実装が必要かと思われ。
         */
        return;
    }

    //チュートリアルの処理
    if(menu == "tutorial"){
        
        //長くなるなら更に別メソッドを呼ぶほうが良いかも
        
        
        /**
         *　チュートリアル終了後
         *  再度タイトルシーンを呼ぶ場合は特に気をつける処理はなし
         */
     
        
        return;
    }
    
    
}


#pragma mark-
#pragma mark オープニング動作

/***********************************************************
                各種オープニングの動作設定
 **********************************************************/

//プリセット
void TitleScene::presetSprite(){

    //タイトル効果
    auto titleRain = Sprite::create("yellow_rain.png");
    titleRain -> setPosition(Vec2(selfFrame.width/2,selfFrame.height + 200));
    titleRain -> setScale(0.1);
    titleRain -> setVisible(false);
    titleRain -> setName("titleRain");
    this->addChild(titleRain);
    
    //タイトル
    titleLabel = Label::createWithSystemFont("レイン\nドロップ","jackeyfont",120);
    titleLabel -> setPosition(Vec2(selfFrame.width/2, selfFrame.height*2/3));
    titleLabel->setOpacity(0);
    titleLabel->setVisible(false);
    titleLabel->setName("titleLabel");
    this->addChild(titleLabel,10);
    
    //タイトルリング
    auto titleRing = Sprite::create("yellow_ring.png");
    titleRing -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    titleRing -> setScale(0.1);
    titleRing ->setVisible(false);
    titleRing ->setName("titleRing");
    this->addChild(titleRing);
    
    //スタートボタン効果
    auto startRain = Sprite::create("blue_rain.png");
    startRain -> setPosition(Vec2(selfFrame.width/2,selfFrame.height+100));
    startRain -> setScale(0.1);
    startRain -> setVisible(false);
    startRain -> setName("startRain");
    this -> addChild(startRain);
    
    //スタートボタン
    auto startBt = Sprite::create("blue_umbrella.png");
    startBt -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/6));
    startBt -> setScale(0.1);
    startBt -> setOpacity(0);
    startBt -> setVisible(false);
    startBt -> setName("start");
    addChild(startBt,10);
    
    auto startLabel = Label::createWithSystemFont("スタート","DragonQuestFC",30);
    startLabel -> setPosition(Vec2(startBt->getPosition().x, startBt->getPosition().y));
    startLabel -> setVisible(false);
    startLabel -> setName("startLabel");
    addChild(startLabel,10);
    
    //スタートリング
    auto startRing = Sprite::create("blue_ring.png");
    startRing -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/6));
    startRing -> setScale(0.1);
    startRing -> setVisible(false);
    startRing -> setName("startRing");
    this->addChild(startRing);
    CCLOG("りんぐx:%f,y:%f",startRing->getPosition().x,startRing->getPosition().y);
    
    //スタートボタンをタップした時のエフェクト効果
    auto startBtEffect = Sprite::create("blue_ring.png");
    startBtEffect -> setPosition(Vec2(this->getChildByName("start")->getPosition()));
    startBtEffect -> setScale(0.1);
    startBtEffect -> setVisible(false);
    startBtEffect -> setName("startBtEffect");
    this-> addChild(startBtEffect);

    

    //ランキングボタン効果
    auto rankingRain = Sprite::create("green_rain.png");
    rankingRain -> setPosition(Vec2(60,selfFrame.height+100));
    rankingRain -> setScale(0.1);
    rankingRain -> setVisible(false);
    rankingRain -> setName("rankingRain");
    this->addChild(rankingRain);
    
    
    //ランキング
    ranking = Sprite::create("green_umbrella.png");
    ranking -> setPosition(Vec2(60,selfFrame.height/4));
    ranking -> setScale(0.1);
    ranking -> setOpacity(0);
    ranking -> setVisible(false);
    ranking -> setName("ranking");
    addChild(ranking,10);
    
    auto rankingLabel = Label::createWithSystemFont("ランキング","DragonQuestFC",30);
    rankingLabel -> setPosition(Vec2(ranking->getPosition().x, ranking->getPosition().y));
    rankingLabel -> setVisible(false);
    rankingLabel -> setName("rankingLabel");
    addChild(rankingLabel,10);
    
    //ランキングリング
    auto rankingRing = Sprite::create("green_ring.png");
    rankingRing -> setPosition(Vec2(60,selfFrame.height/6));
    rankingRing -> setScale(0.1);
    rankingRing -> setVisible(false);
    rankingRing -> setName("rankingRing");
    addChild(rankingRing);

    
    // チュートリアル効果
    auto tutorialRain = Sprite::create("red_rain.png");
    tutorialRain -> setPosition(Vec2(selfFrame.width-60,selfFrame.height+100));
    tutorialRain -> setScale(0.1);
    tutorialRain -> setVisible(false);
    tutorialRain -> setName("tutorialRain");
    this->addChild(tutorialRain);
    
    //チュートリアル
    tutorial = Sprite::create("red_umbrella.png");
    tutorial -> setPosition(Vec2(selfFrame.width-60,selfFrame.height/4));
    tutorial -> setScale(0.1);
    tutorial -> setOpacity(0);
    tutorial -> setVisible(false);
    tutorial -> setName("tutorial");
    addChild(tutorial,10);
    
    auto tutorialLabel = Label::createWithSystemFont("あそびかた","DragonQuestFC",30);
    tutorialLabel -> setPosition(Vec2(tutorial->getPosition().x, tutorial->getPosition().y));
    tutorialLabel ->setVisible(false);
    tutorialLabel -> setName("tutorialLabel");
    addChild(tutorialLabel,10);

    //チュートリアルリング
    auto tutorialRing = Sprite::create("red_ring.png");
    tutorialRing -> setPosition(Vec2(selfFrame.width-60,selfFrame.height/6));
    tutorialRing -> setScale(0.1);
    tutorialRing -> setVisible(false);
    tutorialRing -> setName("tutorialRing");
    this->addChild(tutorialRing);
    
    //ボタン押下後の波紋
    auto startEffectRing = Sprite::create("blue_ring.png");
    startEffectRing -> setPosition(Vec2(this->getChildByName("start")->getPosition().x,this->getChildByName("start")->getPosition().y));
    startEffectRing -> setScale(0.1);
    startEffectRing -> setVisible(false);
    startEffectRing -> setName("startEffectRing");
    this -> addChild(startEffectRing);

    auto rankingEffectRing = Sprite::create("green_ring.png");
    rankingEffectRing -> setPosition(Vec2(this->getChildByName("ranking")->getPosition().x,this->getChildByName("ranking")->getPosition().y));
    rankingEffectRing -> setScale(0.1);
    rankingEffectRing -> setVisible(false);
    rankingEffectRing -> setName("rankingEffectRing");
    this -> addChild(rankingEffectRing);

    auto tutorialEffectRing = Sprite::create("red_ring.png");
    tutorialEffectRing -> setPosition(Vec2(this->getChildByName("tutorial")->getPosition().x,this->getChildByName("tutorial")->getPosition().y));
    tutorialEffectRing -> setScale(0.1);
    tutorialEffectRing -> setVisible(false);
    tutorialEffectRing -> setName("tutorialEffectRing");

    this -> addChild(tutorialEffectRing);

    
    //アンブレラ
    auto umbrella = Sprite::create("umbrella.png");
    umbrella -> setAnchorPoint(Vec2(1,1));
    umbrella -> setScale(0.08);
    umbrella-> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    umbrella -> setOpacity(0);
    umbrella -> setVisible(false);
    umbrella -> setName("umbrella");
    addChild(umbrella);
    
}



//オープニングのタイトルの動作
void TitleScene::setTitle(){
 
    //オブジェクトの移動
    auto move = MoveTo::create(2, Vec2(selfFrame.width/2,selfFrame.height*2/3));
    
    //オブジェクトの削除
    auto remove = RemoveSelf::create(true);
    
    //タイトルフェードイン
    auto func = CallFunc::create([this](){
        
        this -> fadeInTitle();
        
        //オブジェクトの拡大
        auto scale = ScaleBy::create(2, 12);
        //オブジェクトのフェードアウト
        auto fadeOut = FadeOut::create(2);
        
        auto remove = RemoveSelf::create(true);
        
        //拡大・フェードアウト同時アクション
        auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
        
        //拡大後削除のアクション
        auto moveScale = Sequence::create(scaleFadeOut,remove,NULL);
        
        this->getChildByName("titleRing") -> setVisible(true);
        
        this->getChildByName("titleRing") -> runAction(moveScale);
        
    });
    
    //移動後削除のアクション
    auto moveRemove = Sequence::create(move,remove,func,NULL);

    this->getChildByName("titleRain") -> setVisible(true);
    this->getChildByName("titleRain") -> runAction(moveRemove);
    
}



//オープニングのスタート動作
void TitleScene::setStart(){
        
     //オブジェクトの移動
     auto move = MoveTo::create(2, Vec2(selfFrame.width/2,selfFrame.height/6));
     
     //オブジェクトの削除
     auto remove = RemoveSelf::create(true);
     
     //タイトルフェードイン
     auto func = CallFunc::create([this](){
         
         this -> fadeInStart();
         
         
         //オブジェクトの拡大
         auto scale = ScaleBy::create(2, 12);
         //オブジェクトのフェードアウト
         auto fadeOut = FadeOut::create(2);
     
         auto remove = RemoveSelf::create(true);
     
         //拡大・フェードアウト同時アクション
         auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
     
         //拡大後削除のアクション
         auto moveScale = Sequence::create(scaleFadeOut,remove,NULL);
     
         this->getChildByName("startRing") -> setVisible(true);
         
         this->getChildByName("startRing") -> runAction(moveScale);
     
     });
     
     //移動後削除のアクション
     auto moveRemove = Sequence::create(move,remove,func,NULL);
     
    this->getChildByName("startRain") -> setVisible(true);
    this->getChildByName("startRain") -> runAction(moveRemove);

}



//オープニングのランキング動作
void TitleScene::setRanking(){
    
    
    
    //オブジェクトの移動
    auto move = MoveTo::create(2, Vec2(60,selfFrame.height/6));
    
    //オブジェクトの削除
    auto remove = RemoveSelf::create(true);
    
    //タイトルフェードイン
    auto func = CallFunc::create([this](){
        
        this -> fadeInRanking();
        
    
        
        //オブジェクトの拡大
        auto scale = ScaleBy::create(2, 12);
        //オブジェクトのフェードアウト
        auto fadeOut = FadeOut::create(2);
        
        auto remove = RemoveSelf::create(true);
        
        //拡大・フェードアウト同時アクション
        auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
        
        //拡大後削除のアクション
        auto moveScale = Sequence::create(scaleFadeOut,remove,NULL);
        
        this->getChildByName("rankingRing") -> setVisible(true);
        
        this->getChildByName("rankingRing") -> runAction(moveScale);
        
    });
    
    //移動後削除のアクション
    auto moveRemove = Sequence::create(move,remove,func,NULL);
    
    this->getChildByName("rankingRain") -> setVisible(true);
    this->getChildByName("rankingRain") -> runAction(moveRemove);
    
}


//オープニングのチュートリアル動作
void TitleScene::setTutorial(){
    
    
    //オブジェクトの移動
    auto move = MoveTo::create(2, Vec2(selfFrame.width-60,selfFrame.height/6));
    
    //オブジェクトの削除
    auto remove = RemoveSelf::create(true);
    
    //チュートリアルフェードイン
    auto func = CallFunc::create([this](){
        
        this -> fadeInTutorial();
        
        
        
        //オブジェクトの拡大
        auto scale = ScaleBy::create(2, 12);
        //オブジェクトのフェードアウト
        auto fadeOut = FadeOut::create(2);
        
        auto remove = RemoveSelf::create(true);
        
        //拡大・フェードアウト同時アクション
        auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
        
        //拡大後削除のアクション
        auto moveScale = Sequence::create(scaleFadeOut,remove,NULL);
        
        this->getChildByName("tutorialRing") -> setVisible(true);
        
        this->getChildByName("tutorialRing") -> runAction(moveScale);

    });
    
    //移動後削除のアクション
    auto moveRemove = Sequence::create(move,remove,func,NULL);
    
    this->getChildByName("tutorialRain") -> setVisible(true);
    this->getChildByName("tutorialRain") -> runAction(moveRemove);
    
}

/***********************************************************
                各種オープニングの動作設定　終
 **********************************************************/



#pragma mark-
#pragma mark タイトル等ボタン設定


/***********************************************************
                タイトル,各種ボタン設定
 **********************************************************/

//タイトルのフェードイン表示
void TitleScene::fadeInTitle(){

    this -> getChildByName("titleLabel") -> setVisible(true);
    this -> getChildByName("titleLabel") -> runAction(FadeIn::create(2));
    
    /*
    auto umbrella = Sprite::create("umbrella.png");
    umbrella -> setAnchorPoint(Vec2(1,1));
    umbrella -> setScale(0.08);
    umbrella-> setPosition(Vec2(selfFrame.width/2+titleLabel->getContentSize().width*2/3,selfFrame.height*2/3+titleLabel->getContentSize().height*2/5));
    umbrella -> setOpacity(0);
    addChild(umbrella);
    umbrella -> runAction(FadeIn::create(2));
    */
}

void TitleScene::fadeInUmbrella(){
    

    this -> getChildByName("umbrella") -> setVisible(true);
    this -> getChildByName("umbrella") -> runAction(FadeIn::create(2));

}

//スタートのフェードイン表示
void TitleScene::fadeInStart(){

    this -> getChildByName("start") -> setVisible(true);
    this -> getChildByName("start") -> runAction(FadeIn::create(2));

    this -> getChildByName("startLabel") -> setVisible(true);
    this -> getChildByName("startLabel") -> runAction(FadeIn::create(2));


}

//ランキングのフェードイン表示
void TitleScene::fadeInRanking(){
    

    this -> getChildByName("ranking") -> setVisible(true);
    this -> getChildByName("ranking") -> runAction(FadeIn::create(2));
    
    this -> getChildByName("rankingLabel") -> setVisible(true);
    this -> getChildByName("rankingLabel") -> runAction(FadeIn::create(2));

}

//チャレンジのフェードイン表示
void TitleScene::fadeInTutorial(){

    this -> getChildByName("tutorial") -> setVisible(true);
    this -> getChildByName("tutorial") -> runAction(FadeIn::create(2));
    
    this -> getChildByName("tutorialLabel") -> setVisible(true);
    this -> getChildByName("tutorialLabel") -> runAction(FadeIn::create(2));

    
}
/***********************************************************
                タイトル,各種ボタン設定　終
 **********************************************************/




#pragma mark-
#pragma mark タイトルに雨を降らせる動作


void TitleScene::setDrops(float time){
    
    auto rnd = arc4random_uniform(5);
    
    std::string pngCircle;
    std::string pngRing;
    
    if (rnd == 0) {
        
        pngCircle = "aqua_rain.png";
        pngRing = "aqua_ring.png";
        
    }else if(rnd == 1){
        
        pngCircle = "green_rain.png";
        pngRing = "green_ring.png";
    
    }else if(rnd == 2){
    
        pngCircle = "yellow_rain.png";
        pngRing = "yellow_ring.png";
        
    }else if(rnd == 3){
    
        pngCircle = "blue_rain.png";
        pngRing = "blue_ring.png";
        
    }else if (rnd == 4){
        
        pngCircle = "red_rain.png";
        pngRing = "red_ring.png";
    
    }
    
    
    auto moveY = (arc4random_uniform(selfFrame.height*2/5)+selfFrame.height/2);
    
    
    //輪の設定
    auto dropRing = Sprite::create(pngRing);
    dropRing -> setScale(0.01);
    dropRing -> setPosition(Vec2( arc4random_uniform(selfFrame.width*3/5)+selfFrame.width/5, selfFrame.height+ dropRing->getContentSize().height/2));
    addChild(dropRing);
    
    
    //円の設定
    auto dropCircle = Sprite::create(pngCircle);
    dropCircle -> setScale(0.03);
    dropCircle -> setPosition(Vec2(dropRing->getPosition().x,dropRing->getPosition().y));
    addChild(dropCircle);
    
    
    
//オブジェクトの移動
    auto moveCircle = MoveTo::create(2, Vec2(dropRing->getPosition().x,moveY));
    
    auto moveRing = MoveTo::create(2, Vec2(dropRing->getPosition().x,moveY));
    
    
    //オブジェクトの拡大
    auto scale = ScaleBy::create(2, 12);
    //オブジェクトの削除
    auto remove = RemoveSelf::create(true);
    //オブジェクトのフェードアウト
    auto fadeOut = FadeOut::create(2);
    
    //拡大・フェードアウト同時アクション
    auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
    //移動後拡大のアクション
    auto moveScale = Sequence::create(moveRing, scaleFadeOut,remove,NULL);
    //移動後削除のアクション
    auto moveRemove = Sequence::create(moveCircle,remove,NULL);
    
    dropCircle -> runAction(moveRemove);
    dropRing -> runAction(moveScale);
    
    
}



