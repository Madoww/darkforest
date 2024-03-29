//
//  Timer.cpp
//  dark_forest
//
//  Created by Filip Szafran on 08/08/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#include "Timer.hpp"

Timer::Timer()
{
    m_startpoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    stop();
}

void Timer::stop()
{
    auto end_timepoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startpoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();
    auto duration = end - start;
    
    double ms = duration*0.001;
    
    std::cout<<ms<<std::endl;
}
