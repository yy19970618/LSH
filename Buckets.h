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
	static int findMIn(Point *p,std::ifstream *file,std::vector<int32_t> idarray) 
	{
		std::vector<Point> array;
		for (int i = 0; i < idarray.size(); i++)
		{
			Point temp;
			int64_t numbyte = (int64_t)(idarray[i]* 1025.0 * 4.0);
			file->seekg(numbyte,std::ios::beg);
			Buckets::read_point(file, &temp);
			array.push_back(temp);
		}
		float min = countDistance(p, &array[0]);
		int minindex = 0;
		for (int i = 1; i < array.size(); i++)
		{
			float temp = countDistance(&array[i],p,min);
			if (min > temp&&temp!=-1)
			{
				min = temp; minindex = array[i].id;
			}
		}
		return minindex;

	};//在桶中找到点p的最邻近
	static float countDistance(Point *q, Point *p) {
		float count = 0;
		for (int i = 0; i < 1024; i++)
		{
			count = count + (p->value[i] - q->value[i])*(p->value[i] - q->value[i]);
		}
		return count;
	}
	static float countDistance(Point *q, Point *p,float min) {
		float count = 0;
		for (int i = 0; i < 1024; i++)
		{
			count = count + (p->value[i] - q->value[i])*(p->value[i] - q->value[i]);
			if (count > min)
				return -1;
		}
		return count;
	}
	
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
	static void writePointIndex(int p,std::fstream *file,int64_t numbyte) {
		int64_t a;
		file->seekp(numbyte);
		while (true) {
			file->read((char*)&a, sizeof(a));
			if (a < 4) {
				file->seekg(numbyte);
				a++;
				file->write((char*)&a, sizeof(a)); file->flush();
				numbyte = numbyte + 8 + 4*(a-1);
				file->seekg(numbyte);
				file->write((char*)&(p), sizeof(p)); file->flush();
				return;
			}
			else if (a == 4) {
				file->seekg(0,std::ios::end);
				int64_t loc = file->tellg();//下一个字块开头的位置
				file->seekg(numbyte); file->write((char*)&loc, sizeof(loc));
				file->seekg(0,std::ios::end);
				a = 1;file->write((char*)&a, sizeof(a)); file->flush();
				file->write((char*)&(p), sizeof(p)); file->flush();
				float b = 0;
				file->write((char*)&b, sizeof(b)*3); file->flush();
				return;
				
			}
			else {
				numbyte = a;
				file->seekp(numbyte);
			}
		}
	};
	

};
#pragma once
