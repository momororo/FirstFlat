//
//  Player.cpp
//  FirstFlat
//
//  Created by yasutomo on 2014/09/26.
//
//

#include "Player.h"

USING_NS_CC;

//初期化
Player* Player::player = 0;

Player* Player::getInstance(){

    if(!Player::player){
        Player::player = new Player();
    }
    
    return player;
    
}

Sprite* Player::getPlayer(){
    
    

    
    if(!Player::playerSprite){

        auto selfFrame = Director::getInstance() -> getWinSize();
        auto visibleSize = Director::getInstance()->getVisibleSize();

        /**************　プレイヤー設定  ******************/
        playerSprite = Sprite::create();
        
        playerSprite->setTextureRect(cocos2d::Rect(0, 0, visibleSize.width/8, visibleSize.width/8));
        
        playerSprite->setColor(Color3B::GREEN);
        
        playerSprite->setPosition(Vec2(selfFrame.width/2, selfFrame.height/7));

        /**************　プレイヤー設定　おわり  ******************/

    }
    
    return playerSprite;
    

}

void Player::moveToX(float x){
    
    auto selfFrame = Director::getInstance() -> getWinSize();

    playerSprite->setPosition(Vec2(x, selfFrame.height/7));
    
    return;
    
}