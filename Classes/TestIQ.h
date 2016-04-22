#ifndef		__TestIQ_H__
#define		__TestIQ_H__

#include "AllHeadFileAndNamespace.h"
USING_NS_CC;
class TestIQ : public LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(TestIQ);
	void my_update(float dt);
	void my_update2(float dt);
private:
	Sprite *Dian;
	Sprite *Test;
};

#endif 