/******************************************************************************
 * ANNKit is a platform independent C++ implementation of a 3 layer
 * neural net trained by back propagation.
 * 
 * Copyright of Gerry Ens and GoWest Robotics. www.GoWestRobotics.com
 * You are free to use, alter and redistribute this code for all non-commercial 
 * purposes. Commercial use is also allowed under these conditions:
 * 1) Notify the author by email at: Gerry@GoWestRobotics.com
 * 2) Include this header intact somewhere in any file using all or part of 
 *    this code 
 * 3) Clearly mark any modifications to this code
 *****************************************************************************/ 
#include "valuevector.h"

CValueVector::CValueVector(void)
{
}

//initializes with n 0 values.
//any pushing during run-time (not initialization) requires a cs.
CValueVector::CValueVector(int n)
{
   for (int i = 0; i < n; i++)
   {
      this->push_back(0);
   }
}

CValueVector::~CValueVector(void)
{
}
