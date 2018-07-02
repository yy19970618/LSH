
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
		return max;
	}
	static void findMax(float *p, int d, int *ret)
	{
		int max = 0, nextmax = 1;
		if(abs(*(p)) < abs(*(p + 1))) {max=1;nextmax=0;}
		for (int i = 2; i < d; i++)
		{
			if (abs(*(p + i)) > abs(*(p + max)))
			{
				nextmax = max;
				max = i;
			}

		}
		if (*(p + max) < 0)
			max += d;
		if (*(p + nextmax) < 0)
			nextmax += d;
		ret[0] = max; ret[1] = nextmax;
	}
	//将向量p单位化
	static void pointUnit(float *p) {
		float count = 0;
		for (int i = 0; i < 1024; i++)
		{
			count = (*(p+i)) * (*(p+i)) + count;
		}
		count = sqrt(count);
		for (int i = 0; i < 1024; i++)
		{
			*(p + i) = *(p + i) / count;
		}
	}

};


		

#pragma once
