#include "Buckets.h"
#include "Math.h"
#include <fstream>
#include <iostream>

using namespace std;

const string DATA_FILE_NAME = ""; //数据集
const string QUERY_FILE_NAME = ""; //查询集

const int LOG_DIM = 10;
const int NUM_HASH_TABLES = 50; //哈希表个数
const int NUM_HASH_BITS = 18; //初始k值
const ifstream files[2048]; //2048个输出流


void processData() //处理数据集的向量,让它们分配到每个桶里去
{
	ifstream *file;
	file->open(DATA_FILE_NAME, ios::binary);
	Point *p;
	Buckets::read_point(file, p);

}
void init()
{
	string filename;
	for (int i = 1; i <= 2048; i++)
	{
		filename = "D:\\vs2012\\projects\\file\\file\\wdata\\" + std::to_string(i) + ".binary";
		//files[i].open(filename, ios::binary);
	}
}
int main() {
	float test[1024];
	for(int i=0;i<1024;i++)
		test[i]=1.0*i;
	StaticTable::random_rotate(test, LOG_DIM);
	cout << test[0] <<endl; 
	cout << test[1] <<endl; 
	cout << test[2] <<endl;
	cout << test[3] <<endl;

}