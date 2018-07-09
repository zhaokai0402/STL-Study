// STL-Study.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"

// memory leak detection
#define _CRTDBG_MAP_ALLOC // memory leak info add file name and line number
#include <cstdlib>
#include <crtdbg.h>

#include <iostream>
#include "tiny_alloc.h"
#include "tiny_iterator.h"
#include "tiny_type_traits.h"
#include "tiny_numeric.h"
#include "tiny_vector.h"
#include <vector>
#include <numeric>
#include <iterator>

void tiny_alloc_unit_test();
void tiny_vector_unit_test();

int main(int argc, char *argv[])
{
    // if detected memory leaks, before program quit will print info.
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint(&s1); 	// memory snapshot s1

#if 0
	tiny_alloc_unit_test();
	tiny_vector_unit_test();
#endif // 0

	int ia[5] = {2, 2, 3, 4, 5};
	std::vector<int> iv(ia, ia + 5);

	std::cout << tiny::accumulate(iv.begin(), iv.end(), 0, std::minus<int>()) << std::endl;
	std::ostream_iterator<int> oite(std::cout, " ");
	tiny::adjacent_difference(iv.begin(), iv.end(), oite);
	std::cout << std::endl;

	tiny::adjacent_difference(iv.begin(), iv.end(), oite, std::plus<int>());
	std::cout << std::endl;

    _CrtMemCheckpoint(&s2);		// memory snapshot s2

    if(_CrtMemDifference(&s3, &s1, &s2)) // diff snapshot
    {
        _RPTF0( _CRT_WARN ,"_CrtMemDumpStatistics: \n");
        _CrtMemDumpStatistics(&s3);
    }
	printf("press any key to continue...");
	getchar();
    return 0;
}

#if 0
void tiny_alloc_unit_test()
{
    int* a = (int*)malloc_alloc::allocate(sizeof(int));
    a = (int*)malloc_alloc::reallocate(a, sizeof(int) * 2);
    a[0] = 10;
    a[1] = 11;
    malloc_alloc::deallocate(a);
}

void tiny_vector_unit_test()
{
	// vector() 
	vector<int> vec;
	cout << "vec: " << vec.size() << endl;
	for (int n : vec)
		cout << n << " ";
	cout << endl;
	
	// vector(size_t count, const T& value) 
	vector<int> vec1((size_t)20, 10);	/// = { 1, 2, 3 , 4, 5 };
	cout << "vec1: " << vec1.size() << endl;
	for (int n : vec1)
		cout << n << " ";
	cout << endl;

	// explicit vector(size_t count) 
	vector<int> vec2((size_t)20);	/// = { 1, 2, 3 , 4, 5 };
	cout << "vec2: " << vec.size() << endl;

	// vector(InputIterator first, InputIterator last) 
	vector<int> vec3(10, 20);	/// = { 1, 2, 3 , 4, 5 };
	for (int n: vec3)
		cout << n << " ";
	cout << endl;

#if 0
	// vector(InputIterator first, InputIterator last) 
	int a[10] = { 1, 2, 3 };
	vector<int> vec4(a, a+3);
	for(int n: vec4)
		cout << n << " ";
	cout << endl;

	// vector(const vector& other) 
	vector<int> vec5(vec4);
	for(int n: vec5)
		cout << n << " ";
	cout << endl;

	vector<int> vec6 = { 1, 2, 3, 4, 5, 6 };
	for(int n: vec6)
		cout << n << " ";
	cout << endl;
#endif
}
#endif