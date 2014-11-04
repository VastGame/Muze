//
//  GameScene.h
//  Muze
//
//  Created by apple on 14-11-4.
//
//

#ifndef __Muze__GameScene__
#define __Muze__GameScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    virtual void onEnter();
    //重写重力感应函数
//    virtual void didAccelerate(Acceleration* acc, Event* event);
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);
    void reSetWordAcc(float);
private:
    //重力感应小球
    Sprite *ball;
    Scene * gameScen;
    void onTouchEnded(Touch * t, Event * e);
    Vec2 current_acc;
    EventListenerAcceleration * accelerationListion;
};

#endif /* defined(__Muze__GameScene__) */
