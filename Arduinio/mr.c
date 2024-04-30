#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "kvlist.h"


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <dirent.h>
#include <err.h>
#include <stdbool.h>
#include <unistd.h>

#include "hash.h"
#include "mr.h"



// helper datatype
//===========================================================
  // for referencing mapper inside of thread argument
  struct mapperThreadArgs {
    mapper_t mapper; //referencing mapper function
    kvlist_t* list;
  };

  // for referencing reducer inside of thread argument
  struct reducerThreadArgs {
    reducer_t reduce; //referencing reduce function
    kvlist_t* list;
  };
//===========================================================



// helper function
//===========================================================

    // creating array of kvlist function 
    kvlist_t** create_kvlist_array(size_t num_divider) {
      kvlist_t** array_list = (kvlist_t**)malloc(num_divider * sizeof(kvlist_t*));
      if (array_list == NULL) {
          fprintf(stderr, "Error: Allocation failed\n");
          return NULL;
      }
      // initiallize them and free if problem occyr
      for (size_t i = 0; i < num_divider; i++) {
        array_list[i] = kvlist_new();
        if (array_list[i] == NULL) {
            // free up
            for (size_t j = 0; j < i; j++) {
                kvlist_free(&array_list[j]);
            }
            free(array_list);
            fprintf(stderr, "Error: Allocation failed\n");
            return NULL;
        }
      }
      return array_list;
    }


    // input split function, spliting the kvlist input into multiple kvlist for thread
    kvlist_t** input_split (kvlist_t* input, size_t num_divider) {
        
        //create list array using helper function
        kvlist_t** list_array = create_kvlist_array(num_divider);

        // create input list iteration and handle problem
        kvlist_iterator_t* iter = kvlist_iterator_new(input);
        if (iter == NULL) {
            // free up
            for (size_t i = 0; i < num_divider; i++) {
                kvlist_free(&list_array[i]);
            }
            free(list_array);
            fprintf(stderr,"Error: Allocation failed\n");
            return NULL;
        }


        int traverse = 1;
        while (1) {
            kvpair_t* pair = kvlist_iterator_next(iter);
            if (pair == NULL) {
                break;
            }
            kvlist_append(list_array[traverse - 1], pair);
            traverse = (traverse % num_divider) + 1;
        }
        kvlist_iterator_free(&iter);


        // debugging 
        // print the kvlist array into the terminal for checking
        // for (size_t i = 0; i < num_divider; i++) {
        //     kvlist_print(1, list_array[i]); 
        // }

        
        return list_array;
    }


    void* testing_function_thread() {
      int time = 0;
      while (time < 1000000000) {
        time ++;
      }
      printf("thread: \n");

      return NULL;
    }

    
    // mapper function for the thread
    void* mapper_threading(void* arg) {
        // retype casting the argument input from pthread
        struct mapperThreadArgs* thread_args = (struct mapperThreadArgs*)arg;
        mapper_t mapper = thread_args->mapper;
        kvlist_t* list = thread_args->list;
        kvlist_t* output = kvlist_new();
        kvlist_iterator_t* iter = kvlist_iterator_new(list);

        if (output == NULL) {
          kvlist_free(&list);
          fprintf(stderr, "Error: Allocation failed\n");
          pthread_exit(NULL); // Exit with NULL value

        }
        if (iter == NULL) {
          // free up
          kvlist_free(&list);
          kvlist_free(&output);
          fprintf(stderr,"Error: Allocation failed\n");
          pthread_exit(NULL);
          // free the previous one as well

        }
        while(1) {
            kvpair_t *pair = kvlist_iterator_next(iter);
            // check end of list
            if (pair == NULL) {
                break;
            }

            // mapper function on itself
            mapper(pair, output);
        }

        //free and exit
        kvlist_iterator_free(&iter);
        pthread_exit(output);
    }

    // map phase with multiple threads
    kvlist_t** map_phase(kvlist_t** list_array, size_t num_threads, mapper_t mapper) {
        //threads array
        pthread_t threads[num_threads];
        struct mapperThreadArgs thread_args[num_threads];

      //create array to result after thread
        kvlist_t** output = create_kvlist_array(num_threads);


        // Assign a thread to each one of the indices
        for (size_t i = 0; i < num_threads; i++) {
            // creat the thread
            thread_args[i].mapper = mapper;
            thread_args[i].list = list_array[i];

            if (pthread_create(&threads[i], NULL, mapper_threading, (void*)&thread_args[i]) != 0) {
                fprintf(stderr, "Error: Failed to create thread %zu\n", i);
                exit(EXIT_FAILURE);
            }
        }

        

        // Wait for all threads to finish
        for (size_t i = 0; i < num_threads; i++) {
          kvlist_t * thread_result;
          if (pthread_join(threads[i], (void**)&thread_result) != 0) {
            fprintf(stderr, "Error: Failed to join thread\n");
            exit(EXIT_FAILURE);
          }

          //output[i] = thread_result;
          output[i] = (kvlist_t*)thread_result;
        }

        // // for debugging
        // for (size_t i = 0; i < num_threads; i++) {
        //     kvlist_print(1, output[i]); 
        // }
    
        return output;
    }

    //////////////////////////////////////////
    // reducer function for the thread
    void* reducer_threading(void* arg) {
        // retype casting the argument input from pthread
        struct reducerThreadArgs* thread_args = (struct reducerThreadArgs*)arg;
        reducer_t reducer = thread_args->reduce;
        kvlist_t* list = thread_args->list;
        kvlist_t* output = kvlist_new();
        kvlist_iterator_t* iter = kvlist_iterator_new(list);

        if (output == NULL) {
          kvlist_free(&list);
          fprintf(stderr, "Error: Allocation failed\n");
          pthread_exit(NULL); // Exit with NULL value

        }
        if (iter == NULL) {
          // free up
          kvlist_free(&list);
          kvlist_free(&output);
          fprintf(stderr,"Error: Allocation failed\n");
          pthread_exit(NULL);
          // free the previous one as well

        }

        //traverse the list to fine the number of unique key
        int unique = 0;
        char* key1 = NULL;
        while (1) {
            kvpair_t* pair1 = kvlist_iterator_next(iter);
            // check end of list
            if (pair1 == NULL) {
                break;
            }

            // key is different from the previous one
            if (key1 == NULL || strcmp(key1, pair1->key) != 0) {
                // update key
                unique++;
                key1 = pair1->key;
            }

        }

        //create a array of list to split they key so that each list has the same key
        kvlist_t** array_unique = create_kvlist_array(unique);

        // reset the iterator for the second traversal
        kvlist_iterator_free(&iter);
        iter = kvlist_iterator_new(list);
        
        // traversing the list again to split it 
        int assign = 0;
        char* key = NULL;
        while (1) {
            kvpair_t* pair = kvlist_iterator_next(iter);
            if (pair == NULL) {
                break;
            }

            // to the corresponding list in the array_unique
            if (key == NULL || strcmp(key, pair->key) != 0) {
                // update key
                assign++;
                key = pair->key;

            }
            kvlist_append(array_unique[assign-1], pair);
        }



        //reduce
        for (int i = 0; i < unique; i++) {
          char* key3 = NULL;
          kvlist_iterator_t* iter_3 = kvlist_iterator_new(array_unique[i]);
            if (iter_3 == NULL) {
              // Handle allocation failure
              kvlist_free(&list);
              kvlist_free(&output);

              for (int j = 0; j < unique; j++) {
                  kvlist_free(&array_unique[j]);
              }

              pthread_exit(NULL);
          }
          
          kvpair_t* pair1 = kvlist_iterator_next(iter_3);
          // check end of list
          if (pair1 == NULL) {
              break;
          }

          // key is different from the previous one
          if (key3 == NULL || strcmp(key3, pair1->key) != 0) {
              // update key
              key3 = pair1->key;
          }
          reducer(key3,array_unique[i], output);
      
          kvlist_iterator_free(&iter_3);
        }



        // free memory and exit
        for (int i = 0; i < unique; i++) {
          kvlist_free(&array_unique[i]);
        }


        //free and exit
        kvlist_iterator_free(&iter);
        pthread_exit(output);
    }

    // reducer phase with multiple threads
    kvlist_t** reduce_phase(kvlist_t** list_array, size_t num_threads, reducer_t reducer) {
        //threads array
        pthread_t threads[num_threads];
        struct reducerThreadArgs thread_args[num_threads];

      //create array to result after thread
        kvlist_t** output = create_kvlist_array(num_threads);


        // Assign a thread to each one of the indices
        for (size_t i = 0; i < num_threads; i++) {
            // creat the thread
            thread_args[i].reduce = reducer;
            thread_args[i].list = list_array[i];

            if (pthread_create(&threads[i], NULL, reducer_threading, (void*)&thread_args[i]) != 0) {
                fprintf(stderr, "Error: Failed to create thread %zu\n", i);
                exit(EXIT_FAILURE);
            }
        }

        

        // Wait for all threads to finish
        for (size_t i = 0; i < num_threads; i++) {
          kvlist_t * thread_result;
          if (pthread_join(threads[i], (void**)&thread_result) != 0) {
            fprintf(stderr, "Error: Failed to join thread\n");
            exit(EXIT_FAILURE);
          }

          //output[i] = thread_result;
          output[i] = (kvlist_t*)thread_result;
        }

        // // for debugging
        // for (size_t i = 0; i < num_threads; i++) {
        //     kvlist_print(1, output[i]); 
        // }
    
        return output;
    }


    // shuffle phase
    kvlist_t** hash_num_reduce(size_t num_mapper, size_t num_reducer, kvlist_t** list_array) {

      // iterate over to see howmany list needed
      kvlist_t** shuffleKvlistArray = create_kvlist_array(num_reducer);
      for(size_t i = 0; i < num_mapper; i++) {
        // create input list iteration and handle problem
        kvlist_iterator_t* iter = kvlist_iterator_new(list_array[i]);
        if (iter == NULL) {
            //free up
            fprintf(stderr, "Error: Allocation failed\n");
            // Free memory and return NULL
            for (size_t j = 0; j < num_mapper; j++) {
                kvlist_free(&list_array[j]);
                free(list_array);
            }
            free(list_array);
            for (size_t j = 0; j < num_reducer; j++) {
                kvlist_free(&shuffleKvlistArray[j]);
            }
            free(shuffleKvlistArray);
            return NULL;
        }

        while(1) {
            kvpair_t *pair = kvlist_iterator_next(iter);
            if (pair == NULL) {
                break;
            }
            unsigned long hash_value =  hash(pair->key);
            
            // print for debug
            // printf("pair->key: %s\n", pair->key);

          
            int correspond_list = (hash_value  % num_reducer);
            
            
            
            // printf("correspond list: %i\n", correspond_list);

            kvlist_append(shuffleKvlistArray[correspond_list], pair);
        }
        kvlist_iterator_free(&iter);
      }


      //sorting for output
      for (size_t i = 0; i < num_reducer; i++) {
        kvlist_sort(shuffleKvlistArray[i]);
      }


      return shuffleKvlistArray;
    } 


    // // free list array 
    // void kvlist_array_free (kvlist_t ***list_array) {
      
    //   kvlist_iterator_t iter = kvlist_iterator_new(*list_array[0])
    //   while ()
    // }
//===========================================================






void map_reduce(mapper_t mapper, size_t num_mapper, reducer_t reducer,
                size_t num_reducer, kvlist_t* input, kvlist_t* output) {



    // check for num_mapper and num_reducer
    if (num_mapper <= 0 || num_reducer <= 0) {
        fprintf(stderr,"Error: Non positive of number of mapper and reducer threads");
        return;
    }

    

    /*
    SPLIT 
    ============================================================================
    In the split phase (also called the partition phase), you split the input 
    list into num_mapper smaller lists so that each smaller list can be 
    processed by different threads independently.
    */
    // kvlist_print(1, input);
    // printf("\n==========SPLIT phase==========\n");
    kvlist_t** list_array_input = input_split(input, num_mapper);




    /*
    MAP
    ============================================================================
    In the map phase, you create num_mapper threads. Each thread is responsible
     for a smaller list from the previous phase and calls the mapper function 
     to obtain a new list.
    */
    // printf("\n==========Map phase==========\n");
    kvlist_t** outputMapArray = map_phase(list_array_input, num_mapper, mapper);

    // for (int i = 0; i < num_mapper; i++) {
    //   printf("i: %i\n", i);
    //   kvlist_print(1, outputMapArray[i]); 
    // }

    /*
    SHUFFLE
    ============================================================================
    In the shuffle phase, you create num_reducer independent lists 
    that can be processed in the next phase. Since you need to provide 
    all pairs with the same key to the reducer function, the same key 
    must be assigned to the same list. For example, if you have two pairs 
    with the same key, those two pairs must be assigned to the same list so 
    that they can be passed to reducer together.
    */
    // printf("\n==========Shuffle phase==========\n");

    kvlist_t** shuffle = hash_num_reduce(num_mapper, num_reducer, outputMapArray);

    // for (size_t i = 0; i < num_reducer; i++) {
    //   // printf("i: %zu\n", i);
    //   kvlist_print(1, shuffle[i]); 
    // }


    /*
    REDUCE
    ============================================================================
    In the reduce phase, you create num_reducer threads. Each thread is responsible 
    for a smaller list from the previous phase and calls the reducer function to 
    aggregate results. When calling reducer, you need to construct a list of all pairs with 
    the same key. There are many ways to do this, but one way is to use the 
    kvlist_sort function.
    */
    // printf("\n==========REDUCE phase==========\n");
    kvlist_t** outputReduceArray = reduce_phase(shuffle, num_reducer, reducer);

    // for (size_t i = 0; i < num_reducer; i++) {
    //   // printf("i: %zu\n", i);
    //   kvlist_print(1, outputReduceArray[i]); 
    // }



   /*
  OUTPUT
  ============================================================================
  You need to store the results in the output list passed as an argument. 
  Use kvlist_extend to move pairs to output.
  */
  // printf("\n==========OUTPUT phase==========\n");
  for (size_t i = 0; i < num_reducer; i++) {
    // printf("When i is : %i\n", i);
    kvlist_extend(output,outputReduceArray[i]); 
    // kvlist_print(1, output);
  }
  kvlist_sort(output);

}
