/**
*	Filename: SortTiming.cpp
*	List Container Sorting
*
*	After inserting random numbers into a list container, this program will calculate the time taken to sort
*	the container in ascending order using three sorting algorithms. These will include the Bubble and quick
*	sorting algorithms.
*/
#include <list>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <queue>
using namespace std::chrono;

class SortTimer
{
public:
	SortTimer(){}
	~SortTimer(){}

	/** 
	*	The print function prints the list of a list container. 
	*	Note: Not part of main program, used to check if list was/is sorted.
	*
	*	@param list<int> list which contains the list to be printed.
	*/
	void print(std::list<int> list)
	{
		std::list<int>::iterator i = list.begin();
		while (i != list.end())
		{
			std::cout << *i << std::endl;
			i++;
		}
	}
	/**
	*	The timer() function times the amount of time it takes to sort a list using the different types of sorting algorithms in SortTimer's child classes.
	*
	*	@param list<int> list which contains an empty list that is about to be filled up for timing purposes. The list is cleared after every run.
	*/
	void timer(std::list<int> list)
	{
		// Initialize random seed
		srand(time(NULL));
		double totalTime = 0;
		double min = 0;
		double max = 0;
		int step = 1000;
		int n = 0;
		int k = 20;

		// Obtain 20 loops so there will be 20 lines of print per function run.
		for (int i = 0; i < 20; i++)
		{
			totalTime = 0;
			min = 100;
			max = 0;
			n += step;

			// Repeat 50 times.
			for (int i = 0; i < 50; i++)
			{
				for (int i = 0; i < n; i++)
				{
					list.push_front(rand() % 100);
				}

				// Start time
				steady_clock::time_point t1 = steady_clock::now();
				sort(list.begin(), list.end());

				// End time
				steady_clock::time_point t2 = steady_clock::now();

				// Record time taken
				duration<double> timer = duration_cast<duration<double>>(t2 - t1);

				totalTime += timer.count();

				// Obtain minimum time taken to sort.
				if (timer.count() < min)
				{
					min = timer.count();
				}

				// Obtain maximum time taken to sort.
				if (timer.count() > max)
				{
					max = timer.count();
				}

				// Clear list after every sort.

				list.clear();
			}
			// Prints n, Average Time, Min, and then Max respectively.
			std::cout << n << "\t\t" << totalTime / 50 << "\t\t" << min << "\t\t" << max << std::endl;
		}
	}

	/** Place holder sort function **/
	virtual void sort(std::list<int>::iterator begin, std::list<int>::iterator end)
	{ /** filler **/ }
};

class BubbleSort : public SortTimer
{
public:
	BubbleSort(){}
	~BubbleSort(){}

	/**
	*	The sort() function within the BubbleSort class orders the integers in ascending order using the Bubble Sort algorithm.
	*
	*	@param list<int>::iterator begin points right before the value at the beginning of the list.
	*	@param list<int>::iterator end points right after the value at the end of the list.
	*/
	void sort(std::list<int>::iterator begin, std::list<int>::iterator end)
	{
		bool sorted = false;
		std::list<int>::iterator last = end;
		std::advance(last, -1);

		while (!sorted)
		{
			// Reset first and second iterators to starting positions.
			std::list<int>::iterator first = begin;
			std::list<int>::iterator second = begin;
			advance(second, 1);

			// Assumed sorted unless the first value is less than the second value.
			sorted = true;

			// Bubble Sort for loop which compares and swaps values as required.
			for (;first != last; second++)
			{
				if (*first > *second)
				{
					// Since if statement is engaged, the list is not sorted.
					sorted = false;

					std::swap(*first, *second);	
				}
			 first++;
			}
		}
		// Remove last value from being compared since Bubble Sort moves the largest value to the end.
		last--;
	}

};
class QuickSort : public SortTimer
{
public:
	QuickSort(){}
	~QuickSort(){}

	/**
	*	The sort() function within the QuickSort Class orders the list in ascending order using the Quick Sort algorithm.
	*
	*	@param list<int>::iterator begin points right before the value at the beginning of the list.
	*	@param list<int>::iterator end points right after the value at the end of the list.
	*/
	void sort(std::list<int>::iterator begin, std::list<int>::iterator end)
	{
		// If list/partion contains only 1 or is empty, stop function from recursion.
		if (std::distance(begin, end) <= 1)
			return;

		// Set pivot iterator at the beginning of the list.
		std::list<int>::iterator pivot = begin;
		int pivotVal = *pivot;

		// Create left and right iterators so begin and end iterators never get moved.
		std::list<int>::iterator left = begin;
		std::list<int>::iterator right = end;

		// Move right iterator back by one. There is no point for an iterator to point outside to the right of the list for Quick Sorting.
		right--;

		// Swap pivot value to the right for upcoming comparison.
		std::swap(*pivot, *right);

		// Quick Sort Comparison Loop: if left side is less than pivot value, swap.
		while (left != right)
		{
			if (*left <= pivotVal)
			{
				std::swap(*left, *pivot);
				pivot++;
			}
			left++;
		}

		std::swap(*pivot, *right);

		// Setting up for recursion calling.
		right = pivot;
		right++;
		sort(begin, pivot);
		sort(right, end);

	}
};

class RadixSort : public SortTimer
{
public:
	RadixSort(){}
	~RadixSort(){}

int main()
{
	std::list<int> list;
	
	SortTimer *timed[2] = { new BubbleSort, new QuickSort()};

	// Run timed test for Quick Sort.
	std::cout << "<-- BubbleSort -->" << std::endl;
	timed[0]->timer(list);

	// Run timed test for Quick Sort.
	std::cout << "<-- Quick Sort -->" << std::endl;
	timed[1]->timer(list);

	for (int i = 0; i < 2; i++)
		delete timed[i];
}
