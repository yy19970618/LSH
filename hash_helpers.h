#include"Math.h"
#include "Buckets.h"
#include<ostream>
#include<math.h>

class hash_helpers{
public:
	//找到p中绝对值最大的分量下标
	static int findMax(float *p)
	{
		int max = 0;
		for (int i = 1; i < 1024; i++)
		{
			if (abs(*(p+i)) > abs(*(p+max)))
			{
				max = i;
			}
		}
	}

};


		

#pragma once
