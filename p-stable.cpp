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

void queryData_stable()
{
	ifstream *file = new ifstream();
	file->open(QUERY_FILE_NAME, ios::binary);
	if (file->is_open() == false)
	{
		cout << "querydata file fail!" << endl; return;
	}
	
	ifstream data_file;
	data_file.open(DATA_FILE_NAME, ios::binary);
	if (data_file.is_open() == false)
	{
		cout << "dataset file fail!" << endl; return;
	}
	ifstream bucket_file;
	bucket_file.open(INDEX_FILE_NEME);
	if (bucket_file.is_open() == false)
	{
		cout << "bucket file fail!" << endl; return;
	}
	string linestr;

	ofstream result;
	result.open(RESULT_FILE_NAME);
	if (result.is_open() == false)
	{
		cout << "bucket file fail!" << endl; return;
	}
	//加载桶和参数a,b
	float a[NUM][N]; int b[NUM];
	string linestr; int index = 0;
	for (int i = 0; i < NUM; i++)
	{
		getline(bucket_file, linestr);
		stringstream ss(linestr);
		string str;
		for (int j = 0; j < N; j++) {
			getline(ss, str, ',');
			a[i][j] = stoi(str);
		}
		b[i] = stoi(str);
	}
	while (getline(bucket_file, linestr))
	{
		stringstream ss(linestr);
		string str;
		while (getline(ss, str, ','))
			hashindex_stable[index].push_back(stoi(str));
		index++;
	}
	Point p;
	int num = 0;
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
			cout << "total num:" << num << endl;
			return;
		}
		
		Buckets::read_point(file, &p);
		vector<int> queryarray;
		int indexid = 0;
		for (int i = 0; i < NUM; i++)
		{
			int temp = countHash(a[i], &b[i], p.value);
			indexid = indexid + temp*pow(10, i);
		}
		cout << p.id << endl;
		
			//cout << bucket[i] << " ";
			for (int j = 0; j < hashindex_stable[indexid].size(); j++)
			{
				//cout << hashindex[cnt][numByte[i]][j] << " ";
				queryarray.push_back(hashindex_stable[indexid][j]);
			}
	
		int ret = Buckets::findMIn(&p, &ofile, queryarray);
		result << ret << endl;
		float tmp = Buckets::distance(&ofile, ret, p);
		cout << "find id:" << ret << " distance:" << tmp << endl;
		for (int i = 0; i<queryarray.size(); i++)
		{
			if (queryarray[i] == p.id)
			{
				num++; break;
			}

		}
		tmp = Buckets::distance(&ofile, p.id, p);
		cout << "actual id:" << p.id << " distance:" << tmp << endl;
		//return;

	}

}

int main()
{
	processData_stable();
	return 0;
}