//
//  GameScene.cpp
//  Muze
//
//  Created by apple on 14-11-4.
//
//

#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();   //创建一个物理场景
    //设置物理世界重力方向
    
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    auto layer = GameScene::create();   //创建一个图层
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->addChild(layer);
    return scene;
}


//初始化当前的图层
bool GameScene::init()
{
    if(!Layer::init())      //初始化父类
        return false;
    auto visibleSize= Director::getInstance()->getVisibleSize();
    
    //创建 世界地面
    auto load = Node::create();
    auto load_phy = PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height));
    load_phy->setContactTestBitmask(1);
    load->setPhysicsBody(load_phy);
    load->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    addChild(load);
    
    
    //初始化小球精灵
    auto draw_ball = DrawNode::create();
    draw_ball->drawDot(Point(0,0),50,Color4F::WHITE);
    ball = Sprite::create();
    //绑定绘制球体
    ball->addChild(draw_ball);
    auto ball_physicsBody =PhysicsBody::createCircle(40.0f);
    ball_physicsBody->setMass(10);
    ball_physicsBody->setDynamic(true);
    //线性阻尼
    //ball_physicsBody->setLinearDamping(0);
    ball_physicsBody->setGravityEnable(true);
    ball_physicsBody->setCategoryBitmask(1);
    ball_physicsBody->setCollisionBitmask(-1);
    ball_physicsBody->setContactTestBitmask(1);
    ball->setPhysicsBody(ball_physicsBody);
    ball->setPosition(visibleSize.width/2,visibleSize.height/2);
    ball->setTag(12);
    addChild(ball);
    
    //定时刷新 更改世界 重力方向
    schedule(schedule_selector(GameScene::reSetWordAcc),0.1);
//    //触摸监听
//    //触控监听
//    auto touchListener= EventListenerTouchOneByOne::create();
//    //设置不能向下传递
//    touchListener->setSwallowTouches(false);
//    //触摸结束
//    touchListener->onTouchBegan = [=](Touch * t, Event * e){
//        
//        return true;
//    };
//    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
//    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

void GameScene::onEnter(){
    gameScen= Director::getInstance()->getRunningScene();
    Layer::onEnter();
    //开启重力感应
    Device::setAccelerometerEnabled(true);
    //创建事件监听
    accelerationListion = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene:: onAcceleration, this));
    //事件中注册
    _eventDispatcher->addEventListenerWithSceneGraphPriority(accelerationListion, this);


}
void GameScene::onAcceleration(Acceleration *acc, Event *event){
    
//    log("x= %f , y= %f",acc->x,acc->y);
//    auto gamescene=Director::getInstance()->getRunningScene();
    //改变 物理世界 重力方向
    
//    gamescene->getPhysicsWorld()->setGravity(Vec2(980*acc->x, 980*acc->y));
//    if(fabs(current_acc.x - 980*acc->x)>50 && fabs(current_acc.y - 980*acc->y)>50){
       current_acc = Vec2(980*acc->x, 980*acc->y);
//    gameScen->getPhysicsWorld()->setGravity(Vec2(980*acc->x, 980*acc->y));
//    }
    

}
///**
// */
//void GameScene::onAcceleration(Acceleration *acc, Event *event){
//    
//}
void GameScene::onTouchEnded(Touch * t, Event * e){
//    auto gamescene=Director::getInstance()->getRunningScene();
//    gamescene->getPhysicsWorld()->setGravity(current_acc);

}

void GameScene::reSetWordAcc(float){

//    auto gamescene=Director::getInstance()->getRunningScene();
    gameScen->getPhysicsWorld()->setGravity(current_acc);

}


