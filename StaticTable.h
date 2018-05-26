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
	int_fast32_t num_bits_;
	template <typename V>
	void setup(V vals);

public:
	Table construct_table(LSHParameters& params);
};

Table StaticTable::construct_table(LSHParameters& params) {
	num_bits_ = hash_helpers::compute_number_of_hash_bits(params.dimension, params.last_cp_dimension, params.k);
	if (num_bits_ <= 32) {
		typedef uint32_t HashType;
		HashType tmp;
		setup(std::make_tuple(tmp));
	}
	else if (num_bits_ <= 64) {
		typedef uint64_t HashType;
		HashType tmp;
		setup(std::make_tuple(tmp));
	}
	else {
		std::cout <<
			"More than 64 hash bits are currently not "
			"supported." << std::endl;
	}
}

template <typename V>
void StaticTable::setup(V vals) {

}

#pragma once
