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
#ifndef __SYNAPSEVECTOR_CLASS__
#define __SYNAPSEVECTOR_CLASS__

#include <vector>
class CSynapse;

/******************************************************************************
CSynapseVector is a vector of CSynapse.
There is no other added functionality
******************************************************************************/
class CSynapseVector :  public std::vector<CSynapse *>
{
public:
   CSynapseVector(void);
   virtual ~CSynapseVector(void);
};
#endif //__SYNAPSEVECTOR_CLASS__
