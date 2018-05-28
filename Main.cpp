#include "Buckets.h"
#include "Math.h"
#include "hash_helpers.h"
#include "StaticTable.h"
#include <fstream>
#include <iostream>

using namespace std;

const string DATA_FILE_NAME = "d:/1/1/1.binary"; //数据集
const string BUCKETS_FILES = "d:/1/buckets/"; //存放桶文件
const string QUERY_FILE_NAME = "d:/1/1/2.binary"; //查询集

int result[100];//结果集，返回id集
const int LOG_DIM = 10;
const int NUM_HASH_TABLES = 50; //哈希表个数
const int NUM_HASH_BITS = 18; //初始k值

//查询
int queryData() 
{
	ifstream *file = new ifstream();
	file->open(QUERY_FILE_NAME, ios::binary);
	Point p;
	int i = 0;
	while (true)
	{
		if (file->peek() == EOF)
			return;
		Buckets::read_point(file, &p);
		float vector[1024];
		for (int i = 0; i < 1024; i++) {
			vector[i] = p.value[i];
		}
		StaticTable::random_rotate(vector, LOG_DIM);
		int bucket = hash_helpers::findMax(vector);
		ifstream bucketfile;
		string filename = "D:\\1\\buckets\\" + to_string(bucket) + ".binary";
		bucketfile.open(filename, ios::binary);
		Buckets probs;
		result[i]=probs.findMIn(&p, &bucketfile);
		i++;
	}
}
void processData() //处理数据集的向量,让它们分配到每个桶里去
{
	ifstream *file = new ifstream();
	file->open(DATA_FILE_NAME, ios::binary);
	Point p ;
	while (true)
	{
		if (file->peek() == EOF)
			return ;
		Buckets::read_point(file, &p);
		float vector[1024];
		for (int i = 0; i < 1024; i++) {
			vector[i] = p.value[i];
		}
		StaticTable::random_rotate(vector, LOG_DIM);
		int bucket = hash_helpers::findMax(vector);
		ofstream ofile;
		string filename = "D:\\1\\buckets\\" + to_string(bucket) + ".binary";
		ofile.open(filename, ios::binary);
		Buckets::writePoint(&p, &ofile);
	}

}
//建立输出桶文件
void init()
{
	for (int n=1; n<=2048; n++)
	{
		string filename = BUCKETS_FILES + to_string(n) + ".binary";
		cout << filename << endl;//用于显示filename，方便查看结果  
		ofstream examplefile(filename);//声明一个输出流，并打开一个文件  
	}
}
int main() {
	init();
	processData();
	return 0;
}