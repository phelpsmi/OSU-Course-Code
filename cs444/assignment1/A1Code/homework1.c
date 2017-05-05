/*
File: homework1.c
Authors: Michael Phelps, Danial Garlock
Date: 10/10/2016
Description: Simulates the producer-consumer problem model using ptreads to represent
			 producers and consumers. Generates random timings for task completion using
			 rdrand or (if rdrand is unnavailable) Mersenne Twister.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <immintrin.h>
#include <string.h>
#include <time.h>

#include "mt19937ar.c"

unsigned int gen_rand();
void *produce(void *);
void *consume(void *);

struct item{
  int num;
  int length;
};

struct buffer_struct{
  struct item data[32];
  int count;
};

struct buffer_struct buffer;
pthread_mutex_t lock;
pthread_cond_t item_produced,item_consumed;
int rdrand = 0;

void *produce(void *param){
  int count;
  int id = *((int *)param);
  
  while(1){
    
    //sleep for 3-7 seconds
    sleep((gen_rand() % 5) + 3);
    
    pthread_mutex_lock(&lock);
    
    while(buffer.count >= 32){
      pthread_cond_wait(&item_consumed, &lock);
    }
    count = buffer.count;
    
    buffer.data[count].num = gen_rand() % 1000;
    buffer.data[count].length = (gen_rand() % 8) + 2;
    printf("Producer %d: Created a task #%d with a %d second completion time.\n",
      		id,
          buffer.data[count].num, 
          buffer.data[count].length);
           
    buffer.count++;
    printf("Producer %d: There are now %d items in the buffer.\n", id, buffer.count);
    
    pthread_cond_signal(&item_produced);
    pthread_mutex_unlock(&lock);
  }
}

void *consume(void *param){
  struct item current_item;
  int i;
  int id = *((int *)param);
  
  while(1){
    pthread_mutex_lock(&lock);
    
    while(buffer.count == 0){
      pthread_cond_wait(&item_produced, &lock);
    }
    
    current_item = buffer.data[0];
    //shift all the items in the buffer up one possition in the queue.
    for(i = 1; i < buffer.count; i++){
      buffer.data[i-1] = buffer.data[i];
    }
    buffer.count -= 1;
    printf("\tConsumer %d: Started task #%d\n", id, current_item.num);
    
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&item_consumed);
    
    sleep(current_item.length);
    printf("\tConsumer %d: Completed task #%d\n", id, current_item.num);
  }
}


unsigned int gen_rand(){
  unsigned int rnd = 0;
  

  if(rdrand == 0){
	  unsigned int eax;
	  unsigned int ebx;
	  unsigned int ecx;
	  unsigned int edx;
	  eax = 0x01;
	  
	  __asm__ __volatile__(
	  	                     "cpuid;"
	  	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	  	                     : "a"(eax)
	  	                     );

	  if(ecx & 0x40000000){
	  	rdrand = 1;
	  	printf("Using rdrand to generate random numbers\n");
	  } else {
	  	rdrand = 2;
	  	printf("Using mt19937ar to generate random numbers\n");
	  }
	}
	
  	if(rdrand == 1){
  		__asm__ __volatile__("rdrand %0" : "=r" (rnd) );
  	}
  	else{
  		rnd = genrand_int32();
  	}
    
    return rnd;
}

int main(int argc, char **argv)
{
	unsigned long init[4] = {time(NULL)+0x123, time(NULL)+0x234, time(NULL)+0x345, time(NULL)+0x456};
	unsigned long length = 4;
	init_by_array(init, length);
  
  buffer.count = 0;
  
  int producer_count = 1, consumer_count = 1, i;
  pthread_t *producers, *consumers;

  if(argc == 3){
  	producer_count = atoi(argv[1]);
  	consumer_count = atoi(argv[2]);
  }

  //Declare number of producers and consumers
  printf("Number of producers: %d\n", producer_count);
  printf("Number of consumers: %d\n", consumer_count);

  producers = malloc(sizeof(pthread_t) * producer_count);
  consumers = malloc(sizeof(pthread_t) * consumer_count);
  
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&item_produced, NULL);
  pthread_cond_init(&item_consumed, NULL);

  for(i = 0; i < producer_count; i++){
  	int *arg = malloc(sizeof(*arg));
  	*arg = i+1;
  	pthread_create(&(producers[i]), NULL, produce, arg);
  }
  for(i = 0; i < consumer_count; i++){
  	int *arg = malloc(sizeof(*arg));
  	*arg = i+1;
  	pthread_create(&(consumers[i]), NULL, consume, arg);
  }

  for(i = 0; i < producer_count; i++){
  	pthread_join(producers[i], NULL);
  }
  for(i = 0; i < consumer_count; i++){
  	pthread_join(consumers[i], NULL);
  }
  pthread_mutex_destroy(&lock);
	
	return 0;
}