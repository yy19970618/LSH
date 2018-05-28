#include "Math.h"
#include "hash_helpers.h"
#include <iostream>
#include <tuple>  
#include <stdlib.h>
<<<<<<< HEAD
#include "./ffht/fht_header_only.h"
=======
#include "../include/ffht/fht_header_only.h"
>>>>>>> temp

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
	static void random_rotate(float* vector, int log_n);

};

void StaticTable::random_rotate(float* vector, int log_n) {
	srand(SEED);
	//三次变换
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			if (rand() % 2 == 0)
				vector[j] *= -1;
		}
		fht_float(vector, log_n);
	}
}

#pragma once
