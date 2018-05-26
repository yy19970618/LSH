#include "Math.h"
///
/// Data structure for point query statistics
///
struct QueryStatistics {
	///
	/// Average total query time
	///
	double average_total_query_time = 0.0;
	///
	/// Average hashing time
	///
	double average_lsh_time = 0.0;
	///
	/// Average hash table retrieval time
	///
	double average_hash_table_time = 0.0;

	double average_sketches_time = 0.0;
	///
	/// Average time for computing distances
	///
	double average_distance_time = 0.0;
	///
	/// Average number of candidates
	///
	double average_num_candidates = 0;
	///
	/// Average number of *unique* candidates
	///
	double average_num_unique_candidates = 0;

	double average_num_filtered_candidates = 0;
	///
	/// Number of queries the statistics were computed over
	///
	int_fast64_t num_queries = 0;

	// TODO: move these to internal helper functions?
	void convert_to_totals() {
		average_total_query_time *= num_queries;
		average_lsh_time *= num_queries;
		average_hash_table_time *= num_queries;
		average_sketches_time *= num_queries;
		average_distance_time *= num_queries;
		average_num_candidates *= num_queries;
		average_num_unique_candidates *= num_queries;
		average_num_filtered_candidates *= num_queries;
	}

	void compute_averages() {
		if (num_queries > 0) {
			average_total_query_time /= num_queries;
			average_lsh_time /= num_queries;
			average_hash_table_time /= num_queries;
			average_sketches_time /= num_queries;
			average_distance_time /= num_queries;
			average_num_candidates /= num_queries;
			average_num_unique_candidates /= num_queries;
			average_num_filtered_candidates /= num_queries;
		}
	}

	void add_totals(const QueryStatistics& other) {
		average_total_query_time += other.average_total_query_time;
		average_lsh_time += other.average_lsh_time;
		average_hash_table_time += other.average_hash_table_time;
		average_sketches_time += other.average_sketches_time;
		average_distance_time += other.average_distance_time;
		average_num_candidates += other.average_num_candidates;
		average_num_unique_candidates += other.average_num_unique_candidates;
		average_num_filtered_candidates += other.average_num_filtered_candidates;
		num_queries += other.num_queries;
	}

	void reset() {
		average_total_query_time = 0.0;
		average_lsh_time = 0.0;
		average_hash_table_time = 0.0;
		average_sketches_time = 0.0;
		average_distance_time = 0.0;
		average_num_candidates = 0.0;
		average_num_unique_candidates = 0.0;
		average_num_filtered_candidates = 0.0;
		num_queries = 0;
	}
};


#pragma once
