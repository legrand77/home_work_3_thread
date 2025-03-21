#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;


void selectionSort(vector<int>& array, promise<void> pr) {
	int size = array.size();
	int  min;
	for (int i = 0; i < size - 1; i++) {
		min = i; 
		for (int j = i + 1; j < size; j++) {
			
			if (array[min] > array[j]) {
			
				min = j; 
			}
		}
		int temp = array[i]; 
		array[i] = array[min]; 
		array[min] = temp; 
		
	}
	this_thread::sleep_for(1000ms);
        pr.set_value();
}


int main(){
	vector<int> arr1{2, 4, 56, 23, 12, 78,59,34};
	promise<void> pr;
	future<void> fut = pr.get_future();
	auto t1 = async(selectionSort, ref(arr1), move(pr));
	fut.wait();
	for (auto i:arr1){

		cout << i << endl;
	}
	return EXIT_SUCCESS;
}