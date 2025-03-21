#include <iostream>
#include <vector>
#include <random>
#include <future>

using namespace std;
template<typename T, typename F>
void for_each_parallel(T begin, T end, F func){
    auto Size = end - begin;
	if (Size <= 1){
		func(*begin);
		return;
	}
	auto midle = begin;
	midle+=1;
	auto R = async(for_each_parallel<T,F>, begin, midle, func);
    for_each_parallel(midle, end, func);
}

void printVector(vector<int> v){
	cout << "Container: { ";
	for (auto i:v){
		cout << i << " ";
	}
   cout << "};" << endl;
}

int main(){ 
	int N = 10;
	vector<int> v{};
	for (int i = 0; i < N; ++i){
		v.push_back(rand() % 30);
	}
	printVector(v);
	auto f = [](int& n) {n*=2; };
	for_each_parallel(v.begin(), v.end(), f);
	printVector(v);
	return EXIT_SUCCESS;
}
