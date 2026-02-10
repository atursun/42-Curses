
#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <sys/time.h>

class PmergeMe {
private:
    std::vector<int> t_vector;
    std::deque<int>  t_deque;

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe &operator=(const PmergeMe& other);
    ~PmergeMe();

    void add_to_containers(int argc, char **args);
    void sort_elements_in_vector(std::vector<int>& array);
    void sort_elements_in_deque(std::deque<int>& array); 
    void calculate_duration();
};
