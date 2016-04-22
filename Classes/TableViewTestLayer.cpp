#include "TableViewTestLayer.h"
Scene* TableViewTestLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TableViewTestLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TableViewTestLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *sprite = Sprite::create("b1.png");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(sprite, 0);
	
	auto Back = Sprite::createWithSpriteFrameName("back.png");
	Back->setAnchorPoint(Point(0, 0));
	Back->setPosition(0, visibleSize.height - 400 - 80);
	addChild(Back, 1);

	UserDefault::getInstance()->setIntegerForKey("Chapter", -1);

	
	CreateDatabase();

	//创建一个talbleview 将datasource设置为当前的类的对象 tableview的显示区域大小为 300 * 300
	TableView* tableView = TableView::create(this, visibleSize);
	__tableView = tableView;
	//设置tableview为水平方向  ScrollView::Direction::VERTICAL 为垂直,ScrollView::Direction::HORIZONTAL 为水平
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	//设置位置
	tableView->setPosition(0, 0);
	//设置代理对象
	tableView->setDelegate(this);
	// 填充顺序
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//添加tableview到当前layer
	this->addChild(tableView,1);
	//加载tableview 
	tableView->reloadData();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		if (Back->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(LevelSelect::createScene());
		}
		return true;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		if (CellID >= 0)
		{
			TableViewCell *cell = __tableView->cellAtIndex(CellID);
			for (int i = 0 + NumberOfCell * CellID; i < (CellID + 1) * NumberOfCell; ++i)
			{
				//if ((Sprite*)cell->getChildByTag(1000 + i))
				if (Value(result[colum*(i + 1) + 1]).asInt() >= 0)
				{
					Sprite* sprite = (Sprite*)cell->getChildByTag(1000 + i);
					if (sprite->boundingBox().containsPoint(touch->getLocation()))
					{
						UserDefault::getInstance()->setIntegerForKey("Chapter", i);
						Director::getInstance()->replaceScene(PourWater::createScene());
						break;
					}	
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setKeyboardEnabled(true);
	auto BacklListener = EventListenerKeyboard::create();
	//和回调函数绑定
	BacklListener->onKeyReleased = CC_CALLBACK_2(TableViewTestLayer::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(BacklListener, this);

    return true;
}
void TableViewTestLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Director::getInstance()->replaceScene(LevelSelect::createScene());
}
void TableViewTestLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CellID = cell->getIdx();
}

Size TableViewTestLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(800, 480);
}

//由于tableview是动态获取数据的，该方法在初始化时会被调用一次，之后在每个隐藏的cell显示出来的时候都会调用
TableViewCell* TableViewTestLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	// 在重用队列中获取一个cell 然后判断cell是否为空 不为空则创建一个新的
	TableViewCell *cell = table->dequeueCell();
	
	if (!cell) 
	{
		cell = new TableViewCell();
		cell->autorelease();
	}
	//else
	//{
		cell->removeAllChildrenWithCleanup(true);
		level = idx * NumberOfCell+1;
		ChildTAg = idx * NumberOfCell;
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Sprite *sprite = Sprite::createWithSpriteFrameName(StringUtils::format("sta%d.png", Value(result[colum*level + 1]).asInt()));
				sprite->setScale(0.5f);
				sprite->setPosition(Point(170 + 150 * j, 390 - 140 * i));
				sprite->setTag(1000 + (ChildTAg++));
				cell->addChild(sprite);

				if (Value(result[colum*level + 1]).asInt()>=0)	//第一行是列名，随后的行才是值
				{
					Label *label = Label::createWithTTF(Value(level++).asString(), "fonts/Futura (Light).ttf", 38);
					label->setPosition(Point(170 + 150 * j, 390 - 140 * i - 12));
					cell->addChild(label,1);
				}
			}
		}
	//}
	return cell;
}
ssize_t TableViewTestLayer::numberOfCellsInTableView(TableView *table)
{
    return 3;
}
void TableViewTestLayer::scrollViewDidScroll(ScrollView* view)
{
}
void TableViewTestLayer::scrollViewDidZoom(ScrollView* view)
{
}
void TableViewTestLayer::CreateDatabase()
{
	
	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";//2

	std::string sql;
	//sqlite3_open(path.c_str(), &pdb);


	//int res;
	//res = 
	sqlite3_open(path.c_str(), &pdb);//3
	//if (res != SQLITE_OK)
	//{
	//	sql = "create table record(stage integer, level integer, stars integer, beststeps integer)";
	//	sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	//	//Insert
	//	sql = "insert into record  values(1, 1, 0, 0)";
	//	sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//	for (int i = 2; i <= 36; i++)
	//	{
	//		sql = StringUtils::format("insert into record  values(1, %d, -1, 0)", i);
	//		//sql = "insert into record  values(1,";
	//		//sql += Value(i).asString();
	//		//sql += ", -1, 0)";
	//		sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//	}
	//}
	if (!UserDefault::getInstance()->getIntegerForKey("IsCreateDatabase", 0))
	{	//Create Table 
		sql = "create table record(stage integer, level integer, stars integer, beststeps integer)";
		sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

		//Insert
		sql = "insert into record  values(1, 1, 0, 0)";
		sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
		for (int i = 2; i <= 36; i++)
		{
			sql = StringUtils::format("insert into record  values(1, %d, -1, 0)", i);
			//sql = "insert into record  values(1,";
			//sql += Value(i).asString();
			//sql += ", -1, 0)";
			sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
		}
		UserDefault::getInstance()->setIntegerForKey("IsCreateDatabase", 1);
	}

	//sql = "insert into record  values(1, 1, 0, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 2, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 3, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 4, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 5, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 6, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 7, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 8, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 9, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 10, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 11, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 12, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 13, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 14, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 15, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 16, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 17, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 18, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 19, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 20, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 21, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 22, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 23, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 24, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 25, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 26, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 27, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 28, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 29, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 30, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 31, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 32, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 33, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 34, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 35, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	//sql = "insert into record  values(1, 36, -1, 0)";
	//sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	//Query   
	sqlite3_get_table(pdb, "select level, stars from record", &result, &row, &colum, NULL);//1
	//log("row is %d,column is %d", row, colum);

	//for (int i = 1; i <= row; i++)//2
	//{
	//	for (int j = 0; j<colum; j++)
	//	{
	//		log("%s", result[i*colum + j]);
	//	}
	//}

	//Delete
	//sql = "delete from student where ID=1";
	//result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);


	//Close Database
	sqlite3_close(pdb);
}
