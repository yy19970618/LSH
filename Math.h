#include <fstream>
class Math
{
public:
	inline static int_fast64_t find_next_power_of_two(int_fast64_t x);//求x%2
	inline static int_fast64_t log2ceil(int_fast64_t x); //求log(2,x)
private:
};
inline int_fast64_t Math::find_next_power_of_two(int_fast64_t x) //求x%2
{
	int_fast64_t res = 1;
	while (res < x) {
		res *= 2;
	}
	return res;
}
inline int_fast64_t Math::log2ceil(int_fast64_t x) //求log(2,x)
{
	int_fast64_t res = 0;
	int_fast64_t cur = 1;
	while (cur < x) {
		cur *= 2;
		res += 1;
	}
	return res;
}
#pragma once
