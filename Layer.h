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
#ifndef __LAYER_CLASS__
#define __LAYER_CLASS__

#include <vector>
#include "Neuron.h"

/******************************************************************************
CLayer is a vector of Neurons.
There is no other added functionality
******************************************************************************/
class CLayer :
   public std::vector<CNeuron *>
{
public:
   CLayer(void);
   virtual ~CLayer(void);
};
#endif //__LAYER_CLASS__
