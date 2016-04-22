#include"LevelSelect.h"

Scene* LevelSelect::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelSelect::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelSelect::init()
{ 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	auto BackGround = Sprite::createWithSpriteFrameName("b8.png");
	BackGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(BackGround, 0);
	 
	auto Stage = Sprite::createWithSpriteFrameName("stage.png");
	Stage->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(Stage, 1);

	auto Back = Sprite::createWithSpriteFrameName("back.png");
	Back->setAnchorPoint(Point(0, 0));
	Back->setPosition(0, visibleSize.height - 400 - 80);
	addChild(Back, 1);



	auto IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString("IQ:" + Value(UserDefault::getInstance()->getIntegerForKey("IQ")).asString());
	IQ->setColor(Color3B(255, 255, 255));
	IQ->setPosition(220, 370);
	addChild(IQ, 2);

	auto Pour = Sprite::createWithSpriteFrameName("start2.png");
	Pour->setAnchorPoint(Point(0, 0));
	Pour->setPosition(422, visibleSize.height - 282 - 70);
	addChild(Pour, 2); 

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		if (Pour->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(TableViewTestLayer::createScene());
		}
		if (Back->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(HelloScene::createScene());

		}


		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setKeyboardEnabled(true);
	auto BacklListener = EventListenerKeyboard::create();
	//和回调函数绑定
	BacklListener->onKeyReleased = CC_CALLBACK_2(LevelSelect::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(BacklListener, this);


	return true;
}
void LevelSelect::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Director::getInstance()->replaceScene(HelloScene::createScene());
}