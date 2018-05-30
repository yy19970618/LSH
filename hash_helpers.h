#include"Math.h"
#include "Buckets.h"
#include<ostream>
#include<math.h>


class hash_helpers{
public:
	//找到p中绝对值最大的分量下标
	static int findMax(float *p,int d)
	{
		int max = 0;
		for (int i = 1; i < d; i++)
		{
			if (abs(*(p+i)) > abs(*(p+max)))
			{
				max = i;
			}
		}
		if (*(p + max) < 0)
			max += d;
		return ++max;
	}
	//将向量p单位化
	static void pointUnit(Point* p) {
		float count = 0;
		for (int i = 0; i < 1024; i++)
		{
			count = p->value[i] * p->value[i] + count;
		}
		count = sqrt(count);
		for (int i = 0; i < 1024; i++)
		{
			p->value[i] = p->value[i] / count;
		}
	}

};


		

#pragma once
