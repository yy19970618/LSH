#include "Buckets.h"
#include "hash_helpers.h"
#include "StaticTable.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

/*const string DATA_FILE_NAME = "//mnt/hgfs/I/1/1.binary"; //数据集
const string BUCKETS_FILES = "/home/summar/buckets.binary"; //存放桶文件
const string QUERY_FILE_NAME = "/mnt/hgfs/I/1/2.binary"; //查询集
//g++ -I ~/LSH/include -std=c++11 Main.cpp -g -o main
const string CENTER_FILE_NAME = "/mnt/hgfs/I/1/center.binary";//中心化数据集*/

const string DATA_FILE_NAME = "d:/1/1/sui.binary"; //数据集
const string BUCKETS_FILES = "d:/1/1/3.csv"; //存放桶文件
const string LI = "/media/sunny/source/1/1/3.csv"; //存放桶文件
const string my = "d:/1/1/4.csv"; //存放桶文件
const string QUERY_FILE_NAME = "d:/1/1/2.binary"; //查询集
const string RESULT_FILE_NAME = "d:/1/1/result.csv"; //查询集
//g++ -I ~/home/LSH/include -std=c++11 Main.cpp -g -o main
const string CENTER_FILE_NAME = "d:/1/1/center.binary";//中心化数据集

int result[100];//结果集，返回id集
const int LOG_DIM = 10;
const int NUM_HASH_TABLES = 50; //哈希表个数
const int NUM_HASH_BITS = 18; //初始k值
const int k = 2;  //哈希函数个数
const int d = 512;  //一个哈希函数区域
float center[1024];
vector<int32_t> hashindex[1048576];
//查询
void readIndex()
{
	ifstream file;
	file.open(BUCKETS_FILES);
	string linestr; int index = 0;
	while (getline(file, linestr))
	{
		stringstream ss(linestr);
		string str;
		while (getline(ss, str, ','))
			hashindex[index].push_back(stoi(str));
		index++;
	}
		
}
void queryData() 
{
	ifstream *file = new ifstream();
	file->open(QUERY_FILE_NAME, ios::binary);
	if (file->is_open() == false)
	{
		cout << "querydata file fail!" << endl; return;
	}
	ifstream cenfile;//读中心点
	cenfile.open(CENTER_FILE_NAME, ios::binary);
	for (int i = 0; i<1024; i++)
		cenfile.read((char*)&(center[i]), sizeof(center[i]));
	if (cenfile.is_open() == false)
	{
		cout << "center file fail!" << endl; return;
	}
	ifstream ofile;
	ofile.open(DATA_FILE_NAME, ios::binary);
	if (ofile.is_open() == false)
	{
		cout << "dataset file fail!" << endl; return;
	}
	ifstream myfile;
	myfile.open(my);
	string linestr;

	ofstream result;
	result.open(RESULT_FILE_NAME);
	readIndex();
	Point p;
	int num=0;
	/*time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;
	int sec = ltm->tm_sec;*/
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			/*time_t now1 = time(0);
			tm *ltm1 = localtime(&now1);
			cout << "start time:" << ":" << hour << ":" << min << ":" << sec << endl;
			cout << "end time:" << ltm1->tm_hour << ":" << ltm1->tm_min << ":" << ltm1->tm_sec << endl;*/
			cout<<"total num:"<<num<<endl;
			return;
		}
		int bucket[4];
		float tempvector[1024];
		int64_t numByte[4];
		vector<int32_t> queryarray;
		Buckets::read_point(file, &p);

		/*for (int i = 0; i < 1024; i++) {
			tempvector[i] = p.value[i];
		}

		hash_helpers::pointUnit(tempvector);

		for (int i = 0; i<1024; i++)
			tempvector[i] = tempvector[i] - center[i];

		StaticTable::random_rotate_query(tempvector, LOG_DIM, k, d, bucket);
				
		quer<<bucket[0]<<','<<bucket[1]<<','<<bucket[2]<<','<<bucket[3]<<endl;*/

		getline(myfile, linestr);
		stringstream ss(linestr);
		string str;
		for (int i = 0; i < 4; i++)
		{
			getline(ss, str, ',');
			bucket[i]=stoi(str)+1;
		}
		numByte[0] = (bucket[0] - 1) * 1024 + (bucket[2] - 1);
		numByte[1] = (bucket[0] - 1) * 1024 + (bucket[3] - 1);
		numByte[2] = (bucket[1] - 1) * 1024 + (bucket[2] - 1);
		numByte[3] = (bucket[1] - 1) * 1024 + (bucket[3] - 1);
		
		for (int i = 0; i < 4; i++)
		{
			cout << bucket[i] << " ";
			for (int j = 0; j < hashindex[numByte[i]].size(); j++)
			{
				cout<<hashindex[numByte[i]][j]<<" ";
				queryarray.push_back(hashindex[numByte[i]][j]);
			}
			cout<<endl;
		}
		result << Buckets::findMIn(&p, &ofile, queryarray) << endl;
		for(int i=0;i<queryarray.size();i++)
		{
			if(queryarray[i]==p.id)
				{num++;break;}
				
		}
		cout << p.id << endl;
		//return;
	}
}
void coutIndex() {
	ofstream file;
	file.open(LI);
	int count=0;
	for (int i = 0; i < 1048576; i++)
	{
		if(hashindex[i].size()==0) count++;
		int j ;
		for ( j = 0; j < hashindex[i].size(); j++)
		{
			//file.write((char*)&(hashindex[i][j]), sizeof(int32_t));
			file<<hashindex[i][j]<<',';
		}
		//int a = -1; file.write((char*)&a, sizeof(a));
		file<<endl;
	}
	cout<<"blank buckets num:"<<count<<endl;
}
void processData() //处理数据集的向量,让它们分配到每个桶里去
{
	ifstream *file = new ifstream();
	//fstream ofile;
	file->open(DATA_FILE_NAME, ios::binary);
	if (file->is_open() == false) {
		cout << "dataset out!"; return;
	}
	/*ofile.open(BUCKETS_FILES);
	if (ofile.is_open() == false) {
		cout << "bucketsfile out!"; return;
	}*/
	ifstream cenfile;//读中心点
	cenfile.open(CENTER_FILE_NAME, ios::binary);
	for(int i=0;i<1024;i++)
		cenfile.read((char*)&(center[i]), sizeof(center[i]));
	
	Point p ;
	/*time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;
	int sec = ltm->tm_sec;*/
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			//ofile.close();
			/*time_t now1 = time(0);
			tm *ltm1 = localtime(&now1);
			cout << "start time:" << ":" << hour << ":" << min << ":" << sec<<endl;
			cout << "end time:" << ltm1->tm_hour << ":" << ltm1->tm_min << ":" << ltm1->tm_sec << endl;*/
			coutIndex();
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
		
		//int64_t numByte = (bucket[0] - 1) * 1024 * (4 * 4 + 8) + (bucket[1]-1) * (4 * 4 + 8);
		//bucket[0] = 1; bucket[1] = 2;
		int64_t numByte = (bucket[0] - 1) * 1024  + (bucket[1] - 1) ;
		cout<<numByte<< " ";
		//numByte=numByte/1024;
		hashindex[numByte].push_back(p.id);
		//Buckets::writePointIndex(p.id, &ofile,numByte);
		cout << p.id << endl;
		//if(p.id>6) return;
	}
}

void initBucketFile() {
	ofstream ofile;
	ofile.open(BUCKETS_FILES, ios::binary);
	if (ofile.is_open() == false)
		return;

	for (int i = 0; i < 1024; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			int64_t temp;// = i * 1024 * (4 * 4 + 8) + j*(4 * 4 + 8);
			temp = 0;
			ofile.write((char*)&(temp), 3*sizeof(temp));
		}
	}
	
	ofile.close();
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
	double num = p.id+1;
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

	/*fstream file;
	file.open("d:/1/1/buckets.binary");
	file.seekg(16);
	int64_t a;
	file.read((char*)&a, sizeof(a));
	a++;
	file.seekg(4116);
	cout << file.tellg();
	file.write((char*)&a, sizeof(a));
	cout << file.tellg();*/
	//initBucketFile();
	//initBucketFile();
	//countCenter();
	//coutIndex();
	//processData();
	/*vector<float> www;
	fstream file;
	file.open("D:/1/1/3.binary");
	if (file.is_open()) {
		while (true) {
			if (file.peek() == EOF) break;
			float b;
			file.read((char*)&b, sizeof(b));
			www.push_back(b);
		}
	}*/
	queryData() ;
	//readIndex();
	return 0;

}
