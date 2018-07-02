#include<iostream>
#include<ctime>
#include <fstream>
#include<string>
#include<math.h>
#include"Buckets.h"
#include<sstream>

using namespace std;
const int R = 10;
const int N = 1024;//维度
const int NUM = 6;
const string DATA_FILE_NAME = "d:/1/1/sui.binary"; //数据集
const string QUERY_FILE_NAME = "d:/1/1/2.binary"; //查询集
const string RESULT_FILE_NAME = "d:/1/1/result.csv"; //查询集
const string INDEX_FILE_NEME = "d:/1/1/stable.csv";
const int HASH_BUCKET_NUM = 1000000;
vector<int32_t> hashindex_stable[1000000];

int countHash(float *a, int *b, float *p)
{
	float count = 0;
	for (int i = 0; i < N; i++)
	{
		count = count + (*(a + i))*(*(p + i));
	}
	int temp = (int)(count) + *b;
	return temp%R;
}
void get_Hash_val(float *a, int *b)
{
	srand(time(NULL));
	for (int i=0; i < N; i++)
	{
		*(a + i) = (rand() % 100)*0.01;
	}
	*b = 0;//rand() % R;
}

void processData_stable()
{
	ifstream *file = new ifstream();
	//fstream ofile;
	file->open(DATA_FILE_NAME, ios::binary);
	ofstream ofile;
	ofile.open(INDEX_FILE_NEME);
	if (file->is_open() && ofile.is_open());
	else { cout << "data file out!"; return; }
	

	Point p;
	/*time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;
	int sec = ltm->tm_sec;*/
	float a[NUM][N]; int b[NUM];
	for (int i = 0; i < NUM; i++)
	{
		get_Hash_val(a[i], &b[i]);
	}
	while (true)
	{
		if (file->peek() == EOF)
		{
			file->close(); break;
		}
		Buckets::read_point(file, &p);//读点
		int indexid = 0;
		for (int i = 0; i < NUM; i++)
		{
			int temp=countHash(a[i], &b[i], p.value);
			indexid = indexid + temp*pow(10, i);
		}
		hashindex_stable[indexid].push_back(p.id);
		cout << p.id << endl;
		//if(p.id>6) return;
	}
	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < N; j++) {
			ofile << a[i][j] << ",";
		}
		ofile << b[i]<<endl;
	}
	int count = 0;
	for (int i = 0; i < HASH_BUCKET_NUM; i++)
	{
		if (hashindex_stable[i].size() == 0) count++;
		int j;
		for (j = 0; j < hashindex_stable[i].size(); j++)
		{
			//file.write((char*)&(hashindex[i][j]), sizeof(int32_t));
			ofile << hashindex_stable[i][j] << ',';
		}
		//int a = -1; file.write((char*)&a, sizeof(a));
		ofile << endl;
	}
	cout << "blank buckets num:" << count << endl;
	ofile.close();
	return;
}
void readIndex_stable()
{
	ifstream file;
	file.open(INDEX_FILE_NEME);
	string linestr; int index = 0;
	while (getline(file, linestr))
	{
		stringstream ss(linestr);
		string str;
		while (getline(ss, str, ','))
			hashindex_stable[index].push_back(stoi(str));
		index++;
	}
}


int main()
{
	processData_stable();
	return 0;
}