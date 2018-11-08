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
#include "EntityLayer.h"
#include "Bullet.h"
#include "PeaBullet.h"
#include "PeaShooter.h"
#include "Sunflower.h"
#include "DoublePeaShooter.h"
#include "IceShooter.h"
#include "PotatoMine.h"
#include "Global.h"
#include "BasicZombie.h"
#include <iostream>
#include "Weeds.h"
#include <io.h>
#include <string>
#include "test.h"
#include "Background.h"
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
	loading = new Loading(Point(size.width / 2, size.height/2 ),this);
	for (string x : files)
	{
		TextureCache::getInstance()->addImageAsync(x, CC_CALLBACK_1(HelloWorld::ResourceCallBack, this));
	}
}
void HelloWorld::ResourceCallBack(cocos2d::Texture2D *texture)
{
	double curP = 100 * loadingSprite / (float)tot_loadingSprite;
	loadingSprite++;
	if (loadingSprite == tot_loadingSprite)
	{
		this->scheduleOnce(schedule_selector(HelloWorld::GameIn), 2.0f);
		
	}
}
void HelloWorld::GameIn(float t)
{
	loading->clear();
	this->addChild(EntityLayer::create());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	new Background();
	this->scheduleOnce(schedule_selector(HelloWorld::moveCamera), 1.0f);
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
	auto moveBy = MoveBy::create(2.5, Vec2(150, 0));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::LoadingCard, this));
	Sequence *sequence = Sequence::create(moveBy, DelayTime::create(1.5),moveBy->reverse(), actionDone, NULL);
	camera->runAction(sequence);
}

void HelloWorld::LoadingCard(Node* pSender)
{
	test a = test();
}