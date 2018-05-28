#include "Buckets.h"
#include "Math.h"
#include "hash_helpers.h"
#include "StaticTable.h"
#include <fstream>
#include <iostream>

using namespace std;

const string DATA_FILE_NAME = "d:/1/1/1.binary"; //���ݼ�
const string BUCKETS_FILES = "d:/1/buckets/"; //���Ͱ�ļ�
const string QUERY_FILE_NAME = "d:/1/1/2.binary"; //��ѯ��

int result[100];//�����������id��
const int LOG_DIM = 10;
const int NUM_HASH_TABLES = 50; //��ϣ�����
const int NUM_HASH_BITS = 18; //��ʼkֵ

//��ѯ
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
void processData() //�������ݼ�������,�����Ƿ��䵽ÿ��Ͱ��ȥ
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
//�������Ͱ�ļ�
void init()
{
	for (int n=1; n<=2048; n++)
	{
		string filename = BUCKETS_FILES + to_string(n) + ".binary";
		cout << filename << endl;//������ʾfilename������鿴���  
		ofstream examplefile(filename);//����һ�������������һ���ļ�  
	}
}
int main() {
	init();
	processData();
	return 0;
}