/*
    文件名：    AnimationUtil .h
    描　述：    动画创建工具类
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)
*/
#ifndef __AnimationUtil_H__
#define __AnimationUtil_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:
    /* 根据文件名字前缀创建动画对象 */
    static Animation* createWithSingleFrameName(const char* name, float delay, int iLoops);

    /* 根据文件名字前缀创建动画对象，指定动画图片数量 */
    static Animation* createWithFrameNameAndNum(const char* name, int iNum, float delay, int iLoops);
};

#endif