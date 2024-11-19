#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>
#include <chrono>
#include <ctime>

using namespace std;


int user_main(int argc, char **argv);

void parallel_for(int low1, int high1,  int low2, int high2, function<void(int, int)>  &&lambda, int numThreads);

void parallel_for(int low, int high, function<void(int)> &&lambda, int numThreads);

void demonstration(function<void()> && lambda) {
  lambda();
}

clock_t get_time(){
	return clock();
}

void* parallel_execution(void* arg) {
    auto* func = reinterpret_cast<function<void()>*>(arg);
    (*func)(); // Execute the function pointer
    return nullptr;
}

void parallel_for(int low, int high, function<void(int)> &&lambda, int numThreads){
	clock_t start = get_time();
	
	int interate_from_to = high - low;
	int length_of_each_thread = ((high - low) / numThreads);
	
	pthread_t threads_made[numThreads];
	function<void()> functions[numThreads];
	
	for ( int i = 0 ; i < numThreads ; i++){
		int iteration_begin_point = ((i * length_of_each_thread) + low);
		int iteration_end_point;
		if (i == numThreads - 1){
			iteration_end_point = high;
		}
		else{
			iteration_end_point = iteration_begin_point + length_of_each_thread;
		}
		
		functions[i] = [iteration_begin_point , iteration_end_point , &lambda](){
			for (int j = iteration_begin_point; j < iteration_end_point; j++){
				lambda(j);
			}
		};
		
		int error = pthread_create(&threads_made[i] , NULL , parallel_execution, &functions[i]);
		//if (error == 0){
		//	cout << "Thread created " << i << "\n";
		//}
		
	}
	
	for (int i = 0; i < numThreads; ++i) {
        	if (pthread_join(threads_made[i], NULL) != 0) {
            		cerr << "Deadlock here, no join" << endl;
            		exit(EXIT_FAILURE);
        	}
    	}
	
	clock_t end = get_time();
	
	cout<<"Total time = " << static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC << " milliseconds  ... yes. \n";
	
}

void parallel_for(int low1, int high1,  int low2, int high2, function<void(int, int)>  &&lambda, int numThreads){
	clock_t start = get_time();
	
	cout<<"In the parallelizer rn\n";
	
	clock_t end = get_time();
	
	cout<<"Total time = " << static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC << " milliseconds  ... yes. \n";
}

int main(int argc, char **argv) {
  int x=5,y=1;
  auto lambda1 = [x, &y](void) {
    y = 5;
    cout<<"====== Welcome to Assignment-"<<y<<" of the CSE231(A) ======\n";
  };
  demonstration(lambda1); 

  int rc = user_main(argc, argv);
 
  auto lambda2 = []() {
    cout<<"====== Hope you enjoyed CSE231(A) ======\n";
  };
  demonstration(lambda2);
  return rc;
}

#define main user_main

