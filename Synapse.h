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
#ifndef __SYNAPSE_CLASS__
#define __SYNAPSE_CLASS__

class CNeuron;

/******************************************************************************
CSynapse is a link between two neurons
it only holds a pointer to its source neuron
Neurons hold a list of inputs to synapses
PropDownError is called by these neurons to calculate the error
  and adjust the weight
******************************************************************************/
class CSynapse
{
public:
   CSynapse(void);
   ~CSynapse(void);
   
protected:
   CNeuron *m_pSource;
   double m_dWeight;
public:
   void SetWeight(double dWeight);
   void SetSource(CNeuron * pSource);
   double GetValue(void);
   void PropDownError(double dError);
   
   double *m_pdLearningRate;
};
#endif //__SYNAPSE_CLASS__
