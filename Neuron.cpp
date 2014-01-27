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
#include "neuron.h"
#include "synapse.h"
#include "math.h"

CNeuron::CNeuron(void)
: m_dValue(0)
{
   m_dRawError = 0;
   m_dValue = 0;
}

CNeuron::~CNeuron(void)
{
   CSynapseVector::iterator it;
   for (it = m_vInputs.begin(); it != m_vInputs.end(); it++)
   {
      delete (CSynapse *)(*it);
   }
   m_vInputs.clear();
}

void CNeuron::AddInput(CSynapse * pInput)
{
   m_vInputs.push_back(pInput);
}

void CNeuron::Calculate(void)
{
   double dTotal = 0;
   CSynapse *pSynapse = NULL;
   CSynapseVector::iterator it;
   //total the inputs
   for (it = m_vInputs.begin(); it != m_vInputs.end(); it++)
   {
      pSynapse = (CSynapse *)(*it);
      dTotal += pSynapse->GetValue();
   }
   
   //sigmoid squashing, don't calculate > 50 or < -50
   if (dTotal > 50) m_dValue = 1;
   else if (dTotal < -50) m_dValue = 0;
        else m_dValue = Sigmoid(dTotal);
}

double CNeuron::Sigmoid(double dTotal)
{
   return 1.0 / (1.0+exp(-1.0*dTotal));
}

double CNeuron::GetValue(void)
{
   return m_dValue;
}

void CNeuron::CalcError()
{
   CSynapse *pSynapse = NULL;
   CSynapseVector::iterator it;

   //multiply raw error by derivative of squashing sigmoid
   double dError = m_dValue * (1-m_dValue)* m_dRawError;
   
   //have all inputs put their piece of this error back onto their source nodes
   for (it = m_vInputs.begin(); it != m_vInputs.end(); it++)
   {
      pSynapse = (CSynapse *)(*it);
      pSynapse->PropDownError(dError);
   } 
   //reset raw error
   m_dRawError = 0;
}

//synapses can propagate their errors back this way
void CNeuron::AddToRawError(double dWeightedDelta)
{
   m_dRawError += dWeightedDelta;
}
