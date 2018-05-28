#include "Buckets.h"
#include "Math.h"
#include "hash_helpers.h"
#include "StaticTable.h"
#include <ctime>
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
		cout << "��ѯ��" << i << "��������";
		i++;

	}
}
void processData() //�������ݼ�������,�����Ƿ��䵽ÿ��Ͱ��ȥ
{
	ifstream *file = new ifstream();
	ofstream ofile;
	file->open(DATA_FILE_NAME, ios::binary);
	Point p ;
	string filename;
	int bucket,i=0;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	cout << "��ʼ����ʱ�䣺" << ltm->tm_hour<<":" <<ltm->tm_min<<":"<< ltm->tm_sec << endl;
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close();
			ofile.close();
			time_t now1 = time(0);
			tm *ltm1 = localtime(&now1);
			cout << "��������ʱ�䣺" << ltm1->tm_hour << ":" << ltm1->tm_min << ":" << ltm1->tm_sec << endl;
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
		cout << "�����" << i << "��������";
		i++;
	}

}
//�������Ͱ�ļ�
void init()
{
	for (int n=1; n<=2048; n++)
	{
		string filename = BUCKETS_FILES + to_string(n) + ".binary";
		cout << filename << endl;//������ʾfilename������鿴���  
		ofstream file(filename);//����һ�������������һ���ļ�  
	}
	
}
int main() {
	init();
	processData();
	return 0;
}