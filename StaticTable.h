#include "Math.h"
#include "hash_helpers.h"
#include <iostream>
#include <tuple>  
#include <stdlib.h>
#include "./ffht/fht_header_only.h"



#define SEED 4057218
#define DIMENSION 1024

struct LSHParameters {
	int_fast32_t dimension = 1024;
	//需配置k,l,last_cp_dimension
	int_fast32_t k = -1;
	int_fast32_t l = -1;
	int_fast32_t last_cp_dimension = -1;
	int_fast32_t num_rotations = 1; //密集数据
};


class StaticTable {

private:
	

public:
	static void random_rotate(float* vector, int log_n, int k,int d ,int *ret);

};

void StaticTable::random_rotate(float* p, int log_n,int k,int d,int *ret) {
	srand(SEED);
	//三次变换
	for (int j = 0; j < k; j++) {  //k个哈希函数
		float vector[1024];
		for (int i = 0; i < 1024; i++) {
			vector[i] = p[i];
		}
		for (int i = 0; i < 3; i++) { //三次变换
			for (int j = 0; j < DIMENSION; j++) {
				if (rand() % 2 == 0)
					vector[j] *= -1;
			}
			fht_float(vector, log_n);
		}
		ret[j] = hash_helpers::findMax(vector,d);  //映射到区域
	}
}

#pragma once
