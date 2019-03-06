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
#ifndef __EXAMPLE_CLASS__
#define __EXAMPLE_CLASS__

#include "ValueVector.h"

/******************************************************************************
CExample is a container for two valuevectors, inputs and outputs
It provides two accessors to get pointers to these vectors
******************************************************************************/
class CExample
{
public:
   CExample(void);
   CExample(unsigned nInputs, unsigned nOutputs);
   virtual ~CExample(void);
	//copy constructor
	CExample(CExample& cexRHS);
   //= operator
   CExample &operator=(CExample& cexRHS);

protected:
   CValueVector *m_pvdInputs;
   CValueVector *m_pvdOutputs;
public:
   //accessors
   CValueVector *GetInputs(void);
   CValueVector *GetOutputs(void);
   void SetOutputs(CValueVector *pvdOutputs);
   void SetInputs(CValueVector *pvdInputs);

   void   SetInputValue(unsigned i, double dValue);
   double GetInputValue(unsigned i);
   void   SetOutputValue(unsigned i, double dValue);
   double GetOutputValue(unsigned i);
};
#endif //__EXAMPLE_CLASS__
