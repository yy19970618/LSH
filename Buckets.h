#include<iostream>
#include <fstream>
#include<vector>
#include<string>
struct Point{
	int id;
	float value[1024];
};
/*基本数据结构之桶，桶是查询的基本单位
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

	};//在桶中找到点p的最邻近
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
		Point p;
		while (read_point(file, &p))
			array.push_back(&p);
		size = array.size();
	};
	//读点
	static bool read_point(std::ifstream *file, Point *p)
	{
		if (file->peek() == EOF)
			return false;
		float a;
		file->read((char*)&a, sizeof(a));
		p->id = (int)a;//读id
		for (int i = 0; i < 1024; i++)
		{//读向量
			file->read((char*)&a, sizeof(a));
			p->value[i] = a;
		}
		return true;
	};
	//写数据入桶
	static void writePoint(Point *p,std::fstream *file,int64_t numbyte) {
		int64_t a;
		file->seekp(numbyte);
		while (true) {
			file->read((char*)&a, sizeof(a));
			if (a < 4) {
				file->seekg(numbyte);
				a++;
				file->write((char*)&a, sizeof(a)); file->flush();
				numbyte = numbyte + 8 + 1025 * (a-1);
				file->seekg(numbyte);
				file->write((char*)&(p->id), sizeof(p->id));
				file->write((char*)&(p->value), sizeof(p->value)); file->flush();
				return;
			}
			else if (a == 4) {
				int64_t temp = file->tellg();
				temp = temp - 8;//记录要改写a的位置
				file->seekg(SEEK_END);
				int64_t loc = file->tellg();//下一个字块开头的位置
				file->seekg(temp); file->write((char*)&loc, sizeof(loc));
				file->seekg(SEEK_END);
				a = 0;file->write((char*)&a, sizeof(a)); file->flush();
				file->write((char*)&(p->id), sizeof(p->id));
				file->write((char*)&(p->value), sizeof(p->value)); file->flush();
				float b = 0;
				file->write((char*)&b, (sizeof(b)*1025)*3); file->flush();
				return;
				
			}
			else {
				numbyte = a;
				file->seekp(numbyte);
			}
		}
	};
	void freeArray()
	{
		for (int i = 0; i < size; i++)
			free(array[i]);
	}
private:
	std::vector<Point*> array;//桶的数据集
	int size;//桶中数据点个数

};
#pragma once