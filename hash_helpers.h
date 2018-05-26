#include"Math.h"
#include "./ffht/fht_header_only.h"
#include<ostream>

struct FHTFunction {
	static void apply(float* data, int_fast32_t dim) {
		int_fast32_t log_dim = 0;
		while (((int_fast32_t)1 << log_dim) < dim) {
			++log_dim;
		}
		if (fht_float(data, log_dim) != 0) {
			std::cout<<"fht_float returned nonzero value.";
		}
	}
};
class FHTHelper {
public:
	FHTHelper(int_fast32_t dim) : dim_(dim) {}

	int_fast32_t get_dim() { return dim_; }

	void apply(float* data) { FHTFunction::apply(data, dim_); }

private:
	int_fast64_t dim_;
};



class hash_helpers{
public:

	//¼ÆËãkºÍlast_cp_dim
	static void compute_number_of_hash_functions(int_fast32_t NUM_HASH_BITS,int_fast32_t *last_cp_dim, int_fast32_t *k)
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
	};
	static inline int_fast32_t compute_number_of_hash_bits(
		int_fast32_t rotation_dim, int_fast32_t last_cp_dim, int_fast32_t k) {
		int_fast32_t log_rotation_dim = Math::log2ceil(rotation_dim);
		int_fast32_t last_cp_log_dim = Math::log2ceil(last_cp_dim);
		return (k - 1) * (log_rotation_dim + 1) + last_cp_log_dim + 1;
	};

};

#pragma once
