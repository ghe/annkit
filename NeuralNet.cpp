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
#include "NeuralNet.h"
#include "Synapse.h"
#include "ValueVector.h"
#include "TrainingSet.h"
#include "Example.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CNeuralNet::CNeuralNet(void)
{
   srand(time(0));
   m_dTotalError = 0;
   m_dLearningRate = LEARNING_RATE;
}

CNeuralNet::~CNeuralNet(void)
{
   CLayer::iterator it;

   for (it = m_cOutputLayer.begin(); it != m_cOutputLayer.end(); it++)
   {
      delete (CNeuron *)(*it);
   }
   m_cOutputLayer.clear();

   for (it = m_cHiddenLayer.begin(); it != m_cHiddenLayer.end(); it++)
   {
      delete (CNeuron *)(*it);
   }
   m_cHiddenLayer.clear();

   for (it = m_cInputLayer.begin(); it != m_cInputLayer.end(); it++)
   {
      delete (CNeuron *)(*it);
   }
   m_cHiddenLayer.clear();
}

void CNeuralNet::Initialize(int nInputNodes, int nHiddenNodes, int nOutputNodes)
{
   int i = 0;
   CLayer::iterator iLeft;
   CLayer::iterator iRight;
   CSynapse *pSynapse = NULL;
//   CSynapse *pBias = NULL;

   for (i = 0; i < nInputNodes; i++)
   {
      m_cInputLayer.push_back(new CNeuron);
   }

   for (i = 0; i < nHiddenNodes; i++)
   {
      m_cHiddenLayer.push_back(new CNeuron);
   }

   for (i = 0; i < nOutputNodes; i++)
   {
      m_cOutputLayer.push_back(new CNeuron);
   }

   //synapses
   for (iRight = m_cHiddenLayer.begin(); iRight != m_cHiddenLayer.end(); iRight++)
   {
      for (iLeft = m_cInputLayer.begin(); iLeft != m_cInputLayer.end(); iLeft++)
      {
         pSynapse = new CSynapse();
         pSynapse->SetWeight(Rand0to1());
         pSynapse->SetSource((CNeuron *)(*iLeft));
         pSynapse->m_pdLearningRate = &m_dLearningRate;
         ((CNeuron *)(*iRight))->AddInput(pSynapse);
      }
   }

   for (iRight = m_cOutputLayer.begin(); iRight != m_cOutputLayer.end(); iRight++)
   {
      for (iLeft = m_cHiddenLayer.begin(); iLeft != m_cHiddenLayer.end(); iLeft++)
      {
         pSynapse = new CSynapse();
         pSynapse->SetWeight(Rand0to1());
         pSynapse->SetSource((CNeuron *)(*iLeft));
         pSynapse->m_pdLearningRate = &m_dLearningRate;
         ((CNeuron *)(*iRight))->AddInput(pSynapse);
      }
   }
}

void CNeuralNet::FeedForward(CValueVector *pvInputs)
{
   CLayer::iterator it;

   if (pvInputs->size() != m_cInputLayer.size())
   {
      printf("invalid example input size\n");
      return;
   }

   for (unsigned i = 0; i < m_cInputLayer.size(); i++)
   {
      (m_cInputLayer[i])->m_dValue = (*pvInputs)[i];
   }

   for (it = m_cHiddenLayer.begin(); it != m_cHiddenLayer.end(); it++)
   {
      ((CNeuron *)(*it))->Calculate();
   }

   for (it = m_cOutputLayer.begin(); it != m_cOutputLayer.end(); it++)
   {
      ((CNeuron *)(*it))->Calculate();
   }
}

void CNeuralNet::BackProp(CValueVector *pvOutputs)
{
   double dExpectedOutput = 0;
   double dActualOutput = 0;
   double dError = 0;
   double dThisPassError = 0;
   CNeuron *pNeuron = NULL;
   CLayer::iterator it;

   //test for equal sizes
   if (pvOutputs->size() != m_cOutputLayer.size())
   {
      printf("invalid example output size\n");
      return;
   }

   //set the errors for the output layer
   for (unsigned i = 0; i < m_cOutputLayer.size(); i++)
   {
      pNeuron = m_cOutputLayer[i];
      dActualOutput = pNeuron->m_dValue;
      dExpectedOutput = (*pvOutputs)[i];
      dError = dExpectedOutput - dActualOutput;
      pNeuron->AddToRawError(dError);
      //add the absolute value to a total error
      dThisPassError += (dError > 0 ? dError : dError * -1.0);
   }
   //divide by number of outputs
   m_dTotalError += (dThisPassError / (double)m_cOutputLayer.size());

   for (it = m_cOutputLayer.begin(); it != m_cOutputLayer.end(); it++)
   {
      ((CNeuron *)(*it))->CalcError();
   }

   for (it = m_cHiddenLayer.begin(); it != m_cHiddenLayer.end(); it++)
   {
      ((CNeuron *)(*it))->CalcError();
   }


}

double CNeuralNet::Rand0to1(void)
{
   return (double(rand() % 1000) / 1000.0);
}

double CNeuralNet::Train(CTrainingSet * pExamples)
{
   CTrainingSet::iterator it;
   CExample *pExample = NULL;
   double dTrainingError = 0;

   m_dTotalError = 0;

   for (it = pExamples->begin(); it != pExamples->end(); it++)
   {
      pExample = (CExample *)(*it);
      FeedForward(pExample->GetInputs());
      BackProp(pExample->GetOutputs());
   }
   dTrainingError = m_dTotalError / (double)pExamples->size();
   m_dLearningRate = LEARNING_RATE_DELTA * dTrainingError;
   return dTrainingError;
}

void CNeuralNet::Test(CTrainingSet * pExamples)
{
   CTrainingSet::iterator it;
   CExample *pExample = NULL;

   for (it = pExamples->begin(); it != pExamples->end(); it++)
   {
      pExample = (CExample *)(*it);
      FeedForward(pExample->GetInputs());
      CopyOutputs(pExample->GetOutputs());
   }
}

void CNeuralNet::CopyOutputs(CValueVector * pOutputs)
{
   CNeuron *pNeuron = NULL;

   for (unsigned i = 0; i < m_cOutputLayer.size(); i++)
   {
      pNeuron = m_cOutputLayer[i];
      (*pOutputs)[i] = pNeuron->m_dValue;
   }
}
