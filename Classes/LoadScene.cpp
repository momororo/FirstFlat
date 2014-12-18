//
//  LoadScene.cpp
//  FirstFlat
//
//  Created by yasutomo on 2014/12/18.
//
//

#include "LoadScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene *LoadScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = LoadScene::create();
    scene -> addChild(layer);
    
    
    return scene;
    
}

bool LoadScene::init(){
    
    if (!Layer::init())
    {
        return false;
    }
    
    this -> setColor(Color3B::BLACK);
    

    
    

    return true;
}


//トランジション終了時に呼ばれる
void LoadScene::onEnterTransitionDidFinish(){

    this -> scheduleOnce(schedule_selector(LoadScene::replaceGameScene), 1.0f);
}

//画面の遷移
void LoadScene::replaceGameScene(float delta){
    
    
    float duration = 0.5f;  //開始→終了にかける時間
    Scene* nextScene = CCTransitionFade::create(duration, GameScene::createScene());
    Director::getInstance()->replaceScene(nextScene);

    
}
