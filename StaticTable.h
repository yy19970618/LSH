#include "Math.h"
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

class StaticTable {

private:
	int_fast32_t num_bits_;
	template <typename V>
	void setup(V vals);

public:
	static inline int_fast32_t compute_number_of_hash_bits(int_fast32_t rotation_dim, int_fast32_t last_cp_dim, int_fast32_t k);
	Table construct_table(LSHParameters& params);
};

inline int_fast32_t StaticTable::compute_number_of_hash_bits(
	int_fast32_t rotation_dim, int_fast32_t last_cp_dim, int_fast32_t k) {
	int_fast32_t log_rotation_dim = Math::log2ceil(rotation_dim);
	int_fast32_t last_cp_log_dim = Math::log2ceil(last_cp_dim);
	return (k - 1) * (log_rotation_dim + 1) + last_cp_log_dim + 1;
}

Table StaticTable::construct_table(LSHParameters& params) {
	num_bits_ = compute_number_of_hash_bits(params.dimension, params.last_cp_dimension, params.k);
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
