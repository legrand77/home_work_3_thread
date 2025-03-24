#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void findMin(vector<int>& vec, int& i, int& Size, int& minIndex, promise<void> prom)
{

	for (int j = i + 1; j < Size; j++)
	{
		if (vec[minIndex]>vec[j])
		{
			minIndex = j;
		}
	}
	
	prom.set_value();
};


int main() {

	setlocale(LC_ALL, "rus");

	vector<int>vec{ 2, 4, 56, 23, 12, 78,59,34,6,20,100 };

	int Size = vec.size();
	int minIndex{};
	for (int i = 0; i < Size - 1; i++)
	{
		promise<void> prom;
		future<void> future_res = prom.get_future();
		minIndex = i;
		auto Min = async(findMin, ref(vec), ref(i), ref(Size), ref(minIndex), move(prom));
		future_res.get();
		if (vec[i] > vec[minIndex])
		{
			swap(vec[i], vec[minIndex]);
		}
	}
			
	cout << "После сортировки: " << endl;;
		for (auto i : vec) {
			cout << i << endl;
		
		}

	return EXIT_SUCCESS;
}
