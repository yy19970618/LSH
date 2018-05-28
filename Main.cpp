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


void processData() //�������ݼ�������,�����Ƿ��䵽ÿ��Ͱ��ȥ
{
	ifstream *file;
	file->open(DATA_FILE_NAME, ios::binary);
	Point *p;
	while (true)
	{
		if (file->peek() == EOF)
			return ;
		Buckets::read_point(file, p);

		int bucket = hash_helpers::findMax(p->value);
		ofstream ofile;
		string filename = "D:\\1\\buckets\\" + to_string(bucket) + ".binary";
		ofile.open(filename, ios::binary);
	}

}

int main() {
	

}