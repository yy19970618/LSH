#include "Buckets.h"
#include "Math.h"
#include "hash_helpers.h"
#include "StaticTable.h"
#include <ctime>
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
void queryData() 
{
	ifstream *file = new ifstream();
	ifstream bucketfile;
	file->open(QUERY_FILE_NAME, ios::binary);
	Point p;
	int i = 0,bucket;
	Buckets querybucket[2048];
	float vector[1024];
	string filename;
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			bucketfile.close();
			return;
		}
		Buckets::read_point(file, &p);
		for (int i = 0; i < 1024; i++) {
			vector[i] = p.value[i];
		}
		StaticTable::random_rotate(vector, LOG_DIM);
		bucket = hash_helpers::findMax(vector);
		if (p.value[bucket] < 0)
			bucket = bucket + 1024;
		bucket++;
		filename = "D:\\1\\buckets\\" + to_string(bucket) + ".binary";
		bucketfile.open(filename, ios::binary);
		result[i]=querybucket[bucket].findMIn(&p, &bucketfile);
		cout << "查询第" << i << "个向量中";
		i++;

	}
}
void processData() //处理数据集的向量,让它们分配到每个桶里去
{
	ifstream *file = new ifstream();
	ofstream ofile;
	file->open(DATA_FILE_NAME, ios::binary);
	Point p ;
	string filename;
	int bucket,i=0;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	cout << "开始处理时间：" << ltm->tm_hour<<":" <<ltm->tm_min<<":"<< ltm->tm_sec << endl;
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			ofile.close();
			time_t now1 = time(0);
			tm *ltm1 = localtime(&now1);
			cout << "结束处理时间：" << ltm1->tm_hour << ":" << ltm1->tm_min << ":" << ltm1->tm_sec << endl;
			return;
		}
		Buckets::read_point(file, &p);
		float vector[1024];
		for (int i = 0; i < 1024; i++) {
			vector[i] = p.value[i];
		}
		StaticTable::random_rotate(vector, LOG_DIM);
		bucket = hash_helpers::findMax(vector);
		if (p.value[bucket] < 0)
			bucket = bucket + 1024;
		bucket++;
		filename = "D:\\1\\buckets\\" + to_string(bucket) + ".binary";
		ofile.open(filename, ios::binary);
		Buckets::writePoint(&p, &ofile);
		cout << "处理第" << i << "个向量中";
		i++;
	}

}
//建立输出桶文件
void init()
{
	for (int n=1; n<=2048; n++)
	{
		string filename = BUCKETS_FILES + to_string(n) + ".binary";
		cout << filename << endl;//用于显示filename，方便查看结果  
		ofstream file(filename);//声明一个输出流，并打开一个文件  
	}
	
}
int main() {
	init();
	processData();
	return 0;
}