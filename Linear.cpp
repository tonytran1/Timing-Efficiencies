/**
*	Filename: Linear.cpp
*	In Class Exercise - Linear: Time Taken
*	
*	This program tests the time taken to randomize a number and insert the number into a forward_list.
*	The program will simulate a O(n) operation that will calclate the average time taken for each O(n) loop.
*	The value of n will be incremented by a step value each time an average is to be calculated.
*
*/
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <forward_list>
using namespace std::chrono;

int main()
{
	double totalTime = 0;

	// Repeats: change to 10 or 100
	int numberOfRepeats = 100;

	// n
	int numberOfTimes = 0;

	// Step value to be incremented
	int step = 10000;
	std::forward_list<int> list;

	// Outter loop, increment step 20 times
	for (int i = 0; i < 20; i++)
	{
		// Add step to n
		numberOfTimes += step;

		// Reset total time
		totalTime = 0;

		for (int i = 0; i < numberOfRepeats; i++)
		{
			// Start time
			steady_clock::time_point t1 = steady_clock::now();

			//Loop n times
			for (int i = 0; i < numberOfTimes; i++)
			{
				list.push_front(rand() % 100);
			}list.clear();

			// End time
			steady_clock::time_point t2 = steady_clock::now();

			// Record time taken
			duration<double> timer = duration_cast<duration<double>>(t2 - t1);

			// Add recorded time to total time
			totalTime += timer.count();
		}
		// Output n and average time
		std::cout << numberOfTimes << "\t" << totalTime / numberOfRepeats << std::endl;
	}
}
