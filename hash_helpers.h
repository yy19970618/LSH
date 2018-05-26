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


		// Helper class that contains the actual per-query state of an LSH function
		// object (the transformed input point, the temporary datat of the
		// transformation, and the multiprobe object).
		// The helper class also has functions for retrieving the probing sequence,
		// either in a "lazy" probe-by-probe way or with a "batch" method for a fixed
		// number of probes.
		template <typename HashFunction>
		class HashObjectQuery {
		private:
			typedef typename HashFunction::MultiProbeLookup MultiProbeLookup;
			typedef typename HashFunction::TransformedVectorType TransformedVectorType;
			typedef typename HashFunction::HashTransformation HashTransformation;

		public:
			typedef typename HashFunction::HashType HashType;
			typedef typename HashFunction::VectorType VectorType;

			class ProbingSequenceIterator
				: public std::iterator<std::forward_iterator_tag,
				std::pair<HashType, int_fast32_t>> {
			public:
				ProbingSequenceIterator(HashObjectQuery* parent = nullptr)
					: parent_(parent) {
					if (parent_ != nullptr) {
						if (!parent_->multiprobe_.get_next_probe(&cur_val_.first,
							&cur_val_.second)) {
							parent_ = nullptr;
						}
					}
				}

				// TODO: should also check cur_val for general use?
				bool operator==(const ProbingSequenceIterator& rhs) const {
					return parent_ == rhs.parent_;
				}

				// TODO: should also check cur_val for general use?
				bool operator!=(const ProbingSequenceIterator& rhs) const {
					return parent_ != rhs.parent_;
				}

				typename std::iterator<std::forward_iterator_tag,
					std::pair<HashType, int_fast32_t>>::reference
					operator*() const {
					return cur_val_;
				}

				typename std::iterator<std::forward_iterator_tag,
					std::pair<HashType, int_fast32_t>>::pointer
					operator->() {
					return &cur_val_;
				}

				ProbingSequenceIterator& operator++() {
					if (!parent_->multiprobe_.get_next_probe(&cur_val_.first,
						&cur_val_.second)) {
						parent_ = nullptr;
					}
					return *this;
				}

			private:
				HashObjectQuery* parent_;
				std::pair<HashType, int_fast32_t> cur_val_;
			};

			HashObjectQuery(const HashFunction& parent)
				: parent_(parent), multiprobe_(parent), hash_transformation_(parent) {
				parent_.reserve_transformed_vector_memory(&transformed_vector_);
			}

			std::pair<ProbingSequenceIterator, ProbingSequenceIterator>
				get_probing_sequence(const VectorType& point) {
				hash_transformation_.apply(point, &transformed_vector_);
				multiprobe_.setup_probing(transformed_vector_, -1);
				return std::make_pair(ProbingSequenceIterator(this),
					ProbingSequenceIterator(nullptr));
			}

			void get_probes_by_table(const VectorType& point,
				std::vector<std::vector<HashType>>* probes,
				int_fast64_t num_probes) {
				if (num_probes < parent_.l_) {
					throw LSHFunctionError(
						"Number of probes must be at least "
						"the number of tables.");
				}
				if (static_cast<int_fast64_t>(probes->size()) != parent_.l_) {
					probes->resize(parent_.l_);
				}
				for (size_t ii = 0; ii < probes->size(); ++ii) {
					(*probes)[ii].clear();
				}

				hash_transformation_.apply(point, &transformed_vector_);
				multiprobe_.setup_probing(transformed_vector_, num_probes);

				int_fast32_t cur_table;
				HashType cur_probe;

				for (int_fast64_t ii = 0; ii < num_probes; ++ii) {
					if (!multiprobe_.get_next_probe(&cur_probe, &cur_table)) {
						break;
					}
					// printf("%u %d\n", cur_probe, cur_table);
					(*probes)[cur_table].push_back(cur_probe);
				}
			}

		private:
			const HashFunction& parent_;
			MultiProbeLookup multiprobe_;
			HashTransformation hash_transformation_;
			TransformedVectorType transformed_vector_;
		};

#pragma once
