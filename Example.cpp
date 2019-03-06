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
#include "Example.h"

CExample::CExample(void)
{
   m_pvdInputs = new CValueVector;
   m_pvdOutputs = new CValueVector;
}

CExample::CExample(unsigned nInputs, unsigned nOutputs)
{
   m_pvdInputs = new CValueVector(nInputs);
   m_pvdOutputs = new CValueVector(nOutputs);
}

CExample::~CExample(void)
{
   delete m_pvdInputs;
   delete m_pvdOutputs;
}

CExample::CExample(CExample& cexRHS)
{
   *this = cexRHS;
}

//Deep copy
CExample &CExample::operator=(CExample& cexRHS)
{
   unsigned i = 0;
   //inputs
   for (i = 0; i < m_pvdInputs->size(); i++)
   {
      (*m_pvdInputs)[i] = (*cexRHS.GetInputs())[i];
   }
   //outputs
   for (i = 0; i < m_pvdOutputs->size(); i++)
   {
      (*m_pvdOutputs)[i] = (*cexRHS.GetOutputs())[i];
   }

   return (*this);
}


//accessors
void CExample::SetInputValue(unsigned i, double dValue)
{
   (*m_pvdInputs)[i] = dValue;
}

double CExample::GetInputValue(unsigned i)
{
   return (*m_pvdInputs)[i];
}

void CExample::SetOutputValue(unsigned i, double dValue)
{
   (*m_pvdOutputs)[i] = dValue;
}

double CExample::GetOutputValue(unsigned i)
{
   return (*m_pvdOutputs)[i];
}

CValueVector * CExample::GetInputs(void)
{
   return m_pvdInputs;
}

CValueVector * CExample::GetOutputs(void)
{
   return m_pvdOutputs;
}

void CExample::SetOutputs(CValueVector *pvdOutputs)
{
   m_pvdOutputs = pvdOutputs;
}

void CExample::SetInputs(CValueVector *pvdInputs)
{
   m_pvdInputs = pvdInputs;
}
