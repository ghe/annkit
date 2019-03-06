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

/******************************************************************************
 main.cpp: a very simple implementation of the identity function
 varying the hidden nodes in the network or the number of training cycles
 will cause different performance
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "TrainingSet.h"
#include "NeuralNet.h"

int main(int argc, char *argv[])
{
    int i,j,bit, input, output;
    int cycles    = 1000;
    int hidden    =   10;

    double error;

    CNeuralNet net;
    CTrainingSet set;
    CExample *example;

    //take the number of training cycles and hidden nodes
    //from the command line
    if (argc > 1)
    {
        cycles = atoi(argv[1]);
        if (argc > 2)
        {
            hidden = atoi(argv[2]);
        }
    }

    net.Initialize(8,hidden,8);

    //create a trainingset with 192 numbers
    for (i=0;i<192;i++)
    {
        example = new CExample(8,8);
        input = rand() % 256;
        printf("adding %d\n", input);
        for (j=0;j<8;j++)
        {
            bit = input & (1<<j) ? 1 : 0;
            example->SetInputValue(j, bit);
            example->SetOutputValue(j, bit);
        }
        set.push_back(example);
    }

    //train the network
    for (i=0;i<cycles;i++)
    {
        error = net.Train(&set);
        printf("%6d] training error: %f\r", i, error);
    }

    example = new CExample(8,8);
    input = 0;
    //test the output
    while (input >= 0)
    {
        printf("\nenter a number: ");
        scanf("%d",&input);
        for (j=0;j<8;j++)
        {
            bit = input & (1<<j) ? 1 : 0;
            example->SetInputValue(j, bit);
        }
        net.FeedForward(example->GetInputs());
        net.CopyOutputs(example->GetOutputs());
        output = 0;
        for (j=0;j<8;j++)
        {
            bit = (example->GetOutputValue(j) > 0.5 ? 1 : 0) << j;
            output |= bit;
        }
        printf("output: %d\n", output);
    }

    //clean up
    delete example;
    for (i=0;i<192;i++)
    {
        example = set.front();
        set.pop_front();
        delete example;
    }
}
