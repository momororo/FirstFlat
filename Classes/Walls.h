//
//  Walls.h
//  FirstFlat
//
//  Created by yasutomo on 2014/09/26.
//
//

#ifndef __FirstFlat__Walls__
#define __FirstFlat__Walls__
#define wallGroup 5;

#include "cocos2d.h"

class Walls :public cocos2d::Sprite{
    
private:
    
    //シングルトン用
    Walls(){};
    
protected:
//変数
    //シングルトン用インスタンス格納変数
    static Walls *walls;
    
    //オブジェクト格納用の配列
    cocos2d::Vector<cocos2d::Sprite*>wallsVector = cocos2d::Vector<Sprite*>();

    
public:
//変数
    static Walls* getInstance();
    
//メソッド
    //配列0〜4のオブジェクトを返す
    cocos2d::Vector<Sprite*> getWallsFromZero();
    //配列5〜9のオブジェクトを返す
    cocos2d::Vector<Sprite*> getWallsFromLast();
    //配列の末尾にオブジェクトを追加
    void setWalls();
    
    //配列0〜4のオブジェクトを動かす
    void moveToYFromZero(float y);
    //配列5〜9のオブジェクトを動かす
    void moveToYFromLast(float y);
    
    
//おまじない
    CREATE_FUNC(Walls);

    
    
};

#endif /* defined(__FirstFlat__Walls__) */
