#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota

#define MAX_N 200000

long long pow_n_mod(long long base,
                    long long exponent,
                    const int& modulus)
{
	long long product = 1;

	while (exponent > 0)
	{
		if (exponent % 2 == 1)
		{
			product *= base;
			product %= modulus;
		}
		exponent >>= 1;

		// square the base
		base *= base;
		base %= modulus;
	}

	return product;
}

long long wrapped_mod(long long i, const long long& i_max)
{
	i %= i_max;
	return (i < 0) ? i+i_max : i;
}

struct queue_comparer
{
	int n;             // number of people
	int c, p;          // c:constant, p:modulus, p2:criterion
	long long e;       // e:exponent

	bool operator()(const int& i, const int& j)
	{
		// ab mod n = ((a mod n)(b mod n)) mod n;
		long long var = (wrapped_mod(c*(i-j), p) * pow_n_mod(i+j, e, p)) % p;
		// var > 2*p -> 2*var > p
		return 2 * var > p;
	}
};

int main(void)
{
	int cases;
	std::cin >> cases;

	// pre-allocate the maximum possible size of the queue.
	std::vector<int> queue;
	queue.reserve(MAX_N);

	// setup the comparer.
	queue_comparer comparer;

	while (cases-- > 0)
	{
		std::cerr << "cases " << (cases+1) << std::endl;

		// read the values and prep them.
		std::cin >> comparer.n >> comparer.c >> comparer.e >> comparer.p;

		// resize the queue and fill with numbers
		queue.resize(comparer.n);
		std::iota(std::begin(queue), std::end(queue), 1);

		std::sort(queue.begin(), queue.end(), comparer);

		// print out the result
		for (auto i = queue.begin(); i != queue.end(); ++i)
			std::cout << *i << ' ';

		// wipe out the pointer to holded elements,
		// but not the capacity.
		queue.clear();

		std::cerr << std::endl << std::endl;
	}

	return 0;
}
