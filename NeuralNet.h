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
#ifndef __NEURALNET_CLASS__
#define __NEURALNET_CLASS__

#include "Layer.h"
class CValueVector;
class CTrainingSet;

#define LEARNING_RATE 0.5
#define LEARNING_RATE_DELTA 0.5

/******************************************************************************
CNeuralNet is the top level class
it feautures 3 layers: input, hidden output of type CLayer
sizes of layers are set by Initialize(sizeInput, sizeHidden, sizeOutput)
FeedForward takes a vector of doubles for the input values
CopyOutput copies the result into a vector of doubles
BackProp takes a vector of doubles with the intended output and
  uses the backpropagation algorithm to adapt the weights
******************************************************************************/
class CNeuralNet
{
public:
   CNeuralNet(void);
   ~CNeuralNet(void);
protected:
   CLayer m_cInputLayer;
   CLayer m_cHiddenLayer;
   CLayer m_cOutputLayer;
   double m_dTotalError;
   double m_dLearningRate;
public:
   void Initialize(int nInputNodes, int nHiddenNodes, int nOutputNodes);
   void FeedForward(CValueVector *pvInputs);
   void BackProp(CValueVector *pvOutputs);
   double Rand0to1(void);
   double Train(CTrainingSet * pExamples);
   void Test(CTrainingSet * pExamples);
   void CopyOutputs(CValueVector * pOutputs);
};
#endif //__NEURALNET_CLASS__
