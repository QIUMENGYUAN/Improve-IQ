#ifndef __TABLEVIEWTESTSCENE_H__
#define __TABLEVIEWTESTSCENE_H__
#define NumberOfCell 12
#include "cocos2d.h"
#include "cocos-ext.h"
#include "AllHeadFileAndNamespace.h"
USING_NS_CC;
USING_NS_CC_EXT;
class TableViewTestLayer : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();

	CREATE_FUNC(TableViewTestLayer);
	
	/* 必须实现的函数 */
	// 当滑动tableview时触发该方法 参数为当前的tableview对象
	virtual void scrollViewDidScroll(ScrollView* view);
	// 当tableview被放大或缩小时触发该方法  参数为当前tableview对象
	virtual void scrollViewDidZoom(ScrollView* view);
	// 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	// 设置tableview的Cell大小
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	// 获取编号为idx的cell
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	// 设置tableview中cell的个数
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	void CreateDatabase();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
private:
	int ChildTAg = 0;
	TableView* __tableView;
	int CellID=-1;
	int level = 1;
	char **result;//查询结果
	char **result2;//查询结果
	int row;
	int colum;
	int Stars;
};

#endif // __TABLEVIEWTESTSCENE_H__
