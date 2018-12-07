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
#include "Title.h"
#include "SimpleAudioEngine.h"
#include "EntityLayer.h"
#include "Bullet.h"
#include "Global.h"
#include <iostream>
#include "Weeds.h"
#include <io.h>
#include <string>
#include "test.h"
#include "Background.h"
#include "LevelManager.h"
#include "UILayer.h"
#include <direct.h>
USING_NS_CC;
using namespace std;
using namespace map;

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
	auto ss = Director::getInstance()->getTextureCache()->getCachedTextureInfo();
	log("%s", ss.c_str());
	preLoading();
    return true;
}
void HelloWorld::preLoading()
{
	vector<string>files;
	vector<string>ownnames;
	getFiles("..\\Resources","..\\Resources", files, ownnames);
	tot_loadingSprite = files.size();
	

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	title = new Title(this);
	title->StartButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		this->scheduleOnce(schedule_selector(HelloWorld::GameIn), 0.0f);
	});
	loading = new Loading(Point(size.width / 2, 20 ),this,title);
	
	for (string x : files)
	{
		TextureCache::getInstance()->addImageAsync(x, CC_CALLBACK_1(HelloWorld::ResourceCallBack, this));
	}
}
void HelloWorld::ResourceCallBack(cocos2d::Texture2D *texture)
{
	loadingSprite++;
	if (loadingSprite == tot_loadingSprite)
	{
	}
}
void HelloWorld::GameIn(float t)
{
	//loading->clear();
	title->clear(this);
	this->addChild(EntityLayer::create());
	LevelManager::loadLevel(1);
	//background = new Background();
	//test a = test();
	//this->scheduleOnce(schedule_selector(HelloWorld::moveCamera), 1.0f);
}
string&  HelloWorld::replace_all(string&   str, const   string&   old_value, const   string&   new_value)
{
	while (true) {
		string::size_type   pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}
void HelloWorld::getFiles(string prePath,string path, vector<string>& files, vector<string> &ownname)
{
	/*files存储文件的路径及名称(eg.   C:\Users\WUQP\Desktop\test_devided\data1.txt)
	 ownname只存储文件的名称(eg.     data1.txt)*/

	 //文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles(prePath, p.assign(path).append("\\").append(fileinfo.name), files, ownname );
			}
			else
			{
				string str0 = p.assign(path).append("\\").append(fileinfo.name);
				string str1 = replace_all(str0, prePath + "\\", "");
				files.push_back(str1);
				ownname.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void HelloWorld::moveCamera(float delta)
{
	auto camera = Camera::getDefaultCamera();
	auto moveBy = MoveBy::create(2.5, Vec2(200, 0));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::LoadingCard, this));
	Sequence *sequence = Sequence::create(moveBy, DelayTime::create(1.5),moveBy->reverse(), actionDone, NULL);
	camera->runAction(actionDone);
}

void HelloWorld::moveCameraRight(float delta)
{
	auto camera = Camera::getDefaultCamera();
	auto moveBy = MoveBy::create(1.5f, Vec2(150, 0));
	auto showSelectCard = CallFuncN::create(std::bind(&LevelManager::showSelectCard));
	Sequence *sequence = Sequence::create(moveBy, DelayTime::create(0.4f), showSelectCard, NULL);
	camera->runAction(sequence);
	UILayer::getInstance()->runAction(moveBy->clone());
}

void HelloWorld::moveCameraLeft(float delta)
{
	auto camera = Camera::getDefaultCamera();
	auto moveBy = MoveBy::create(1.5f, Vec2(-150, 0));
	auto actionDone = CallFuncN::create(std::bind(&LevelManager::gameStart));
	Sequence *sequence = Sequence::create(moveBy, DelayTime::create(0.3f), actionDone, NULL);
	camera->runAction(sequence);
	UILayer::getInstance()->runAction(moveBy->clone());
}

void HelloWorld::LoadingCard(Node* pSender)
{
	//LevelManager::test();
	//GameStart = true;
}

void HelloWorld::updateSun(float delta)
{
	if (GameStart == false)
		return;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto x = random(10, (int)visibleSize.width - 10);
	auto y = (int)visibleSize.height;
	
	auto spSun = Sprite::createWithTexture(TextureCache::getInstance()->addImage("sun.png"));
	Point position = Point(x, y);
	spSun->setPosition(position);
	spSun->setScale(0.5);
	UILayer::getInstance()->addChild(spSun, 200);
	auto moveBy = MoveBy::create(4.5f, Point(0, -visibleSize.height + 30.0f));
	spSun->runAction(moveBy);
	dropSun.push_back(spSun);
	//spSun->runAction(reveseseq);
	//readySun.insert(sp, spSun);
}

void HelloWorld::updateZombie(float delta)
{
	LevelManager::createZombie();
}

void HelloWorld::checkWinAndLose(float delta)
{
	LevelManager::checkWin();
}