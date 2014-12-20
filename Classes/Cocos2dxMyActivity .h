//
//  Cocos2dxMyActivity .h
//  ColorBubbles
//
//  Created by 新井脩司 on 2014/11/29.
//
//

#ifndef ColorBubbles_Cocos2dxMyActivity__h
#define ColorBubbles_Cocos2dxMyActivity__h

//#include "cocos2d.h"

package jp.brbranch.lib;

import org.cocos2dx.lib.Cocos2dxActivity;
import android.content.Intent;
import android.os.Bundle;

abstract public class Cocos2dxMyActivity extends Cocos2dxActivity {
    static Cocos2dxMyActivity my;
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        my = this;
    }
    
    public static void tweet(String $msg){
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_TEXT, $msg);
        my.startActivity(intent);
    }
}


#endif
