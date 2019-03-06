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
#ifndef __NEURON_CLASS__
#define __NEURON_CLASS__

#include "SynapseVector.h"

/******************************************************************************
CNeuron is a node in a layer
It has a list of inputs, synapses, storeed in a CSynapseVector
Calculate provides the output value, using the isgmoid function
CalcError calcutaes the error and propagates it down to the synapses
******************************************************************************/
class CNeuron
{
public:
   CNeuron(void);
   ~CNeuron(void);
protected:
   CSynapseVector m_vInputs;
   double m_dRawError;

public:
   void AddInput(CSynapse * pInput);
   void Calculate(void);
   double m_dValue;
   double GetValue(void);
   double Sigmoid(double dTotal);
   void CalcError();
   void AddToRawError(double dWeightedDelta);
};
#endif //__NEURON_CLASS__
