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
    //スコアラベル
    cocos2d::Label *scoreLabel;
    //cocos2d::Sprite *start;
    cocos2d::Sprite *ranking;
    cocos2d::Sprite *tutorial;
    
    //メニューの配列
    std::vector<std::string *> *menus = new std::vector<std::string *>;



    
    
    
    public :
    
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(TitleScene);
    
    void closeCallback(cocos2d::Ref* pSender);



    
    
    /***************** タッチイベント用変数 ***********************/
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

    /***************** タッチイベント用変数 終***********************/
    
    /***************** オープニング動作 ***********************/
    void presetSprite();
    
    
    
    void setStart();
    void setRanking();
    void setTutorial();
    void setTitle();
    
    void fadeInTitle();
    void fadeInStart();
    void fadeInRanking();
    void fadeInTutorial();
    void fadeInUmbrella();
    /****************** オープニング動作　終 ***********************/
    
    //ボタンタップ後の処理メソッド
    void tappedBt(std::string &menu);
    //ボタンタップの管理フラグ
    bool playerCanTapBt;
    
    virtual void setDrops(float time);
    
    //AppCCloudの広告用
    void setAppCCloud();
    void removeAppCCloud();
    //twitter
    void setTwitterBt();
    
    void setTutorialFade();
    bool tutorialFlag;
    float tapPoint;
    float tutorialPointX;
    
    
};

#endif /* defined(__FirstFlat__TitleScene__) */
