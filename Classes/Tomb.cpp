#include "Tomb.h"
#include "Global.h"
#include "BasicZombie.h"
#include "RoadblockZombie.h"
#include "sys/timeb.h"
Tomb::Tomb(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	struct timeb timeSeed;
	ftime(&timeSeed);
	srand(timeSeed.time * 1000 + timeSeed.millitm);
	int cnt = rand() % 5 + 1;
	Sprite *sp;
	if (cnt == 1)
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\Tomb1.png"));
	else if (cnt == 2)
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\Tomb2.png"));
	else if (cnt == 3)
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\Tomb3.png"));
	else if(cnt==4)
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\Tomb4.png"));
	else
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\Tomb5.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(2.2);
	sp->setPosition(position);
	this->setHp(3);
	this->setInterval(7000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);

	PlantStatus* plantstatus = map::find(this->getRow(), this->getCol());
	std::cout << this->getRow() << "    " << this->getCol() << std::endl;
	if (plantstatus != NULL)
	{
		plantstatus->Enabled = false;
		std::cout << plantstatus->Enabled << std::endl;
	}
}

bool Tomb::isWorking()
{
	if (map::GameStart)
	{
		return true;
	}
	return false;
}

void Tomb::work()
{
	if (isWorking())
	{
		setNewBirthTime();
		CreateZombie();
	}
}

void Tomb::Die()
{
	PlantStatus* plantstatus = map::find(this->getRow(), this->getCol());
	if (plantstatus != NULL)
	{
		plantstatus->Enabled = true;
	}
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Tomb::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void Tomb::Self_Animation()
{
}

void Tomb::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Tomb::CreateZombie()
{
	Sprite* tombSp = this->getImg();
	int cnt = rand() % 2 + 1;
	Sprite *sp;
	if (cnt == 1)
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\BasicZombie.png"));
	else 
		sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Tomb\\RoadblockZombie.png"));
	sp->setScale(2);
	CCProgressTimer*timer = CCProgressTimer::create(sp);//创建CCProgressTimer
	timer->setPosition(tombSp->getPositionX(), tombSp->getPositionY()-sp->getContentSize().height*sp->getScaleY()+7);//设置CCProgressTimer位置
	timer->setType(kCCProgressTimerTypeBar);//设置类型
	timer->setScale(2);
	timer->setPercentage(0);//设置当前初始值
	timer->setMidpoint(CCPoint(0, 1));//设置进度开始的位置
	timer->setBarChangeRate(CCPoint(0, 1));//设置进度所占比例

	auto noneSp = Sprite::create();
	noneSp->setScaleX(2.3);
	noneSp->setScaleY(2.7);
	noneSp->setPosition(tombSp->getPositionX(), tombSp->getPositionY()- tombSp->getContentSize().height/2* tombSp->getScaleY()+3);
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str, "Tomb\\Animation\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.33);
	Animate* Dirt_An = Animate::create(an);
	MoveTo* mt = MoveTo::create(1.3, tombSp->getPosition());
	ProgressTo* pt = ProgressTo::create(1.3, 100);
	Spawn* spawn = Spawn::create(mt,pt, NULL);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Tomb::clear, this));
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Tomb::BirthZombie, this,cnt));
	Sequence *sequence = Sequence::create(Dirt_An, actionDone, NULL);
	Sequence *sequence1 = Sequence::create(spawn, actionDone1, NULL);
	addLayer(timer);
	addLayer(noneSp);
	timer->runAction(sequence1);
	noneSp->runAction(sequence);
}
void Tomb::BirthZombie(Node*pSender,int cnt)
{
	pSender->removeFromParent();
	if (cnt == 1)
	{
		new BasicZombie(this->getImg()->getPosition(), this->getRow(), this->getCol());
	}
	else 
	{
		new RoadblockZombie(this->getImg()->getPosition(), this->getRow(), this->getCol());
	}
}
void Tomb::clear(Node * pSender)
{
	pSender->removeFromParent();
}
