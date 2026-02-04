#include "pch.h"
#include <cmath>
#include "MLPProcess.h"

// -------------------------------------------------
// MLP ACTIVATION FUNCTIONS (BAĞIMSIZ)
// -------------------------------------------------

float MLP_Activation(float u, int type)
{
    // 0: TANH, 1: SIGMOID, 2: LINEAR
    if (type == 0)
        return tanhf(u);
    else if (type == 1)
        return 1.0f / (1.0f + expf(-u));
    else
        return u;
}

float MLP_ActivationDeriv(float y, int type)
{
    // y = activation(u)
    if (type == 0)
        return 1.0f - y * y;      // tanh'
    else if (type == 1)
        return y * (1.0f - y);    // sigmoid'
    else
        return 1.0f;              // linear'
}

// -------------------------------------------------
// SINGLE HIDDEN LAYER MLP TRAINING (BAĞIMSIZ)
// -------------------------------------------------

void Train_MLP_Network(
    float* Samples,
    float* Labels,
    int    Size,
    int    inputDim,
    int    hiddenDim,
    float* W1,
    float* b1,
    float* W2,
    float* b2,
    float  learningRate,
    int    maxEpoch,
    float* epochError,
    int    actType
)
{
    float* hiddenNet = new float[hiddenDim];
    float* hiddenOut = new float[hiddenDim];
    float* delta1    = new float[hiddenDim];

    for (int epoch = 0; epoch < maxEpoch; ++epoch) {
        float totalError = 0.0f;

        for (int i = 0; i < Size; ++i) {

            float* x = &Samples[i * inputDim];
            float   t = Labels[i]; // 0 veya 1

            // ---- FORWARD ----
            for (int h = 0; h < hiddenDim; ++h) {
                float net = b1[h];
                for (int j = 0; j < inputDim; ++j)
                    net += W1[h * inputDim + j] * x[j];
                hiddenNet[h] = net;
                hiddenOut[h] = MLP_Activation(net, actType);
            }

            float net2 = b2[0];
            for (int h = 0; h < hiddenDim; ++h)
                net2 += W2[h] * hiddenOut[h];
            float y = MLP_Activation(net2, actType);

            float e = t - y;
            totalError += fabsf(e);

            // ---- BACKWARD ----
            float delta2 = e * MLP_ActivationDeriv(y, actType);

            for (int h = 0; h < hiddenDim; ++h) {
                delta1[h] = MLP_ActivationDeriv(hiddenOut[h], actType) * (W2[h] * delta2);
            }

            // ---- OUTPUT LAYER UPDATE ----
            for (int h = 0; h < hiddenDim; ++h)
                W2[h] += learningRate * delta2 * hiddenOut[h];
            b2[0] += learningRate * delta2;

            // ---- HIDDEN LAYER UPDATE ----
            for (int h = 0; h < hiddenDim; ++h) {
                for (int j = 0; j < inputDim; ++j)
                    W1[h * inputDim + j] += learningRate * delta1[h] * x[j];
                b1[h] += learningRate * delta1[h];
            }
        }

        if (epochError)
            epochError[epoch] = totalError / float(Size);
    }

    delete[] hiddenNet;
    delete[] hiddenOut;
    delete[] delta1;
}

// -------------------------------------------------
// MLP TEST (FORWARD) (BAĞIMSIZ)
// -------------------------------------------------

int Test_MLP_Network(
    float* x,
    int    inputDim,
    int    hiddenDim,
    float* W1,
    float* b1,
    float* W2,
    float* b2,
    int    actType
)
{
    float* hiddenOut = new float[hiddenDim];

    for (int h = 0; h < hiddenDim; ++h) {
        float net = b1[h];
        for (int j = 0; j < inputDim; ++j)
            net += W1[h * inputDim + j] * x[j];
        hiddenOut[h] = MLP_Activation(net, actType);
    }

    float net2 = b2[0];
    for (int h = 0; h < hiddenDim; ++h)
        net2 += W2[h] * hiddenOut[h];
    float y = MLP_Activation(net2, actType);

    delete[] hiddenOut;

    return (y >= 0.5f) ? 1 : 0;
}


