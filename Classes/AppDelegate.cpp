#include "AppDelegate.h"
#include "TitleScene.h"
#include "AppCCloudPlugin.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);
    
    //appccloud
    AppCCloudPlugin::setMK_iOS("099f478caeb05182b4db78ef1c80cf76e1765cd3").start();

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    glview -> setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);


    // create a scene. it's an autorelease object
    auto scene = TitleScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

/*
extern "C"
{
    size_t fwrite$UNIX2003(const void *a, size_t b, size_t c, FILE *d)
    {
        return fwrite(a, b, c, d);
    }
    
    char* strerror$UNIX2003( int errnum )
    {
        return strerror(errnum);
    }
}
 */