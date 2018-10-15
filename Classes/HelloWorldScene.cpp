/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include <time.h>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BulletLayer.h"
#include "PlantLayer.h"
#include "Bullet.h"
#include "PeaBullet.h"
#include "PeaShooter.h"
#include "Sunflower.h"
#include "DoublePeaShooter.h"
#include "IceShooter.h"
#include "Global.h"
#include "TestZombie.h"
#include <iostream>
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Plants* plant13 = new IceShooter(Point(60, 120));
	
	TestZombie *zombie =new TestZombie(Point(300, 120));
	this->addChild(zombie->init());
	/*Plants* plant12 = new DoublePeaShooter(Point(210, 60));
	Plants *plant1 = new Sunflower(Point(60, 250));
	Plants *plant7 = new Sunflower(Point(110, 250));
	Plants *plant = new PeaShooter(Point(110, 60));
	Plants *plant2 = new PeaShooter(Point(60, 180));
	Plants *plant3 = new PeaShooter(Point(60, 120));
	Plants *plant4 = new PeaShooter(Point(60, 60));*/
	/*Plants *plant5 = new PeaShooter(Point(110, 180));
	Plants *plant6 = new PeaShooter(Point(110, 120));
	Plants *plant8 = new Sunflower(Point(160, 250));
	Plants *plant9 = new Sunflower(Point(160, 180));
	Plants *plant10 = new Sunflower(Point(160, 120));
	Plants *plant11 = new Sunflower(Point(160, 60));*/
	this->addChild(PlantLayer::create());
	this->addChild(BulletLayer::create());
	
	//DrawNode* drawNode = DrawNode::create();
	//this->addChild(drawNode);
	//drawNode->drawDot(Vec2(130,180), 3, Color4F::RED);
	
    return true;
}


