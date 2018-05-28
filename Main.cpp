#include "Buckets.h"
#include "Math.h"
#include <fstream>
#include <iostream>

using namespace std;

const string DATA_FILE_NAME = ""; //���ݼ�
const string QUERY_FILE_NAME = ""; //��ѯ��

const int NUM_HASH_TABLES = 50; //��ϣ�����
const int NUM_HASH_BITS = 18; //��ʼkֵ
const ofstream files[2048]; //2048�������
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
void init()
{
	char filename[200];
	for (int n=1; n<=2048; n++)
	{     //sprintf�����½��ļ������ļ��ľ���·����һ��Ҫ��˫б��  
		sprintf(filename, "%s%d%s", "D:\\1\\buckets\\", n, ".txt");
		cout << filename << endl;//������ʾfilename������鿴��� 
		files[n].open(filename, ios::app);
		ofstream examplefile(filename);//����һ�������������һ���ļ�  

	}
}
int main() {
	


}