//
//  TitleScene.cpp
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#include "TitleScene.h"
#include "GameScene.h"
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
    
    //背景色のグラデーション
    auto bgGradient = LayerGradient::create(Color4B(128,229,255,255), Color4B(95,211,188,255));
    this -> addChild(bgGradient);
   
    
    this -> schedule(schedule_selector(TitleScene::setDrops), 1);
    
    //各種タイトルの設定
    setTitle();
    setStart();
    setRanking();
    setChallenge();

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
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    //スタートボタンタップ時の操作
    if (!start) {
        
        return true;
        
    }else if (start->getBoundingBox().containsPoint(touchPoint))
        
    {
        CCLOG("スタートボタンをタップ");
        
        auto effectRing = Sprite::create("aqua_ring.png");
        effectRing -> setPosition(Vec2(start->getPosition().x,start->getPosition().y));
        effectRing -> setScale(0.1);
        addChild(effectRing);
        
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        effectRing -> runAction(ringSequence);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("low_c.mp3");

        
        return true;
    }
    
    
    
    //ランキングボタンタップ時
    if (!ranking) {
        
        return true;
        
    }else if (ranking->getBoundingBox().containsPoint(touchPoint))
        
    {
        CCLOG("スタートボタンをタップ");
        
        auto effectRing = Sprite::create("orange_ring.png");
        effectRing -> setPosition(Vec2(ranking->getPosition().x,ranking->getPosition().y));
        effectRing -> setScale(0.1);
        addChild(effectRing);
        
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        effectRing -> runAction(ringSequence);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("low_bFlat.mp3");

        
        return true;
    }
    
    
    
    //チャレンジボタンタップ時
    if (!challenge) {
        
        return true;
        
    }else if (challenge->getBoundingBox().containsPoint(touchPoint))
        
    {
        CCLOG("スタートボタンをタップ");
        
        auto effectRing = Sprite::create("yellow_ring.png");
        effectRing -> setPosition(Vec2(challenge->getPosition().x,challenge->getPosition().y));
        effectRing -> setScale(0.1);
        addChild(effectRing);
        
        auto ringScale = ScaleBy::create(2, 12);
        auto ringFadeOut = FadeOut::create(2);
        auto ringRemove = RemoveSelf::create(true);
        auto scaleFadeOut = Spawn::create(ringScale,ringFadeOut, NULL);
        auto ringSequence = Sequence::create(scaleFadeOut,ringRemove, NULL);
        
        effectRing -> runAction(ringSequence);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("low_d.mp3");

        
        return true;
    }

    
    
    
    
    
    
    
    
    return true;
    
}


#pragma mark-
#pragma mark touchMoved

void TitleScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    
    
}


#pragma mark-
#pragma mark touchEnded

void TitleScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);

    
    
    if (!start) {
        
        return;
        
    }else if (start->getBoundingBox().containsPoint(touchPoint))
        
    {
        CCLOG("スタートボタンをタップ");

        //アニメーション付き
        float duration = 2.0f;  //開始→終了にかける時間
        Scene* nextScene = CCTransitionFade::create(duration, GameScene::createScene());
 
        Director::getInstance()->replaceScene(nextScene);
        return;
    }
    

    
}


#pragma mark-
#pragma mark touchCancelled

void TitleScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    //タッチキャンセル
    CCLOG("touchCancelled");
    
}


#pragma mark-
#pragma mark オープニング動作

/***********************************************************
                各種オープニングの動作設定
 **********************************************************/


//オープニングのタイトルの動作
void TitleScene::setTitle(){
    
    
    //タイトル効果
    auto titleRain = Sprite::create("yellow_rain.png");
    titleRain -> setPosition(Vec2(selfFrame.width/2,selfFrame.height + 200));
    titleRain -> setScale(0.1);
    addChild(titleRain);
    
    //オブジェクトの移動
    auto move = MoveTo::create(2, Vec2(selfFrame.width/2,selfFrame.height*2/3));
    //オブジェクトの削除
    auto remove = RemoveSelf::create(true);
    
    //タイトルフェードイン
    auto func = CallFunc::create([this](){
        
        this -> fadeInTitle();
        
        
        
    });
    
    //移動後削除のアクション
    auto moveRemove = Sequence::create(move,remove,func,NULL);



    
    /*
    ring = Sprite::create("yellow_ring.png");
    ring -> setPosition(Vec2(selfFrame.width/2,selfFrame.height + 200));
    ring -> setScale(0.1);
    */
    
    
    //オブジェクトの拡大
    //auto scale = ScaleBy::create(2, 12);
        //オブジェクトのフェードアウト
    auto fadeOut = FadeOut::create(2);
    
    
    
    
    //拡大・フェードアウト同時アクション
    //auto scaleFadeOut = Spawn::create(scale,fadeOut, NULL);
    //移動後拡大のアクション
    //auto moveScale = Sequence::create(move, scaleFadeOut,remove,NULL);

    
    circle -> runAction(moveRemove);
    ring -> runAction(moveScale);
    
}



//オープニングのスタート動作
void TitleScene::setStart(){
    
    //スタートボタン効果
    auto circleStart = Sprite::create("blue_rain.png");
    circleStart -> setPosition(Vec2(selfFrame.width/2,selfFrame.height+100));
    circleStart -> setScale(0.1);
    addChild(circleStart);
    
    auto ringStart = Sprite::create("blue_ring.png");
    ringStart -> setPosition(Vec2(selfFrame.width/2,selfFrame.height+100));
    ringStart -> setScale(0.1);
    addChild(ringStart);
    
    //スタートオブジェクトの移動
    auto moveCircle2 = MoveTo::create(2, Vec2(selfFrame.width/2, selfFrame.height/6));
    auto moveRing2 = MoveTo::create(2, Vec2(selfFrame.width/2, selfFrame.height/6));
    
    //オブジェクトの拡大
    auto scale2 = ScaleBy::create(2, 12);
    //オブジェクトの削除
    auto remove2 = RemoveSelf::create(true);
    //オブジェクトのフェードアウト
    auto fadeOut2 = FadeOut::create(2);
    
    
    auto funcStart = CallFunc::create([this](){
        
        this -> fadeInStart();
        
    });
    
    //拡大・フェードアウト同時アクション
    auto scaleFadeOut2 = Spawn::create(scale2,fadeOut2, NULL);
    //移動後拡大のアクション
    auto moveScale2 = Sequence::create(moveRing2, scaleFadeOut2,remove2, NULL);
    //移動後削除のアクション
    auto moveRemove2 = Sequence::create(moveCircle2,remove2,funcStart,NULL);
    
    circleStart -> runAction(moveRemove2);
    ringStart -> runAction(moveScale2);

}



//オープニングのランキング動作
void TitleScene::setRanking(){
    
    //ランキングボタン効果
    auto circleRanking = Sprite::create("orange_circle.png");
    circleRanking -> setPosition(Vec2(60,selfFrame.height+100));
    circleRanking -> setScale(0.1);
    addChild(circleRanking);
    
    auto ringRanking = Sprite::create("orange_ring.png");
    ringRanking -> setPosition(Vec2(60,selfFrame.height+100));
    ringRanking -> setScale(0.1);
    addChild(ringRanking);
    
    //オブジェクトの移動
    auto moveCircle3 = MoveTo::create(2, Vec2(60,selfFrame.height/4));
    auto moveRing3 = MoveTo::create(2, Vec2(60,selfFrame.height/4));
    
    //オブジェクトの拡大
    auto scale3 = ScaleBy::create(2, 12);
    //オブジェクトの削除
    auto remove3 = RemoveSelf::create(true);
    //オブジェクトのフェードアウト
    auto fadeOut3 = FadeOut::create(2);
    
    
    auto funcRanking = CallFunc::create([this](){
        
        this -> fadeInRanking();
        
    });
    
    //拡大・フェードアウト同時アクション
    auto scaleFadeOut3 = Spawn::create(scale3,fadeOut3, NULL);
    //移動後拡大のアクション
    auto moveScale3 = Sequence::create(moveRing3, scaleFadeOut3,remove3,NULL);
    //移動後削除のアクション
    auto moveRemove3 = Sequence::create(moveCircle3,remove3,funcRanking,NULL);
    
    circleRanking -> runAction(moveRemove3);
    ringRanking -> runAction(moveScale3);
 
}


//オープニングのチャレンジ動作
void TitleScene::setChallenge(){
    
    //チャレンジボタン効果
    auto circleChallenge = Sprite::create("yellow_circle.png");
    circleChallenge -> setPosition(Vec2(selfFrame.width-60,selfFrame.height+100));
    circleChallenge -> setScale(0.1);
    addChild(circleChallenge);
    
    auto ringChallenge = Sprite::create("yellow_ring.png");
    ringChallenge -> setPosition(Vec2(selfFrame.width-60,selfFrame.height+100));
    ringChallenge -> setScale(0.1);
    addChild(ringChallenge);
    
    
    //オブジェクトの移動
    auto moveCircle4 = MoveTo::create(2, Vec2(selfFrame.width-60,selfFrame.height/4));
    auto moveRing4 = MoveTo::create(2, Vec2(selfFrame.width-60,selfFrame.height/4));
    
    //オブジェクトの拡大
    auto scale4 = ScaleBy::create(2, 12);
    //オブジェクトの削除
    auto remove4 = RemoveSelf::create(true);
    //オブジェクトのフェードアウト
    auto fadeOut4 = FadeOut::create(2);
    
    
    auto funcChallenge = CallFunc::create([this](){
        
        this -> fadeInCallenge();
        
    });
    
    //拡大・フェードアウト同時アクション
    auto scaleFadeOut4 = Spawn::create(scale4,fadeOut4, NULL);
    //移動後拡大のアクション
    auto moveScale4 = Sequence::create(moveRing4, scaleFadeOut4,remove4,NULL);
    //移動後削除のアクション
    auto moveRemove4 = Sequence::create(moveCircle4,remove4,funcChallenge,NULL);
    
    
    circleChallenge -> runAction(moveRemove4);
    ringChallenge -> runAction(moveScale4);


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
    
    //タイトル
    titleLabel = Label::createWithSystemFont("レイン\nドロップ","DragonQuestFC",120);
    titleLabel -> setPosition(Vec2(selfFrame.width/2, selfFrame.height*2/3));
    titleLabel->setOpacity(0);
    addChild(titleLabel,10);
    titleLabel -> runAction(FadeIn::create(2));
    
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
    
    auto umbrella = Sprite::create("umbrella.png");
    umbrella -> setAnchorPoint(Vec2(1,1));
    umbrella -> setScale(0.08);
    umbrella-> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    umbrella -> setOpacity(0);
    addChild(umbrella);
    umbrella -> runAction(FadeIn::create(2));

}

//スタートのフェードイン表示
void TitleScene::fadeInStart(){
    
    //スタートボタン
    start = Sprite::create("aqua_circle.png");
    start -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/6));
    start -> setScale(0.1);
    start -> setOpacity(0);
    addChild(start,10);
    
    auto startLabel = Label::createWithSystemFont("スタート","DragonQuestFC",30);
    startLabel -> setPosition(Vec2(start->getPosition().x, start->getPosition().y));
    addChild(startLabel,10);
    
    start -> runAction(FadeIn::create(2));
    startLabel ->runAction(FadeIn::create(2));

}

//ランキングのフェードイン表示
void TitleScene::fadeInRanking(){
    
    //ランキング
    ranking = Sprite::create("orange_circle.png");
    ranking -> setPosition(Vec2(60,selfFrame.height/4));
    ranking -> setScale(0.1);
    ranking -> setOpacity(0);
    addChild(ranking,10);
    
    auto rankingLabel = Label::createWithSystemFont("ランキング","DragonQuestFC",30);
    rankingLabel -> setPosition(Vec2(ranking->getPosition().x, ranking->getPosition().y));
    addChild(rankingLabel,10);
    
    ranking -> runAction(FadeIn::create(2));
    rankingLabel -> runAction(FadeIn::create(2));
    

}

//チャレンジのフェードイン表示
void TitleScene::fadeInCallenge(){
    
    //チャレンジモード
    challenge = Sprite::create("yellow_circle.png");
    challenge -> setPosition(Vec2(selfFrame.width-60,selfFrame.height/4));
    challenge -> setScale(0.1);
    challenge -> setOpacity(0);
    addChild(challenge,10);
    
    auto challengeLabel = Label::createWithSystemFont("チャレンジ","DragonQuestFC",30);
    challengeLabel -> setPosition(Vec2(challenge->getPosition().x, challenge->getPosition().y));
    addChild(challengeLabel,10);
    
    challenge -> runAction(FadeIn::create(2));
    challengeLabel -> runAction(FadeIn::create(2));

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
        
        pngCircle = "aqua_circle.png";
        pngRing = "aqua_ring.png";
        
    }else if(rnd == 1){
        
        pngCircle = "green_circle.png";
        pngRing = "green_ring.png";
    
    }else if(rnd == 2){
    
        pngCircle = "yellow_circle.png";
        pngRing = "yellow_ring.png";
        
    }else if(rnd == 3){
    
        pngCircle = "blue_circle.png";
        pngRing = "blue_ring.png";
        
    }else if (rnd == 4){
        
        pngCircle = "orange_circle.png";
        pngRing = "orange_ring.png";
    
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




