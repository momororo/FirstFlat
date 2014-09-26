//
//  Walls.cpp
//  FirstFlat
//
//  Created by yasutomo on 2014/09/26.
//
//

#include "Walls.h"

USING_NS_CC;

Walls* Walls::walls = 0;

//シングルトン
Walls* Walls::getInstance(){
    
    if(!Walls::walls){
        Walls::walls = new Walls();
    }
    
    return walls;
    
}


//配列0〜4のオブジェクトを返す
cocos2d::Vector<Sprite*> Walls::getWallsFromZero(){
    
    Vector<Sprite*> returnWalls = Vector<Sprite*>();
    
    int cnt = wallGroup;
    
    for(int idx = 0 ; idx < cnt ; idx++){
        returnWalls.pushBack(wallsVector.at(idx));
    }
    
    return returnWalls;
    
}

//配列5〜9のオブジェクトを返す
cocos2d::Vector<Sprite*> Walls::getWallsFromLast(){

    Vector<Sprite*> returnWalls = Vector<Sprite*>();

    
    int idx = (int)wallsVector.size() - wallGroup;
    
    for(;idx < wallsVector.size(); ++idx){
        returnWalls.pushBack(wallsVector.at(idx));
    }
    
    return returnWalls;

    
}

//配列の末尾にオブジェクトを追加
void Walls::setWalls(){
    
    auto selfFrame = Director::getInstance() -> getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    
    int cnt = wallGroup;
    
    for(int idx = 0 ; idx < cnt ; idx++){
        /**************　壁設定  ******************/
        Sprite *wall = Sprite::create();
        
        wall->setTextureRect(cocos2d::Rect(0, 0, visibleSize.width/5, visibleSize.width/8));
        
        int colorIdx = arc4random_uniform(5);
        
        switch (colorIdx) {
            case 0:
                wall->setColor(Color3B::GREEN);
                break;
            case 1:
                wall->setColor(Color3B::BLUE);
                break;
            case 2:
                wall->setColor(Color3B::GRAY);
                break;
            case 3:
                wall->setColor(Color3B::BLACK);
                break;
            case 4:
                wall->setColor(Color3B::WHITE);
                break;
            default:
                break;
        }
        
        
        //ポジション設定
        if(idx == 0){
            
            //最初のハコの位置調整
            wall->setPosition(Vec2(0 + wall->getContentSize().width/2,selfFrame.height*1.5));

        }else{
            
            //一つ前のオブジェクトの位置から次のオブジェクトの位置を置く。
            Sprite *preWall = wallsVector.at(wallsVector.size()-1);
            
            Vec2 prePosition = preWall->getPosition();
            
            wall->setPosition(Vec2(prePosition.x + (preWall->getContentSize().width),prePosition.y));
            
        }
        
        //配列に入れとく
        wallsVector.pushBack(wall);
        
        /**************　壁設定　おわり  ******************/

    }
    
    return;
    
}

//配列0〜4のオブジェクトを動かす
void Walls::moveToYFromZero(float y){
    
    
    int cnt = wallGroup;
    
    for (int idx = 0; idx < cnt ; idx++) {
        MoveTo* move = MoveTo::create(3.0f, Vec2(wallsVector.at(idx)->getPosition().x,y));
        wallsVector.at(idx)->runAction(move);
    }
    
}

//配列5〜9のオブジェクトを動かす
void Walls::moveToYFromLast(float y){
    
    int idx = (int)wallsVector.size() - wallGroup;
    
    for (; idx < wallsVector.size() ; idx++) {
        MoveTo* move = MoveTo::create(3.0f, Vec2(wallsVector.at(idx)->getPosition().x,y));
        wallsVector.at(idx)->runAction(move);
    }
    
}