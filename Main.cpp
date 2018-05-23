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

//����k��last_cp_dim
void compute_number_of_hash_functions(int_fast32_t *last_cp_dim, int_fast32_t *k)
{
	int_fast32_t rotation_dim = Math::find_next_power_of_two(1024);
	int_fast32_t bits_per_cp = Math::log2ceil(rotation_dim) + 1;
	*k = NUM_HASH_BITS / bits_per_cp;
	if (*k * bits_per_cp < NUM_HASH_BITS) {
		int_fast32_t remaining_bits = NUM_HASH_BITS - *k * bits_per_cp;
		*k += 1;
		*last_cp_dim = 1 << (remaining_bits - 1);
	}
	else {
		*last_cp_dim = rotation_dim;
	}
}


void rocessData() //�������ݼ�������,�����Ƿ��䵽ÿ��Ͱ��ȥ
{
	ifstream file;
	file.open(DATA_FILE_NAME, ios::binary);

}

int main() {

}