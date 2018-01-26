#include <pthread.h>
#include <stdint.h>
#include <iostream>
#include <sstream>

// Let's hear it for ~Global Variables~
int err; // needs to be global. If it wasn't global, a child thread would return a local variable on the child's address space, which is not availible in the parent's address space
uint64_t globalCount;
//uint64_t[] workerCounts;
uint64_t MAX_COUNTER;
uint64_t NUM_WORKERS;

void* incrementCounter(void* ptr){
  //workerCounts[*ptr] = 0
  while(globalCount < MAX_COUNTER){
    //workerCounts[threadID]++;
    globalCount++;
  }
}

int main(int argc, char** argv)
{
  globalCount = 0;
  
  if(argc > 2){
    std::istringstream(argv[1]) >> MAX_COUNTER;
    std::istringstream(argv[2]) >> NUM_WORKERS;
  }
  std::cout << "MAX_COUNTER: " << MAX_COUNTER << std::endl
	    << "NUM_WORKERS: " << NUM_WORKERS << std::endl;
  
  uint64_t ii;
  pthread_t tid[NUM_WORKERS];
  for(ii = 0; ii < NUM_WORKERS; ii++){
    err = pthread_create(&tid[ii], NULL, incrementCounter, (void *) ii);
  }
  
  for(uint64_t i = 0; i < NUM_WORKERS; i++){
    err = pthread_join(tid[i], NULL); // replace NULL if you want completion status 
  }

  std::cout << "Final counter value: " << globalCount << std::endl;
  
  return 0; 
}
