#include "Buckets.h"
#include "Math.h"
#include "hash_helpers.h"
#include "StaticTable.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

const string DATA_FILE_NAME = "/media/sunny/source/1/1/1.binary"; //数据集
const string BUCKETS_FILES = "/media/sunny/source/1/buckets/"; //存放桶文件
const string QUERY_FILE_NAME = "/media/sunny/source/1/1/2.binary"; //查询集
//g++ -I ~/home/LSH/include -std=c++11 Main.cpp -g -o main
const string CENTER_FILE_NAME = "/media/sunny/source/1/1/center.binary";//中心化数据集

int result[100];//结果集，返回id集
const int LOG_DIM = 10;
const int NUM_HASH_TABLES = 50; //哈希表个数
const int NUM_HASH_BITS = 18; //初始k值
const int k = 2;  //哈希函数个数
const int d = 1024;  //一个哈希函数区域
float center[1024];

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
		//StaticTable::random_rotate(vector, LOG_DIM);
		bucket = hash_helpers::findMax(vector,1024);
		if (p.value[bucket] < 0)
			bucket = bucket + 1024;
		bucket++;
		filename = BUCKETS_FILES + to_string(bucket) + ".binary";
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
	if (file->is_open() == false) {
		cout << "dataset out!"; return;
	}
	ifstream cenfile;
	cenfile.open(CENTER_FILE_NAME, ios::binary);
	for(int i=0;i<1024;i++)
		cenfile.read((char*)&(center[i]), sizeof(center[i]));
	/*ofstream ofile[2048];
	for (int i = 1; i <= 2048; i++) {
		string temp = BUCKETS_FILES + to_string(i) + ".binary";
		cout << i << endl;
		ofile[i-1].open(temp, ios::binary | ios::app);
		if (ofile[i - 1].is_open() == false) {
			cout << "file out!"; return;
		}
	}*/
	
	Point p ;
	int bucket;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;
	int sec = ltm->tm_sec;
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			time_t now1 = time(0);
			tm *ltm1 = localtime(&now1);
			cout << "start time:" << ":" << hour << ":" << min << ":" << sec<<endl;
			cout << "end time:" << ltm1->tm_hour << ":" << ltm1->tm_min << ":" << ltm1->tm_sec << endl;
			return;
		}
		Buckets::read_point(file, &p);
		float vector[1024];
		for (int i = 0; i < 1024; i++) {
			vector[i] = p.value[i];
		}
		
		/*cout<<"a";
		for(int i=0;i<1024;i++)
			cout<<vector[i]<<" ";
		cout<<endl;*/

		hash_helpers::pointUnit(vector);

		/*cout<<"b";
		for(int i=0;i<1024;i++)
			cout<<vector[i]<<" ";
		cout<<endl;*/

		for(int i=0;i<1024;i++)
			vector[i]=vector[i]-center[i];

		/*cout<<"c";
		for(int i=0;i<1024;i++)
			cout<<vector[i]<<" ";
		cout<<endl;*/

		int bucket[k];
		StaticTable::random_rotate(vector, LOG_DIM,k,d,bucket);

		string filename = BUCKETS_FILES;
		char buffer[20];
		for (int i = 0; i < k; i++)
		{
			sprintf(buffer, "%04d", bucket[i]);
			filename = filename + buffer;
		}
		filename = filename + ".binary";
		ofile.open(filename, ios::binary | ios::app);
		Buckets::writePoint(&p, &ofile);
		ofile.close();
		cout << p.id << endl;
	}
}
void countCenter() {
	ifstream *file = new ifstream();
	file->open(DATA_FILE_NAME, ios::binary);
	if (file->is_open() == false) {
		cout << "dataset out!"; return;
	}
	Point p;
	double count[1024];
	for (int i = 0; i < 1024; i++)//初始化中心点
		count[i] = 0;
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			break;
		}
		Buckets::read_point(file, &p);
		hash_helpers::pointUnit(p.value);
		for (int i = 0; i < 1024; i++) {
			count[i] = count[i] + p.value[i];
		}
		cout << p.id << endl;
	}
	double num = 10000000;
	for (int i = 0; i < 1024; i++) {
		center[i] = count[i] / num;
	}
	ofstream cenfile;
	cenfile.open(CENTER_FILE_NAME, ios::binary | ios::app);
	for(int i=0;i<1024;i++)
		cenfile.write((char*)&(center[i]), sizeof(center[i]));
	cenfile.close();
}
int main() {
	//countCenter();
	//processData();

	return 0;
}
