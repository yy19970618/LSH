#include "Math.h"
#include "hash_helpers.h"
#include <iostream>
#include <tuple>  

struct LSHParameters {
	int_fast32_t dimension = 1024;
	//需配置k,l,last_cp_dimension
	int_fast32_t k = -1;
	int_fast32_t l = -1;
	int_fast32_t last_cp_dimension = -1;
	int_fast32_t num_rotations = 1; //密集数据
};
struct Table {

};

class StaticTable {

private:
	

public:

};



#pragma once
