#include "Buckets.h"
#include "Math.h"
#include <fstream>
#include <iostream>
using namespace std;

const string DATA_FILE_NAME = ""; //���ݼ�
const string QUERY_FILE_NAME = ""; //��ѯ��

const int NUM_HASH_TABLES = 50; //��ϣ�����
const int NUM_HASH_BITS = 18; //��ʼkֵ

//����
bool read_point(ifstream *file, Point *p) 
{
	if (file->peek() == EOF)
		return false;
	float a;
	file->read((char*)&a, sizeof(a));
	p->id = (int)a;//��id
	for (int i = 0; i < 1024; i++) 
	{//������
		file->read((char*)&a, sizeof(a));
		p->value[i] = a;
	}
	return true;
}



void processData() //�������ݼ�������,�����Ƿ��䵽ÿ��Ͱ��ȥ
{
	ifstream file;
	file.open(DATA_FILE_NAME, ios::binary);

}

int main() {

}