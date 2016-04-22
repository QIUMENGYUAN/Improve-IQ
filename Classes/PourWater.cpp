#include "PourWater.h"

Scene* PourWater::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PourWater::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
	
}

// on "init" you need to initialize your instance
bool PourWater::init()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound2.mp3", false);
	const auto OutScreen = Point(-100, -100);
	auto BkImage = Sprite::createWithSpriteFrameName("b7.png");
	BkImage->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(BkImage, 0);

	auto Main = Sprite::createWithSpriteFrameName("main.png");
	Main->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(Main, 0);

	auto Back = Sprite::createWithSpriteFrameName("back.png");
	Back->setAnchorPoint(Point(0, 0));
	Back->setPosition(0, visibleSize.height - 400 - 80);
	addChild(Back, 1);

	flag = true;

	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";
	sqlite3_open(path.c_str(), &pdb);
	std::string sql;
	char **re;
	sql = "select beststeps from record where level=";
	sql += Value(UserDefault::getInstance()->getIntegerForKey("Chapter") + 1).asString();
	sqlite3_get_table(pdb, sql.c_str(), &re, NULL, NULL, NULL);
	m_BestSteps = Value(re[1]).asInt();
	sqlite3_close(pdb);

	auto Help = Sprite::createWithSpriteFrameName("help.png");
	Help->setPosition(visibleSize.width - Help->getContentSize().width / 2, visibleSize.height - Help->getContentSize().height / 2);
	addChild(Help, 6);

	auto HelpInformation = Sprite::createWithSpriteFrameName("helpinfo.png");
	HelpInformation->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	HelpInformation->setVisible(false);
	addChild(HelpInformation, 16);

	auto CloseHelp  = Sprite::createWithSpriteFrameName("closehelp.png");
	CloseHelp->setAnchorPoint(Point(0, 0));
	CloseHelp->setPosition(647, visibleSize.height - 41 - 67);
	CloseHelp->setVisible(false);
	addChild(CloseHelp, 16);

	auto Retry = Sprite::createWithSpriteFrameName("restart.png");
	Retry->setPosition(visibleSize.width - Help->getContentSize().width / 2, Retry->getContentSize().height / 2);
	addChild(Retry, 6);

	LabelIQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 55);
	LabelIQ->setString("IQ:"+Value(UserDefault::getInstance()->getIntegerForKey("IQ")).asString());
	LabelIQ->setPosition(90, 373);
	LabelIQ->setColor(Color3B(214, 215, 250));
	addChild(LabelIQ, 6);

	CurrentBsetStep = Label::createWithTTF("", "fonts/Futura (Light).ttf", 26);
	CurrentBsetStep->setPosition(760, 388);
	CurrentBsetStep->setColor(Color3B(0, 255, 255));
	addChild(CurrentBsetStep, 6);
	 
	CurrentStep = Label::createWithTTF("", "fonts/Futura (Light).ttf", 26);
	CurrentStep->setPosition(760, 353);
	CurrentStep->setColor(Color3B(0, 255, 255));
	addChild(CurrentStep, 6);

	
	Blue = Sprite::createWithSpriteFrameName("BottleBack1.png");
	Blue->setPosition(OutScreen);
	addChild(Blue, 1); 
	Red = Sprite::createWithSpriteFrameName("BottleBack2.png");
	Red->setPosition(OutScreen);
	addChild(Red, 1);

	SetWater();

	auto Acup = Sprite::createWithSpriteFrameName("Bottle1-100.png");
	Acup->setScale(1.5);
	auto APoint = Point(visibleSize.width*0.17, 210);
	Acup->setPosition(APoint);
	addChild(Acup, 2); m_Cup.pushBack(Acup);
	auto AHWidth = Acup->getContentSize().width / 2 * Acup->getScale();

	auto Bcup = Sprite::createWithSpriteFrameName("Bottle1-0.png");
	Bcup->setScale(((float(Capacity[1]) + float(Capacity[0])) / 2 / float(Capacity[0]))*1.5);
	auto BPoint = Point(visibleSize.width*0.40, 210);
	Bcup->setPosition(BPoint);
	addChild(Bcup, 2); m_Cup.pushBack(Bcup);
	auto BHWidth = Bcup->getContentSize().width / 2 * Bcup->getScale();

	auto Ccup = Sprite::createWithSpriteFrameName("Bottle1-0.png");
	auto CPoint = Point(visibleSize.width*0.63, 210);
	Ccup->setPosition(CPoint);
	addChild(Ccup, 2); m_Cup.pushBack(Ccup);
	Ccup->setScale(((float(Capacity[2]) + float(Capacity[0])) / 2 / float(Capacity[0]))*1.5);
	auto CHWidth = Ccup->getContentSize().width / 2 * Ccup->getScale();

	auto Dcup = Sprite::createWithSpriteFrameName("Bottle1-0.png");
	auto DPoint = Point(visibleSize.width*0.86, 210);
	Dcup->setPosition(DPoint);
	addChild(Dcup, 2); m_Cup.pushBack(Dcup);
	Dcup->setScale(((float(Capacity[3]) + float(Capacity[0])) / 2 / float(Capacity[0]))*1.5);
	auto DHWidth = Dcup->getContentSize().width / 2 * Dcup->getScale();



	auto Acurcap = Label::createWithTTF("", "fonts/Futura (Light).ttf", 26);
	addChild(Acurcap, 6);
	Acurcap->setColor(Color3B(214, 215, 250));
	Current_Capacity.pushBack(Acurcap);

	auto Bcurcap = Label::createWithTTF("", "fonts/Futura (Light).ttf", 26);
	addChild(Bcurcap, 6);
	Bcurcap->setColor(Color3B(214, 215, 250));
	Current_Capacity.pushBack(Bcurcap);

	auto Ccurcap = Label::createWithTTF("", "fonts/Futura (Light).ttf", 26);
	addChild(Ccurcap, 6);
	Ccurcap->setColor(Color3B(214, 215, 250));
	Current_Capacity.pushBack(Ccurcap);

	auto Dcurcap = Label::createWithTTF("", "fonts/Futura (Light).ttf", 26);
	addChild(Dcurcap, 6);
	Dcurcap->setColor(Color3B(214, 215, 250));
	Current_Capacity.pushBack(Dcurcap);


	auto Condiiton = Label::createWithTTF("", "fonts/Futura (Light).ttf", 34);
	Condiiton->setString(Value(DestinationWater[0]).asString() + ", " + Value(DestinationWater[1]).asString() + ", " + Value(DestinationWater[2]).asString() + ", " + Value(DestinationWater[3]).asString());
	Condiiton->setPosition(555,436);
	Condiiton->setColor(Color3B(246, 232, 255));
	addChild(Condiiton, 6);
	 

	Next = Sprite::createWithSpriteFrameName("next.png");
	Next->setAnchorPoint(Point(0, 0));
	Next->setPosition(510, visibleSize.height - 293 - 74);
	addChild(Next, 20);
	Next->setVisible(false);
	
	Restart = Sprite::createWithSpriteFrameName("restart2.png");
	Restart->setAnchorPoint(Point(0, 0));
	Restart->setPosition(510, visibleSize.height - 190 - 74);
	addChild(Restart, 20);
	Restart->setVisible(false);

	m_Menu = Sprite::createWithSpriteFrameName("menu.png");
	m_Menu->setAnchorPoint(Point(0, 0));
	m_Menu->setPosition(510, visibleSize.height - 90 - 74);
	addChild(m_Menu, 20);
	m_Menu->setVisible(false);


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		//Take out the Sprite object had been bind when Register the Listener Event
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (IsIntoNext)
		{
			if (Next->getBoundingBox().containsPoint(touch->getLocation()))
			{
				UserDefault::getInstance()->setIntegerForKey("Chapter", Chapter + 1);
				Director::getInstance()->replaceScene(PourWater::createScene());
			}
			if (Restart->getBoundingBox().containsPoint(touch->getLocation()))
			{
				Director::getInstance()->replaceScene(PourWater::createScene());
			}
			if (m_Menu->getBoundingBox().containsPoint(touch->getLocation()))
			{
				Director::getInstance()->replaceScene(TableViewTestLayer::createScene());
			}
		}		
		if (IsTouch)
		{

			if (Help->getBoundingBox().containsPoint(touch->getLocation()))
			{
				//IsTouch = false;
				HelpInformation->setVisible(true);
				CloseHelp->setVisible(true);
			}
			if (CloseHelp->getBoundingBox().containsPoint(touch->getLocation()))
			{
				//IsTouch = true;
				HelpInformation->setVisible(false);
				CloseHelp->setVisible(false);
			}
			if (Retry->getBoundingBox().containsPoint(touch->getLocation()))
			{
				Acup->setPosition(APoint);
				Bcup->setPosition(BPoint);
				Ccup->setPosition(CPoint);
				Dcup->setPosition(DPoint);
				m_steps = 0;
				CurrentWarter[0] = Capacity[0];
				CurrentWarter[1] = CurrentWarter[2] = CurrentWarter[3] = 0;
			}
			if (Back->getBoundingBox().containsPoint(touch->getLocation()))
			{
				Director::getInstance()->replaceScene(TableViewTestLayer::createScene());
			}
			if (target->getBoundingBox().containsPoint(touch->getLocation()))
			{
				//Blue Set Scale from target'Scale
				Blue->setScale(target->getScale());
				Blue->setPosition(target->getPosition());
				target->setVisible(true);
				return true;
			}	
		}
		return false;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
	
		//Take out the Sprite object had been bind when Register the Listener Event
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		//Set higer ZOrder when move cup
		Blue->setZOrder(3);
		target->setZOrder(4);

		//Control the range of cup, must not exceed the Rect of screen
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point TargetPosition = target->getPosition() + touch->getDelta();
		if (TargetPosition.x > visibleSize.width - target->getContentSize().width / 2 * target->getScale())
			TargetPosition.x = visibleSize.width - target->getContentSize().width / 2 * target->getScale();
		if (TargetPosition.x < target->getContentSize().width / 2 * target->getScale())
			TargetPosition.x = target->getContentSize().width / 2 * target->getScale();
		if (TargetPosition.y > visibleSize.height - 150.0)
			TargetPosition.y = visibleSize.height - 150.0;
		if (TargetPosition.y < 200.0)
			TargetPosition.y = 200.0;
		target->setPosition(TargetPosition);

		Blue->setScale(target->getScale());
		Blue->setPosition(TargetPosition);

		//for (auto cup = m_Cup.begin(); cup != m_Cup.end(); cup++)
		//{
		//	auto Interval = target->getPositionX() - (*cup)->getPositionX();
		//	if (target != (*cup) && Interval>-(target->getContentSize().width / 2 * target->getScale() + (*cup)->getContentSize().width / 2 * (*cup)->getScale()) && Interval < target->getContentSize().width / 2 * target->getScale() + (*cup)->getContentSize().width / 2 * (*cup)->getScale())
		//	{
		//		Red->setScale((*cup)->getScale());
		//		Red->setPosition((*cup)->getPosition());
		//	}
		//	else if (cup == m_Cup.end())
		//		cup = m_Cup.begin();
		//	else
		//		Red->setPosition(OutScreen);
		//}
		if (target != Acup && target->getPositionX() - Acup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + AHWidth) && target->getPositionX() - Acup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + AHWidth)
		{
			//Red Set Scale from target'Scale
			Red->setScale(Acup->getScale());
			Red->setPosition(Acup->getPosition());
		}
		else if (target != Bcup && target->getPositionX() - Bcup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + BHWidth) && target->getPositionX() - Bcup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + BHWidth)

		{
			Red->setScale(Bcup->getScale());
			Red->setPosition(Bcup->getPosition());
		}
		else if (target != Ccup && target->getPositionX() - Ccup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + CHWidth) && target->getPositionX() - Ccup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + CHWidth)

		{
			Red->setScale(Ccup->getScale());
			Red->setPosition(Ccup->getPosition());
		}
		else if (target != Dcup && target->getPositionX() - Dcup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + DHWidth) && target->getPositionX() - Dcup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + DHWidth)
		{
			Red->setScale(Dcup->getScale());
			Red->setPosition(Dcup->getPosition());
		}
		else
			Red->setPosition(OutScreen);
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{		
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		//The water of cup from Pour cup to
		int from, to;


		//Select the DestinationPoint of cup after PourWater
		Point DestinationPoint;
		auto i = m_Cup.begin();
		if (target == (*i++))
		{
			from = 0;
			DestinationPoint = APoint;
		}
		else 	if (target == (*i++))
		{
			from = 1;
			DestinationPoint = BPoint;
		}
		else 	if (target == (*i++))
		{
			from = 2;
			DestinationPoint = CPoint;
		}
		else 	if (target == (*i))
		{
			from = 3;
			DestinationPoint = DPoint;
		}
			
	
		//Rotate and rotateback
		auto rotate = RotateBy::create(0.3f, 110.0f);
		auto rotateback = RotateBy::create(0.3f, -110.0f);
		if (target != Acup && target->getPositionX() - Acup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + AHWidth) && target->getPositionX() - Acup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + AHWidth)
		{
			to = 0;
			PourAction(target, Acup, from, to, rotate, rotateback, DestinationPoint);
		}
		else if (target != Bcup && target->getPositionX() - Bcup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + BHWidth) && target->getPositionX() - Bcup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + BHWidth)
		{
			to = 1;
			PourAction(target, Bcup, from, to, rotate, rotateback, DestinationPoint);
		}
		else if (target != Ccup && target->getPositionX() - Ccup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + CHWidth) && target->getPositionX() - Ccup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + CHWidth)
		{
			to = 2;
			PourAction(target, Ccup, from, to, rotate, rotateback, DestinationPoint);
		}
		else if (target != Dcup && target->getPositionX() - Dcup->getPositionX()>-(target->getContentSize().width / 2 * target->getScale() + DHWidth) && target->getPositionX() - Dcup->getPositionX()<target->getContentSize().width / 2 * target->getScale() + DHWidth)
		{
			to = 3;
			PourAction(target, Dcup, from, to, rotate, rotateback, DestinationPoint);
		}
		else
			target->setPosition(DestinationPoint);

		target->setZOrder(2);
		Blue->setZOrder(1);
		Blue->setPosition(OutScreen);
		Red->setPosition(OutScreen);
		
		//Pass mission
		if (IsDestinationState())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound3.ogg", false);
			IsTouch = false;
			//Next level after 1.0 seconds
			scheduleOnce(schedule_selector(PourWater::my_update), 0.8);

		}
	};
	//Register the Listener Event, bind Sprite Acup
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, Acup);
	//Register the Listener Event, bind Sprite Bcup, Ccup, Dcup. Pay attention, Listener object has been cloned
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Bcup);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Ccup); 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Dcup);

	scheduleUpdate();

	setKeyboardEnabled(true);
	auto BacklListener = EventListenerKeyboard::create();
	//和回调函数绑定
	BacklListener->onKeyReleased = CC_CALLBACK_2(PourWater::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(BacklListener, this);

	return true;
}
void PourWater::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Director::getInstance()->replaceScene(TableViewTestLayer::createScene());
}
void PourWater::update(float dt)
{
	//Update the state of cups
	auto cup = m_Cup.begin();
	int i;
	for (i = 0; cup != m_Cup.end(); i++, cup++)
	{
		if(CurrentWarter[i]==0)
			(*cup)->setSpriteFrame("Bottle1-0.png");
		else if (CurrentWarter[i] / Capacity[i] == 1)
		{
			(*cup)->setSpriteFrame("Bottle1-100.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.2)
		{
			(*cup)->setSpriteFrame("Bottle1-10.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.3)
		{
			(*cup)->setSpriteFrame("Bottle1-20.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.4)
		{
			(*cup)->setSpriteFrame("Bottle1-30.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.5)
		{
			(*cup)->setSpriteFrame("Bottle1-40.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.6)
		{
			(*cup)->setSpriteFrame("Bottle1-50.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.7)
		{
			(*cup)->setSpriteFrame("Bottle1-60.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.8)
		{
			(*cup)->setSpriteFrame("Bottle1-70.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) <= 0.9)
		{
			(*cup)->setSpriteFrame("Bottle1-80.png");
		}
		else if (float(CurrentWarter[i]) / float(Capacity[i]) < 1.0)
		{
			(*cup)->setSpriteFrame("Bottle1-90.png");
		}
	}


	//Update the water label 
	auto cu = m_Cup.begin();
	for (auto la = Current_Capacity.begin(); la != Current_Capacity.end(); la++, cu++)
	{
		(*la)->setPosition((*cu)->getPositionX(), (*cu)->getPositionY() - (*cu)->getContentSize().height / 2 * (*cu)->getScale() - (*la)->getContentSize().height);
	}


	i = 0;
	//Update Current_Capacity In Cups
	for (auto cuca = Current_Capacity.begin(); cuca != Current_Capacity.end(); cuca++, i++)
		(*cuca)->setString(" "+Value(CurrentWarter[i]).asString() + " / " + Value(Capacity[i]).asString());

	//Update Steps
	CurrentStep->setString(Value(m_steps).asString());
	CurrentBsetStep->setString(Value(m_BestSteps).asString());
}
//Next level
void PourWater::my_update(float dt)
{
	IsTouch = false;
	auto Firework = Sprite::create("Clear1.png");
	Firework->setPosition(121, visibleSize.height / 2 + 60);
	addChild(Firework, 14);
	Firework->setScale(2.0f);
	Firework->runAction(createAnimate());

	auto Firework2 = Sprite::create("Clear1.png");
	Firework2->setPosition(678, visibleSize.height / 2 + 60);
	addChild(Firework2, 14);
	Firework2->setScale(2.0f);
	Firework2->runAction(createAnimate());


	int StarLevel;
	if (m_steps >= TheBestSteps + 3)
	{
		StarLevel = 1;
	}
	if (m_steps > TheBestSteps&&m_steps < TheBestSteps + 3)
	{
		StarLevel = 2;
	}
	if (m_steps <= TheBestSteps)
	{
		StarLevel = 3;
	}
	WinPicture = Sprite::createWithSpriteFrameName(StringUtils::format("win%d.png", StarLevel));
	WinPicture->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(WinPicture, 12);

	VirCurrentBsetStep = Label::createWithTTF("", "fonts/Futura (Light).ttf", 50);
	VirCurrentBsetStep->setString(Value(m_BestSteps == 0 ? m_steps : m_BestSteps).asString());
	VirCurrentBsetStep->setPosition(430, 206);
	VirCurrentBsetStep->setColor(Color3B(55, 193, 249));
	addChild(VirCurrentBsetStep, 14);

	VirtualCurrentStep = Label::createWithTTF("", "fonts/Futura (Light).ttf", 50);
	VirtualCurrentStep->setString(Value(m_steps).asString());
	VirtualCurrentStep->setPosition(430, 136);
	VirtualCurrentStep->setColor(Color3B(55,193,249));
	addChild(VirtualCurrentStep, 14);

	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";
	sqlite3_open(path.c_str(), &pdb);
	std::string sql;
	char **re;

	if (m_BestSteps > m_steps || m_BestSteps==0)
	{
		sql = "update record set beststeps=";
		sql += Value(m_steps).asString();
		sql+=" where level=";
		sql += Value(UserDefault::getInstance()->getIntegerForKey("Chapter") + 1 ).asString();
		sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	}

	//Set next level stars if next level stars==-1
	sql = "select stars from record where level=";
	sql += Value(UserDefault::getInstance()->getIntegerForKey("Chapter") + 1 + 1).asString();
	sqlite3_get_table(pdb, sql.c_str(), &re, NULL,NULL,NULL);
	if (UserDefault::getInstance()->getIntegerForKey("Chapter") + 1 < 36 && Value(re[1]).asInt()==-1)
	{
		sql = "update record set stars=0 where level=";
		sql += Value(UserDefault::getInstance()->getIntegerForKey("Chapter") + 1 + 1).asString();
		sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	}
	sqlite3_free_table(re);

	//Set this level stars
	sql = "select stars from record where level=";
	sql += Value(UserDefault::getInstance()->getIntegerForKey("Chapter") + 1 ).asString();
	sqlite3_get_table(pdb, sql.c_str(), &re, NULL, NULL, NULL);

	Preview = UserDefault::getInstance()->getIntegerForKey("IQ");
	Cha = StarLevel - Value(re[1]).asInt()>0 ? StarLevel - Value(re[1]).asInt():0;

	if (Value(re[1]).asInt() < StarLevel)
	{
		UserDefault::getInstance()->setIntegerForKey("IQ", UserDefault::getInstance()->getIntegerForKey("IQ") + Cha);
		sql = "update record set stars=";
		sql += Value(StarLevel).asString();
		sql +=" where level=";
		sql += Value(UserDefault::getInstance()->getIntegerForKey("Chapter") + 1 ).asString();
		sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	}
	sqlite3_free_table(re);
	sqlite3_close(pdb);

	scheduleOnce(schedule_selector(PourWater::my_update2), 5.0);
}
void PourWater::my_update2(float dt)
{
	LabelIQ->setVisible(false);
	removeChild(VirtualCurrentStep, false);
	removeChild(VirCurrentBsetStep, false);
	
	IsIntoNext = true;
	WinPicture->setSpriteFrame("victory.png");

	Next->setVisible(true);
	Restart->setVisible(true);
	m_Menu->setVisible(true);

	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 99);
	IQ->setString("IQ:");
	IQ->setColor(Color3B(214, 215, 250));
	IQ->setPosition(100, 325);
	addChild(IQ, 20);

	scheduleOnce(schedule_selector(PourWater::my_update3), 0.0);
}
void PourWater::my_update3(float dt)
{
	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString(Value(Preview).asString());
	IQ->setPosition(60, 230);
	IQ->setColor(Color3B(214, 215, 250));
	addChild(IQ, 20);
	NextPoint = IQ->getPositionX()*0.9 + IQ->getContentSize().width / 2 + 10;
	scheduleOnce(schedule_selector(PourWater::my_update4), 0.2);
}
void PourWater::my_update4(float dt)
{
	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString("+");
	addChild(IQ, 20);
	IQ->setColor(Color3B(214, 215, 250));
	//IQ->runAction(MoveTo::create(0.5f, Point(145, 240)));
	IQ->runAction(MoveTo::create(0.5f, Point(NextPoint + IQ->getContentSize().width / 2, 240)));
	NextPoint = NextPoint + IQ->getContentSize().width + 10;
	scheduleOnce(schedule_selector(PourWater::my_update5), 0.2);
}
void PourWater::my_update5(float dt)
{
	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString(Value(Cha).asString());
	addChild(IQ, 20);
	IQ->setColor(Color3B(214, 215, 250));
	//IQ->runAction(MoveTo::create(0.4, Point(205, 230)));
	IQ->runAction(MoveTo::create(0.5f, Point(NextPoint + IQ->getContentSize().width / 2, 230)));
	NextPoint = NextPoint + IQ->getContentSize().width + 10;
	scheduleOnce(schedule_selector(PourWater::my_update6), 0.2);
}
void PourWater::my_update6(float dt)
{
	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString("=");
	IQ->setColor(Color3B(214, 215, 250));
	addChild(IQ, 20);
	//IQ->runAction(MoveTo::create(0.4, Point(273, 240)));
	IQ->runAction(MoveTo::create(0.5f, Point(NextPoint + IQ->getContentSize().width / 2, 240)));
	NextPoint = NextPoint + IQ->getContentSize().width + 10;
	scheduleOnce(schedule_selector(PourWater::my_update7), 0.2);
}
void PourWater::my_update7(float dt)
{
	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString(Value(UserDefault::getInstance()->getIntegerForKey("IQ")).asString());
	IQ->setColor(Color3B(214, 215, 250));
	addChild(IQ, 20);
	//IQ->runAction(MoveTo::create(0.4, Point(365, 230)));
	IQ->runAction(MoveTo::create(0.5f, Point(NextPoint + IQ->getContentSize().width / 2, 230)));
	//NextPoint = IQ->getPositionX() + IQ->getContentSize().width / 2 + 10;
}

//Initialize the water
void PourWater::Initialize(int des[], int cur[], int cap[])
{
	for (int i = 0; i < 4; i++)
	{
		DestinationWater[i]	= des[i];
		CurrentWarter[i]	= cur[i];
		Capacity[i]			= cap[i];
	}
}

bool PourWater::IsDestinationState()
{
	for (int i = 0; i < 4; i++)
	{
		if (DestinationWater[i] != CurrentWarter[i])
			return false;
	}
	return true;
}

Animate* PourWater::createAnimate()
{
	int iFrameNum = 50;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++) 
	{																										//The Rect(0, 0, 210, 210) part of this image	
																											//Rect(0, 0, 210, 210) Point(0, 0) to Point(210, 210)
		frame = SpriteFrame::create(StringUtils::format("Clear%d.png", i), Rect(0, 0, 210, 210));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.08);

	Animate* action = Animate::create(animation);

	return action;
}
void PourWater::PourAction(Sprite* target, Sprite* destination, int from, int to, RotateBy* rotate, RotateBy* rotateback, Point DestinationPoint)
{
	m_steps++;
	Red->setPosition(destination->getPosition());
	if (target->getPositionX() > destination->getPositionX())
	{
		rotate = RotateBy::create(0.3f, -110.0f);
		rotateback = RotateBy::create(0.3f, 110.0f);
	}
	if (flag)
	{
		flag = false;
		Blue->setVisible(false);
		auto moveto = MoveTo::create(0.01f, DestinationPoint);
		CallFunc* callfunc = CallFunc::create([&]()
		{
			flag = true;
			Blue->setVisible(true);
		});
		auto action = Sequence::create(rotate, rotateback, moveto, callfunc, NULL);
		target->runAction(action);
	}
	//The action of Pourwater
	int remain = Capacity[to] - CurrentWarter[to];
	if (Capacity[to] != CurrentWarter[to])
	{
		if (CurrentWarter[from]< remain)
		{
			CurrentWarter[to] += CurrentWarter[from];
			CurrentWarter[from] = 0;
		}
		else
		{
			CurrentWarter[to] = Capacity[to];
			CurrentWarter[from] -= remain;
		}
	}
}

void PourWater::SetWater()
{
	switch (UserDefault::getInstance()->getIntegerForKey("Chapter"))
	{
		case 0:
		{
				  int des1[] = { 1, 1, 1, 0 };
				  int cur1[] = { 3, 0, 0, 0 };
				  int cap1[] = { 3, 2, 1, 1 };
				  Initialize(des1, cur1, cap1);
				  TheBestSteps = 2;
				  break;
		}
		case 1:
		{
				  int cur2[] = { 4, 0, 0, 0 };
				  int des2[] = { 2, 1, 1, 0 };
				  int cap2[] = { 4, 2, 1, 1 };
				  Initialize(des2, cur2, cap2);
				  TheBestSteps = 2;
				  break;
		}
		case 2:
		{
				  int cur3[] = { 6, 0, 0, 0 };
				  int des3[] = { 2, 2, 2, 0 };
				  int cap3[] = { 6, 4, 3, 1 };
				  Initialize(des3, cur3, cap3);
				  TheBestSteps = 4;
				  break;
		}
		case 3:
		{
				  int cur4[] = { 9, 0, 0, 0 };
				  int des4[] = { 3, 3, 3, 0 };
				  int cap4[] = { 9, 7, 6, 1 };
				  Initialize(des4, cur4, cap4);
				  TheBestSteps = 7;
				  break;
		}
		case 4:
		{
				  int cur5[] = { 10, 0, 0, 0 };
				  int des5[] = { 4, 3, 3, 0 };
				  int cap5[] = { 10, 8, 7, 1 };
				  Initialize(des5, cur5, cap5);
				  TheBestSteps = 9;
				  break;
		}
		case 5:
		{
				  int cur6[] = { 11, 0, 0, 0 };
				  int des6[] = { 4, 4, 3, 0 };
				  int cap6[] = { 11, 9, 6, 1 };
				  Initialize(des6, cur6, cap6);
				  TheBestSteps = 8;
				  break;
		}
		case 6:
		{
				  int cur7[] = { 13, 0, 0, 0 };
				  int des7[] = { 5, 4, 4, 0 };
				  int cap7[] = { 13, 9, 7, 3 };
				  Initialize(des7, cur7, cap7);
				  TheBestSteps = 7;
				  break;
		}
		case 7:
		{
				  int cur8[] = { 12, 0, 0, 0 };
				  int des8[] = { 4, 4, 4, 0 };
				  int cap8[] = { 12, 10, 7, 1 };
				  Initialize(des8, cur8, cap8);
				  TheBestSteps = 8;
				  break;
		}
		case 8:
		{
				  int cur9[] = { 13, 0, 0, 0 };
				  int des9[] = { 5, 4, 4, 0 };
				  int cap9[] = { 13, 10, 7, 2 };
				  Initialize(des9, cur9, cap9);
				  TheBestSteps = 7;
				  break;
		}
		case 9:
		{
				  int cur10[] = { 14, 0, 0, 0 };
				  int des10[] = { 5, 5, 4, 0 };
				  int cap10[] = { 14, 11, 4, 3 };
				  Initialize(des10, cur10, cap10);
				  TheBestSteps = 6;
				  break;
		}
		case 10:
		{
				  int cur11[] = { 12, 0, 0, 0 };
				  int des11[] = { 4, 4, 4, 0 };
				  int cap11[] = { 12, 10, 9, 1 };
				  Initialize(des11, cur11, cap11);
				  TheBestSteps = 11;
				  break;
		}
		case 11:
		{
				  int cur12[] = { 14, 0, 0, 0 };
				  int des12[] = { 5, 5, 4, 0 };
				  int cap12[] = { 14, 10, 9, 3 };
				  Initialize(des12, cur12, cap12);
				  TheBestSteps = 11;
				  break;
		}
		case 12:
		{
				   int cur13[] = { 15, 0, 0, 0 };
				   int des13[] = { 5, 5, 5, 0 };
				   int cap13[] = { 15, 11, 6, 3 };
				   Initialize(des13, cur13, cap13);
				   TheBestSteps = 10;
				   break;
		}
		case 13:
		{
				   int cur14[] = { 16, 0, 0, 0 };
				   int des14[] = { 6, 5, 5, 0 };
				   int cap14[] = { 16, 13, 9, 2 };
				   Initialize(des14, cur14, cap14);
				   TheBestSteps = 8;
				   break;
		}
		case 14:
		{
				   int cur15[] = { 15, 0, 0, 0 };
				   int des15[] = { 5, 5, 5, 0 };
				   int cap15[] = { 15, 10, 7, 4 };
				   Initialize(des15, cur15, cap15);
				   TheBestSteps = 9;
				   break;
		}
		case 15:
		{
				   int cur16[] = { 16, 0, 0, 0 };
				   int des16[] = { 6, 5, 5, 0 };
				   int cap16[] = { 16, 16, 10, 2 };
				   Initialize(des16, cur16, cap16);
				   TheBestSteps = 10;
				   break;
		}
		case 16:
		{
				   int cur17[] = { 17, 0, 0, 0 };
				   int des17[] = { 6, 6, 5, 0 };
				   int cap17[] = { 17, 14, 14, 2 };
				   Initialize(des17, cur17, cap17);
				   TheBestSteps = 10;
				   break;
		}
		case 17:
		{
				   int cur18[] = { 17, 14, 0, 0 };
				   int des18[] = { 11, 10, 10, 0 };
				   int cap18[] = { 17, 14, 11, 2 };
				   Initialize(des18, cur18, cap18);
				   TheBestSteps = 10;
				   break;
		}
		case 18:
		{
				   int cur19[] = { 15, 0, 0, 0 };
				   int des19[] = { 5, 5, 5, 0 };
				   int cap19[] = { 15, 14, 11, 1 };
				   Initialize(des19, cur19, cap19);
				   TheBestSteps = 13;
				   break;
		}
		case 19:
		{
				   int cur20[] = { 18, 0, 0, 0 };
				   int des20[] = { 6, 6, 6, 0 };
				   int cap20[] = { 18, 16, 16, 5 };
				   Initialize(des20, cur20, cap20);
				   TheBestSteps = 12;
				   break;
		}
		case 20:
		{
				   int cur21[] = { 18, 12, 0, 0 };
				   int des21[] = { 10, 10, 10, 0 };
				   int cap21[] = { 18, 16, 11, 9 };
				   Initialize(des21, cur21, cap21);
				   TheBestSteps = 14;
				   break;
		}
		case 21:
		{
				   int cur22[] = { 19, 12, 0, 0 };
				   int des22[] = { 11, 10, 10, 0 };
				   int cap22[] = { 19, 16, 11, 8 };
				   Initialize(des22, cur22, cap22);
				   TheBestSteps = 9;
				   break;
		}
		case 22:
		{
				   int cur23[] = { 20, 0, 0, 0 };
				   int des23[] = { 10, 10, 0, 0 };
				   int cap23[] = { 20, 15, 15, 4 };
				   Initialize(des23, cur23, cap23);
				   TheBestSteps = 13;
				   break;
		}
		case 23:
		{
				   int cur24[] = { 21, 0, 0, 0 };
				   int des24[] = { 7, 7, 7, 0 };
				   int cap24[] = { 21, 15, 8, 5 };
				   Initialize(des24, cur24, cap24);
				   TheBestSteps = 11;
				   break;
		}
		case 24:
		{
				   int cur25[] = { 21, 0, 0, 0 };
				   int des25[] = { 7, 7, 7, 0 };
				   int cap25[] = { 21, 17, 9, 3 };
				   Initialize(des25, cur25, cap25);
				   TheBestSteps = 15;
				   break;
		}
		case 25:
		{
				   int cur26[] = { 21, 9, 0, 0 };
				   int des26[] = { 10, 10, 10, 0 };
				   int cap26[] = { 21, 18, 14, 9 };
				   Initialize(des26, cur26, cap26);
				   TheBestSteps = 12;
				   break;
		}
		case 26:
		{
				   int cur27[] = { 22, 0, 0, 0 };
				   int des27[] = { 8, 7, 7, 0 };
				   int cap27[] = { 22, 19, 16, 3 };
				   Initialize(des27, cur27, cap27);
				   TheBestSteps = 17;
				   break;
		}
		case 27:
		{
				   int cur28[] = { 23, 0, 0, 0 };
				   int des28[] = { 8, 8, 7, 0 };
				   int cap28[] = { 23, 19, 16, 3 };
				   Initialize(des28, cur28, cap28);
				   TheBestSteps = 19;
				   break;
		}
		case 28:
		{
				   int cur29[] = { 23, 7, 0, 0 };
				   int des29[] = { 10, 10, 10, 0 };
				   int cap29[] = { 23, 18, 16, 9 };
				   Initialize(des29, cur29, cap29);
				   TheBestSteps = 18;
				   break;
		}
		case 29:
		{
				   int cur30[] = { 24, 0, 0, 0 };
				   int des30[] = { 8, 8, 8, 0 };
				   int cap30[] = { 24, 18, 16, 3 };
				   Initialize(des30, cur30, cap30);
				   TheBestSteps = 11;
				   break;
		}
		case 30:
		{
				   int cur31[] = { 24, 6, 0, 0 };
				   int des31[] = { 10, 10, 10, 0 };
				   int cap31[] = { 24, 21, 16, 8 };
				   Initialize(des31, cur31, cap31);
				   TheBestSteps = 16;
				   break;
		}
		case 31:
		{
				   int cur32[] = { 25, 0, 0, 0 };
				   int des32[] = { 9, 9, 7, 0 };
				   int cap32[] = { 25, 19, 11, 8 };
				   Initialize(des32, cur32, cap32);
				   TheBestSteps = 18;
				   break;
		}
		case 32:
		{
				   int cur33[] = { 25, 5, 0, 0 };
				   int des33[] = { 10, 10, 10, 0 };
				   int cap33[] = { 25, 18, 16, 9 };
				   Initialize(des33, cur33, cap33);
				   TheBestSteps = 21;
				   break;
		}
		case 33:
		{
				   int cur34[] = { 26, 0, 0, 0 };
				   int des34[] = { 9, 9, 8, 0 };
				   int cap34[] = { 26, 19, 13, 7 };
				   Initialize(des34, cur34, cap34);
				   TheBestSteps = 17;
				   break;
		}
		case 34:
		{
				   int cur35[] = { 26, 4, 0, 0 };
				   int des35[] = { 10, 10, 10, 0 };
				   int cap35[] = { 26, 19, 13, 7 };
				   Initialize(des35, cur35, cap35);
				   TheBestSteps = 16;
				   break;
		}
		case 35:
		{
				   int cur36[] = { 27, 3, 0, 0 };
				   int des36[] = { 10, 10, 10, 0 };
				   int cap36[] = { 27, 20, 13, 7 };
				   Initialize(des36, cur36, cap36);
				   TheBestSteps = 17;
				   break;
		}
		default:		break;
	}
}