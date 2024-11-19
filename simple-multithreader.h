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
    (*func)();
    return nullptr;
}

int iteration_begin_finder(int i, int length_of_each_thread, int low){
	int a = ((i * length_of_each_thread) + low);
	if (a < 0){
		cerr << "iteration finder failed" << endl;
            	exit(EXIT_FAILURE);
	}
	return a;
}

int iteration_end_finder(int i, int numThreads, int high, int iteration_begin_point, int length_of_each_thread){
	if ( i == numThreads - 1){
		return high;
	}
	else{
		return iteration_begin_point + length_of_each_thread;
	}
}



void parallel_for(int low, int high, function<void(int)> &&lambda, int numThreads){

	if (high < low){
		cout << "The high and low bounds are given incorrectly. \n ";
		return;
	}

	clock_t start = get_time();
	
	int interate_from_to = high - low;
	int length_of_each_thread = ((high - low) / numThreads);
	
	pthread_t threads_made[numThreads];
	function<void()> functions[numThreads];
	
	int threads_made_yet = 0;
	
	for ( int i = 0 ; i < numThreads ; i++){
	
		int iteration_begin_point = iteration_begin_finder(i, length_of_each_thread, low);
		int iteration_end_point = iteration_end_finder(i, numThreads, high, iteration_begin_point, length_of_each_thread);
		
		functions[i] = [iteration_begin_point , iteration_end_point , &lambda](){
			for (int j = iteration_begin_point; j < iteration_end_point; j++){
				lambda(j);
			}
		};
		
		int error = pthread_create(&threads_made[i] , NULL , parallel_execution, &functions[i]);
		threads_made_yet++;
		
		if (error != 0){
			cout << "Error making thread number " << threads_made_yet << "\n";
			cerr << "*THREAD CREATION ERROR*" << endl;
			exit(EXIT_FAILURE);
		}
		
	}
	
	for (int i = 0; i < numThreads; ++i) {
        	if (pthread_join(threads_made[i], NULL) != 0) {
            		cerr << "Deadlock here, no join" << endl;
            		exit(EXIT_FAILURE);
        	}
    	}
	
	clock_t end = get_time();
	
	cout << "Total threads made = " << threads_made_yet << " \n";
	
	cout<<"Total time = " << static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC << " milliseconds \n";
	
}


void parallel_for(int low1, int high1,  int low2, int high2, function<void(int, int)>  &&lambda, int numThreads){

	if (high1 < low1){
		cout << "The high1 and low1 bounds are given incorrectly. \n ";
		return;
	}
	
	if (high2 < low2){
		cout << "The high2 and low2 bounds are given incorrectly. \n ";
		return;
	}
	
	clock_t start = get_time();
	
	int interate_main_from_to = high1 - low1;
	int length_of_each_thread_of_main = ((high1 - low1) / numThreads);
	
	pthread_t threads_made[numThreads];
	function<void()> functions[numThreads];
	
	int threads_made_yet = 0;
	
	for(int i = 0; i < numThreads; i++){
		int iteration_begin = iteration_begin_finder(i, length_of_each_thread_of_main, low1);
		int iteration_end = iteration_end_finder(i, numThreads, high1, iteration_begin, length_of_each_thread_of_main);
		functions[i] = [iteration_begin , iteration_end , low2, high2, &lambda](){
			for (int j = iteration_begin; j < iteration_end; j++){
				for (int k = low2; k < high2; k++){
					lambda(j , k);
				}
			}
		};
		
		int error = pthread_create(&threads_made[i] , NULL , parallel_execution, &functions[i]);
		threads_made_yet++;
		
		if (error != 0){
			cout << "Error making thread number " << threads_made_yet << "\n";
			cerr << "*THREAD CREATION ERROR*" << endl;
			exit(EXIT_FAILURE);
		}
	}
	
	for (int i = 0; i < numThreads; ++i) {
        	if (pthread_join(threads_made[i], NULL) != 0) {
            		cerr << "Deadlock here, no join" << endl;
            		exit(EXIT_FAILURE);
        	}
    	}
	
	clock_t end = get_time();
	
	cout << "Total threads made = " << threads_made_yet << " \n";
	
	cout<<"Total time = " << static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC << " milliseconds \n";
	
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
    cout<<"====== Hope you enjoyed CSE231(A) ======\n \n";
  };
  demonstration(lambda2);
  return rc;
}

#define main user_main

