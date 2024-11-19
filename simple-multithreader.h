#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>
#include <chrono>

int user_main(int argc, char **argv);

void demonstration(std::function<void()> && lambda) {
  lambda();
}

int main(int argc, char **argv) {
  int x=5,y=1;
  auto lambda1 = [x, &y](void) {
    y = 5;
    std::cout<<"====== Welcome to Assignment-"<<y<<" of the CSE231(A) ======\n";
  };
  demonstration(lambda1); 

  int rc = user_main(argc, argv);
 
  auto lambda2 = []() {
    std::cout<<"====== Hope you enjoyed CSE231(A) ======\n";
  };
  demonstration(lambda2);
  return rc;
}

#define main user_main


