/*
    �ļ�����    AnimationUtil .h
    �衡����    ��������������
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
*/
#ifndef __AnimationUtil_H__
#define __AnimationUtil_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:
    /* �����ļ�����ǰ׺������������ */
    static Animation* createWithSingleFrameName(const char* name, float delay, int iLoops);

    /* �����ļ�����ǰ׺������������ָ������ͼƬ���� */
    static Animation* createWithFrameNameAndNum(const char* name, int iNum, float delay, int iLoops);
};

#endif