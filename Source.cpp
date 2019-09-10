/*
Jeffrey Stoddard
CECS 328
Lab 6
*/

#include <iostream>
#include <chrono>
#include <algorithm>
#include <chrono>

int *arr;
long int size = 0; //n
int k = 0;

//Initializes array with size from user input
void InitArray()
{
	std::cout << "Please enter a positive integer for the array size: ";
	std::cin >> size;
	arr = new int[size];
}

//Prints array
void printArray(int arr[])
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i << "[" << arr[i] << "] ";
	}
	std::cout << std::endl;
}

//generates -5000 through 5000 in arr
void populateArray()
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 20000 - 10000;
	}
}

//Swap utility function for integers
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//Basic selection sort algorithm
void selectionSort(int input[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int min = input[i];
		int index = i; //initialize index to first unsorted element
		for (int j = i; j < size; j++)
		{
			min = (input[j] < min) ? input[j] : min; //set min
			(input[j] == min) ? index = j : index = index; //if a min was found, set the index, else index is the same
		}
		swap(input[index], input[i]);
	}
}

//Max heapifies a node
void max_heapify(int input[], int index, int size)
{
	int &parent = input[index];

	int leftIndex = 2 * index + 1;
	int rightIndex = 2 * index + 2;

	if (rightIndex < size && leftIndex < size) //swap with max condition
	{
		if (input[leftIndex] > input[rightIndex]) //max child is left
		{
			if (parent < input[leftIndex]) //check if parent is less than max
			{
				swap(parent, input[leftIndex]);
				max_heapify(input, leftIndex, size);
			}
		}
		else //max child is right
		{
			if (parent < input[rightIndex]) //check if parent is less than max
			{
				swap(parent, input[rightIndex]);
				max_heapify(input, rightIndex, size);
			}
		}

	}
	else if (leftIndex < size && input[leftIndex] > parent) //swap with child condition
	{
		swap(parent, input[leftIndex]);
		max_heapify(input, leftIndex, size);
	}
	else //no children
	{
		return;
	}
}

//Builds a max heap from an input array
int* build_MaxHeap(int input[], int size)
{
	int* new_a = input; //reference array

	//max heapify new array
	//starts from last leaf and finishes at root
	for (int i = size/2 - 1; i >= 0; i--) 
	{
		max_heapify(input, i, size);
	}
	return new_a;
}

//Generates a sorted array from unsorted array
void heap_sort(int input[], int size)
{
	build_MaxHeap(input, size);
	for (int i = 0; i < size; i++)
	{
		swap(input[size - 1 - i], input[0]); //swap first and last element
		max_heapify(input, 0, size - 1 - i); //re-heapify tree
	}
}

int main()
{
	//seed from clock
	srand(time(NULL));
	
	//PART A

	std::cout << "PART A:" << std::endl;

	//#1...
	InitArray(); //create array
	populateArray(); //generate random elements
	selectionSort(arr, size);
	heap_sort(arr, size);
	//...#4

	long int iterations = 100;

	//timers
	std::chrono::time_point<std::chrono::steady_clock> begin;
	std::chrono::time_point<std::chrono::steady_clock> end;

	//elapsed time
	long long int heapSort = 0;
	long long int selecSort = 0;

	//average time calculation (failure when selection sort time overflows)
	for (int i = 0; i < iterations; i++)
	{
		populateArray(); //randomize array
		begin = std::chrono::high_resolution_clock::now();
		heap_sort(arr, size);
		end = std::chrono::high_resolution_clock::now();
		heapSort += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count(); //incrementing by delta time

		populateArray(); //randomize array
		begin = std::chrono::high_resolution_clock::now();
		selectionSort(arr, size);
		end = std::chrono::high_resolution_clock::now();
		selecSort += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count(); //incrementing by delta time
	}

	double averageHeap = heapSort / iterations;

	std::cout << "Average runtime of heap sort with size " << size << " and " << iterations << " repititions: " << std::endl;
	std::cout << averageHeap << " nanoseconds" << std::endl;

	double averageSelec = selecSort / iterations;

	std::cout << "Average runtime of selection sort with size " << size << " and " << iterations << " repititions: " << std::endl;
	std::cout << averageSelec << " nanoseconds" << std::endl;

	std::cout << "\nSelection sort took: " << (averageSelec / averageHeap) * 100 << "% longer" << std::endl;

	std::cout << "--------------------------------------------------" << std::endl;
	//PART B
	//Sorting array with heap sort
	std::cout << "PART B: " << std::endl;
	
	size = 10;
	arr = new int[size];
	populateArray();

	build_MaxHeap(arr, size);
	std::cout << "Unsorted: " << std::endl;
	printArray(arr);

	heap_sort(arr, size);
	std::cout << "Sorted: " << std::endl;
	printArray(arr);

	system("pause");
	return 0;
}