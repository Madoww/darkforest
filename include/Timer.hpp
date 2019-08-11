//
//  Timer.hpp
//  dark_forest
//
//  Created by Filip Szafran on 08/08/2019.
//  Copyright © 2019 Filip Szafran. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();
    void stop();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startpoint;
};

#endif /* Timer_hpp */
