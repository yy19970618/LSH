#include<iostream>
#include <fstream>
#include<vector>
#include<string>
struct Point{
	int id;
	float value[1024];
};
/*�������ݽṹ֮Ͱ��Ͱ�ǲ�ѯ�Ļ�����λ
*/
class Buckets
{
public:
	int findMIn(Point *p,std::ifstream *file) 
	{
		if (array.size() <= 0) 
			readBucket(file);
		float min = countDistance(p, array[0]);
		int minindex = 0;
		for (int i = 1; i < size; i++)
		{
			float temp = countDistance(array[i],p,min);
			if (min > temp&&temp!=-1)
			{
				min = temp; minindex = array[i]->id;
			}
		}
		return minindex;

	};//��Ͱ���ҵ���p�����ڽ�
	float countDistance(Point *q, Point *p) {
		float count = 0;
		for (int i = 0; i < 1024; i++)
		{
			count = count + (p->value[i] - q->value[i])*(p->value[i] - q->value[i]);
		}
		return count;
	}
	float countDistance(Point *q, Point *p,float min) {
		float count = 0;
		for (int i = 0; i < 1024; i++)
		{
			count = count + (p->value[i] - q->value[i])*(p->value[i] - q->value[i]);
			if (count > min)
				return -1;
		}
		return count;
	}
	void readBucket(std::ifstream *file) {
		Point *p;
		while (read_point(file, p))
			array.push_back(p);
		size = array.size();
	};
	//����
	static bool read_point(std::ifstream *file, Point *p)
	{
		if (file->peek() == EOF)
			return false;
		float a;
		file->read((char*)&a, sizeof(a));
		p->id = (int)a;//��id
		for (int i = 0; i < 1024; i++)
		{//������
			file->read((char*)&a, sizeof(a));
			p->value[i] = a;
		}
		return true;
	};
	//д������Ͱ
	static void writePoint(Point *p,std::ofstream *file) {
		file->write((char*)&(p->id), sizeof(p->id));
		file->write((char*)&(p->value), sizeof(p->value));
	};
private:
	std::vector<Point*> array;//Ͱ�����ݼ�
	int size;//Ͱ�����ݵ����

};
#pragma once