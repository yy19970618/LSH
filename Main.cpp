#include "Buckets.h"
#include "Math.h"
#include "hash_helpers.h"
#include <fstream>
#include <iostream>

using namespace std;

const string DATA_FILE_NAME = ""; //���ݼ�
const string QUERY_FILE_NAME = ""; //��ѯ��

const int NUM_HASH_TABLES = 50; //��ϣ�����
const int NUM_HASH_BITS = 18; //��ʼkֵ
const ifstream files[2048]; //2048�������


void processData() //�������ݼ�������,�����Ƿ��䵽ÿ��Ͱ��ȥ
{
	ifstream *file;
	file->open(DATA_FILE_NAME, ios::binary);
	Point *p;
	Buckets::read_point(file, p);
	int bucket = hash_helpers::findMax(p->value);

}
void init()
{
	string filename;
	for (int i = 1; i <= 2048; i++)
	{
		filename = "D:\\vs2012\\projects\\file\\file\\wdata\\" + std::to_string(i) + ".binary";
		//files[i].open(filename, ios::binary);
	}
}
int main() {
	

}