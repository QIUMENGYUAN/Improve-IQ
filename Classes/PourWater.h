#ifndef __PourWater_SCENE_H__
#define __PourWater_SCENE_H__
#include "AllHeadFileAndNamespace.h"
USING_NS_CC;
class PourWater : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(PourWater);
	void update(float dt);
	void my_update(float dt);
	void my_update2(float dt);
	void my_update3(float dt);
	void my_update4(float dt);
	void my_update5(float dt);
	void my_update6(float dt);
	void my_update7(float dt);
	void SetWater();
	void Initialize(int des[], int cur[], int cap[]);
	void PourAction(Sprite* source, Sprite* destination, int from, int to, RotateBy* rotate, RotateBy* rotateback, Point DestinationPoint);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
	bool IsDestinationState();
	Animate* createAnimate();
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vector<Sprite*> m_Cup;
	Vector<Label*> Current_Capacity;

	Sprite* WinPicture;
	Sprite* Next;
	Sprite* Restart;
	Sprite* m_Menu;
	Sprite* Blue;
	Sprite* Red;

	Label* CurrentStep;
	Label* VirtualCurrentStep;
	Label* CurrentBsetStep;
	Label* VirCurrentBsetStep;
	Label* LabelIQ;
	int DestinationWater[4];
	int CurrentWarter[4];
	int Capacity[4];

	int m_steps = 0;
	int m_BestSteps = 0;
	int m_Stars;
	int TheBestSteps;
	int m_IQ;
	bool IsTouch = true;
	bool IsIntoNext = false;
	int Preview;
	int Cha;
	float NextPoint;
	int Chapter = UserDefault::getInstance()->getIntegerForKey("Chapter");
	bool flag;
};

#endif // __HELLOWORLD_SCENE_H__
