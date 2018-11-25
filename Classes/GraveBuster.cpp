#include "GraveBuster.h"
#include "Global.h"
GraveBuster::GraveBuster(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Card\\GraveBuster.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScaleX(2.2);
	sp->setScaleY(2.5);
	sp->setPosition(position.x,position.y+map::BlockSize.second*0.75);
	this->setHp(6);
	this->setInterval(500);
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool GraveBuster::isWorking()
{
	if (isEating)
	{
		return false;
	}
	return true;
}

void GraveBuster::work()
{
	if (isWorking())
	{
		Sprite* Gsp = this->getImg();
		isEating = true;
		PlantStatus* plantstatus = map::find(this->getRow(), this->getCol());
		if (plantstatus != NULL)
		{
			bool flag = false;
			for (auto x : plantstatus->plantVector)
			{
				if (strcmp(typeid(*x).name(), "class Tomb") == 0)
				{
					plant = x;
					std::cout << "有墓碑，开始工作" << std::endl;
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				std::cout << "没有墓碑，直接死亡" << std::endl;
				readyDie(this->getImg());
				return;
			}
		}
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 1; i <= 42; i++)
		{
			sprintf(str, "GraveBuster\\Self_Animation\\%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.14);
		MoveTo* mt = MoveTo::create(6, Vec2(Gsp->getPositionX(),Gsp->getPositionY()-7));
		Animate* self_An = Animate::create(an);
		Spawn* spawn = Spawn::create(mt, self_An, NULL);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(GraveBuster::readyDie, this));
		Sequence *sequence = Sequence::create(spawn, actionDone, NULL);
		this->getImg()->runAction(sequence);
	}

}
void GraveBuster::readyDie(Node* pSender)
{
	this->setHp(-1);
	if(plant!=NULL)
	plant->setHp(-1);
}

void GraveBuster::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

