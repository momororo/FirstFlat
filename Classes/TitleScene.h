//
//  TitleScene.h
//  FirstFlat
//
//  Created by 新井脩司 on 2014/09/24.
//
//

#ifndef __FirstFlat__TitleScene__
#define __FirstFlat__TitleScene__

#include "cocos2d.h"


class TitleScene : public cocos2d::Layer{
    
protected:

    
    //スタートボタンの生成
    void initStart();
    
    cocos2d::Sprite *start;
    cocos2d::Sprite *ranking;
    cocos2d::Sprite *challenge;
    
    
    
    
    public :
    
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(TitleScene);
    
    
    
    //タップイベントの宣言
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
    /***************** オープニング動作 ***********************/
    void setStart();
    void setRanking();
    void setChallenge();
    void setTitle();
    
    void fadeInTitle();
    void fadeInStart();
    void fadeInRanking();
    void fadeInCallenge();
    /****************** オープニング動作　終 ***********************/
    
    
    
    virtual void setDrops(float time);
    
    
    
    
    
    
    
    
    
    //void startCallback(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type);
    //void startCallback(cocos2d::Ref* sender,cocos2d::EventMouse::MouseEventType type);
    //void starCallback(cocos2d::Ref* pSender);
    
    
};

#endif /* defined(__FirstFlat__TitleScene__) */
