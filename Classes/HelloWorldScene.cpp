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
#include "ZombieLayer.h"
#include "Bullet.h"
#include "PeaBullet.h"
#include "PeaShooter.h"
#include "Sunflower.h"
#include "DoublePeaShooter.h"
#include "IceShooter.h"
#include "PotatoMine.h"
#include "Global.h"
#include "TestZombie.h"
#include "BasicZombie.h"
#include <iostream>
#include "Weeds.h"
#include "test.h"
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
	this->addChild(PlantLayer::create());
	this->addChild(BulletLayer::create());
	this->addChild(ZombieLayer::create());
    auto visibleSize = Director::getInstance()->getVisibleSize();
	test a =test();

	
	
    return true;
}


