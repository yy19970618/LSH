#include"Math.h"
#include "Buckets.h"
#include<ostream>
#include<math.h>


class hash_helpers{
public:
	//�ҵ�p�о���ֵ���ķ����±�
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
	//������p��λ��
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
