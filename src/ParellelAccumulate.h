#pragma once
/**
 ***********************************************************************
 *
 * @brief
 *   TODO
 *
 * @copyright
 *   Copyright 2018 xxxx.  All rights reserved.
 *   Proprietary and confidential material.  Distribution,
 *   use, and disclosure restricted by xxx.
 *
 ***********************************************************************
 */
#include <algorithm>
#include <numeric>
#include <thread>
#include <vector>
#include <functional>


template<typename Iterator, typename T>
struct accumulate_block{
    void operator()(Iterator first, Iterator last, T& result)
        {
         result = std::accumulate(first, last, result);
        }

};

template<typename Iterator, typename T>

T parellel_accumulate(Iterator first, Iterator last, T init)
{
     auto length = std::distance(first , last);

     if(!length)
         return init;

     auto const min_per_thread = 25;
     auto const max_threads=
             ((length + min_per_thread -1)/min_per_thread);
     auto  hardware_threads = std::thread::hardware_concurrency();

     auto const num_threads = std::min((long int)(hardware_threads !=0 ? hardware_threads : 2) , max_threads);
     auto const block_size = length/num_threads;

     std::vector<T> results(num_threads);
     std::vector<std::thread> threads(num_threads -1);

     Iterator block_start = first;

     for(auto i = 0; i<(num_threads -1); i++)
     {
         Iterator block_end = block_start;
         std::advance(block_end, block_size);
         threads[i] = std::thread(accumulate_block<Iterator , T>(), block_start, block_end, std::ref(results[i]));
         block_start= block_end;
     }

     accumulate_block<Iterator , T>()( block_start, last, std::ref(results[num_threads -1]));

     std::for_each(threads.begin(),threads.end(),
     std::mem_fn(&std::thread::join));

     return std::accumulate(results.begin(),results.end(),init);

}
