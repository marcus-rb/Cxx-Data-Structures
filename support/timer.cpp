#include <chrono>
#include <iostream>

class timer {
public:
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<double> duration;

	#pragma warning(suppress: 26495)
	timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << "Time: " << duration.count() * 1000 << "ms" << std::endl;
	}
};