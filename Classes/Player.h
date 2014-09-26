//
//  Player.h
//  FirstFlat
//
//  Created by yasutomo on 2014/09/26.
//


#ifndef __FirstFlat__Player__
#define __FirstFlat__Player__


#include "cocos2d.h"

class Player : public cocos2d::Sprite{
    
private:
    //シングルトン用
    Player(){}
    
protected:
    //変数
    static Player *player;
    cocos2d::Sprite* playerSprite;
    
public:


    //メソッド
    static Player* getInstance();
  
    cocos2d::Sprite* getPlayer();
    
    void moveToX(float);
    
    
    //おまじない
    CREATE_FUNC(Player);
    
    
    
};



#endif /* defined(__FirstFlat__Player__) */
