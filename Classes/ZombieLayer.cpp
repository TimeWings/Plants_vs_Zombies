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
		Zombie *zombie = readyZombies.at(i);
		Sprite *sp = zombie->getImg();
		Plants *p;
		bool flagin = false, flagout = true;
		for (int j = 0; j < readyPlants.size(); j++)
		{
			Plants *plant = readyPlants.at(j);
			Sprite *sp_plant = plant->getImg();
			int row = plant->getRow();
			int startRange = zombie->getRange()->at(0);
			int endRange = zombie->getRange()->at(1);
			if (row<startRange || row>endRange)
			{
				continue;
			}
			if (fabs(sp->getPositionX()- sp_plant->getPositionX())<sp->getContentSize().width/2*sp->getScaleX()+ sp_plant->getContentSize().width / 2 * sp_plant->getScaleX() - 10)
			{
				flagin = true;
				p = plant;
			}
			if (fabs(sp->getPositionX() - sp_plant->getPositionX()) < sp->getContentSize().width / 2 * sp->getScaleX() + sp_plant->getContentSize().width / 2 * sp_plant->getScaleX() + 10)
			{
				flagout = false;
				p = plant;
			}
		}
		if (zombie->isMeeting() && flagout) {
			zombie->Move();
			zombie->setMeeting(false);
		}
		else if (!zombie->isMeeting() && flagin) {
			zombie->attack(p);
			zombie->setMeeting(true);
		}
	}
}

void ZombieLayer::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}
