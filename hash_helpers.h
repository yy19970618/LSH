#include"Math.h"
#include "Buckets.h"
#include<ostream>
#include<math.h>

class hash_helpers{
public:
	//�ҵ�p�о���ֵ���ķ����±�
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
