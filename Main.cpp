#include "Buckets.h"
#include "Math.h"
#include <fstream>
#include <iostream>
using namespace std;

const string DATA_FILE_NAME = ""; //数据集
const string QUERY_FILE_NAME = ""; //查询集

const int NUM_HASH_TABLES = 50; //哈希表个数
const int NUM_HASH_BITS = 18; //初始k值

//读点
bool read_point(ifstream *file, Point *p) 
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
}



void processData() //处理数据集的向量,让它们分配到每个桶里去
{
	ifstream file;
	file.open(DATA_FILE_NAME, ios::binary);

}

int main() {

}