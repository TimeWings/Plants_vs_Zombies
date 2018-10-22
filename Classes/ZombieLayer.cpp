#include "ZombieLayer.h"
#include "Global.h"

ZombieLayer* ZombieLayer::pRet = nullptr;

bool ZombieLayer::init()
{
	this->schedule(schedule_selector(ZombieLayer::Check_isAttack), 0.1);
	return true;
}

ZombieLayer * ZombieLayer::create()
{
	ZombieLayer::pRet = new ZombieLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

void ZombieLayer::Check_isAttack(float t)
{
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* x = readyZombies.at(i);
		if (x->isAttacking() == false) continue;
		struct timeb t1;
		ftime(&t1);
		long long seconds = t1.time * 1000 + t1.millitm;
		long long interval = seconds - x->getBirthTime();
		if (interval > x->getInterval()) {
			//调用工作函数
			x->attack();
			struct timeb t1;
			ftime(&t1);
			long long seconds = t1.time * 1000 + t1.millitm;
			x->setBirthTime(seconds);
		}
	}
}

void ZombieLayer::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}
