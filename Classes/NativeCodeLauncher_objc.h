#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface NativeCodeLauncher_objc : NSObject

// GameCenter
+(void)loginGameCenter;
+(void)openRanking;
+(void)postHighScore:(NSString*)key score:(int)score;

@end