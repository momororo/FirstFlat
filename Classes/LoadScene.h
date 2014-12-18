//
//  LoadScene.h
//  FirstFlat
//
//  Created by yasutomo on 2014/12/18.
//
//

#ifndef __FirstFlat__LoadScene__
#define __FirstFlat__LoadScene__

#include <stdio.h>
#include "cocos2d.h"


class LoadScene : public cocos2d::Layer{
    
protected:

    
    
    public :
    
    static cocos2d::Scene *createScene();
    
    virtual bool init();

    virtual void onEnterTransitionDidFinish();

    void replaceGameScene(float delta);



    
    CREATE_FUNC(LoadScene);

    
};


#endif /* defined(__FirstFlat__LoadScene__) */
