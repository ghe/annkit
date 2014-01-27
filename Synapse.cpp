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
#include "synapse.h"
#include "neuron.h"
#include "neuralnet.h"

CSynapse::CSynapse(void)
{
   m_dWeight = 0;
   m_pSource = NULL;
   m_pdLearningRate = NULL;
}

CSynapse::~CSynapse(void)
{
}

void CSynapse::SetWeight(double dWeight)
{
   m_dWeight = dWeight;
}

void CSynapse::SetSource(CNeuron * pSource)
{
   m_pSource = pSource;
}

double CSynapse::GetValue(void)
{
   double dValue = m_pSource->GetValue();
   return m_dWeight * dValue;
}

//propagates down error and then updates itself
void CSynapse::PropDownError(double dError)
{
   //prop error
   m_pSource->AddToRawError(m_dWeight * dError);
   
   //update weight
   double dSourceValue = m_pSource->GetValue();
   //learning rate comes from network
   m_dWeight += (*m_pdLearningRate) * dSourceValue * dError;
}
