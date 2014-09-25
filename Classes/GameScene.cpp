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
    
    //メイン画面
    auto background = LayerColor::create(Color4B::RED, selfFrame.width, selfFrame.height);
    //Sprite::create();
    //background -> setPosition(Point(WINSIZE.width/2,WINSIZE.height/2));
    this -> addChild(background,0);
    
    
    
    
    
    
    
    
    return true;
}

