#include "NativeCodeLauncher_objc.h"
#include "NativeCodeLauncher.h"

// GameCenterにログイン
void NativeCodeLauncher::loginGameCenter()
{
        [NativeCodeLauncher_objc loginGameCenter];
}
// Leaderboard表示
void NativeCodeLauncher::openRanking()
{
        [NativeCodeLauncher_objc openRanking];
}
// ハイスコアを送信
void NativeCodeLauncher::postHighScore(std::string key,int score)
{
    [NativeCodeLauncher_objc postHighScore:[[[NSString alloc] initWithCString:key.c_str() encoding:NSUTF8StringEncoding] autorelease] score:score];
    
}

/*
namespace Cocos2dExt
{
	// GameCenter
        void NativeCodeLauncher::loginGameCenter()
        {
                static_loginGameCenter();
        }
        void NativeCodeLauncher::openRanking()
        {
                static_openRanking();
        }
        void NativeCodeLauncher::postHighScore(std::string key, int score)
        {
                static_postHighScore( key, score);
        }
}
*/