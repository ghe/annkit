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
#ifndef __TRAININGSSET_CLASS
#define __TRAININGSSET_CLASS

#include <vector>
#include "Example.h"

/******************************************************************************
CTrainingSet is a vector of CExamples.
There is no other added functionality
******************************************************************************/
class CTrainingSet :
   public std::vector<CExample *>
{
public:
   CTrainingSet(void);
   virtual ~CTrainingSet(void);
   void pop_front(void);
};
#endif //__TRAININGSSET_CLASS
