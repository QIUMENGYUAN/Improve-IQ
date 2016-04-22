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
	
	/* ����ʵ�ֵĺ��� */
	// ������tableviewʱ�����÷��� ����Ϊ��ǰ��tableview����
	virtual void scrollViewDidScroll(ScrollView* view);
	// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
	virtual void scrollViewDidZoom(ScrollView* view);
	// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	// ����tableview��Cell��С
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	// ��ȡ���Ϊidx��cell
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	// ����tableview��cell�ĸ���
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	void CreateDatabase();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
private:
	int ChildTAg = 0;
	TableView* __tableView;
	int CellID=-1;
	int level = 1;
	char **result;//��ѯ���
	char **result2;//��ѯ���
	int row;
	int colum;
	int Stars;
};

#endif // __TABLEVIEWTESTSCENE_H__
