#ifndef __FirstFlat__NativeCodeLauncher__
#define __FirstFlat__NativeCodeLauncher__


#include <string>

//namespace Cocos2dExt {

class NativeCodeLauncher{
    public:
		// GameCenter
                static void loginGameCenter();
                static void openRanking();
                static void postHighScore(std::string ,int score);
    };
//}

#endif /* defined(__FirstFlat__NativeCodeLauncher__) */