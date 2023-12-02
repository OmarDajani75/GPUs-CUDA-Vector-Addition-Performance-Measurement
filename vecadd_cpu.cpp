#include <iostream>
#include <math.h>

// function to add the elements of two arrays
void add(int n, float *x, float *y)
{
	for (int i = 0; i < n; i++)
		y[i] = x[i] + y[i];
}

int main(void)
{
	int N = 1 << 26; // 1M elements

	float *x = new float[N];
	float *y = new float[N];

	// initialize x and y arrays on the host
	for (int i = 0; i < N; i++)
	{
		x[i] = 1.0f;
		y[i] = 2.0f;
	}

	// insert start timer code here
	auto start = std::chrono::high_resolution_clock::now();
	// call the method to do the work
	// Run kernel on 1M elements on the CPU
	add(N, x, y);
	// insert end timer code here, and print out the elapsed time for this prob>
	auto end = std::chrono::high_resolution_clock::now();

	double duration = std::chrono::duration<double>(end - start).count();

	// Check for errors (all values should be 3.0f)
	float maxError = 0.0f;
	for (int i = 0; i < N; i++)
		maxError = fmax(maxError, fabs(y[i] - 3.0f));
	std::cout << "Max error: " << maxError << std::endl;

	// Free memory
	delete[] x;
	delete[] y;

	return 0;
}