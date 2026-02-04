#include "pch.h"
#include <cmath>
#include <cstdlib>

// -------------------------------------------------
// DATA & LABEL HANDLING 
// -------------------------------------------------

float* Add_Data(float* sample, int Size, float* x, int Dim) {
    float* temp;
    temp = new float[Size * Dim];
    for (int i = 0; i < (Size - 1) * Dim; i++)
        temp[i] = sample[i];
    for (int i = 0; i < Dim; i++)
        temp[(Size - 1) * Dim + i] = x[i];
    delete[] sample;
    return temp;
}

float* Add_Labels(float* Labels, int Size, int label) {
    float* temp;
    temp = new float[Size];
    for (int i = 0; i < Size - 1; i++)
        temp[i] = Labels[i];
    temp[Size - 1] = float(label);
    delete[] Labels;
    return temp;
}

float* init_array_random(int len) {
    float* arr = new float[len];
    for (int i = 0; i < len; i++)
        arr[i] = ((float)rand() / RAND_MAX) - 0.5f;
    return arr;
}

// -------------------------------------------------
// Z-SCORE NORMALIZATION (ama kullanmad?k)
// -------------------------------------------------

void Z_Score_Parameters(float* x, int Size, int dim, float* mean, float* std) {

    float* Total = new float[dim];

    int i, j;
    for (i = 0; i < dim; i++) {
        mean[i] = std[i] = Total[i] = 0.0f;
    }

    for (i = 0; i < Size; i++)
        for (j = 0; j < dim; j++)
            Total[j] += x[i * dim + j];

    for (i = 0; i < dim; i++)
        mean[i] = Total[i] / float(Size);

    for (i = 0; i < Size; i++)
        for (j = 0; j < dim; j++)
            std[j] += (x[i * dim + j] - mean[j]) * (x[i * dim + j] - mean[j]);

    for (j = 0; j < dim; j++)
        std[j] = sqrt(std[j] / float(Size));

    delete[] Total;
}

// -------------------------------------------------
// TEST 
// -------------------------------------------------

int Test_Forward(float* x, float* weight, float* bias, int num_Class, int inputDim)
{
    // Tek katmanl?, ikili s?n?fland?rma
    float net = bias[0];

    for (int j = 0; j < inputDim; j++)
        net += weight[j] * x[j];

    // Step activation
    if (net >= 0.0f)
        return 1;   // class 1
    else
        return 0;   // class 0
}

// -------------------------------------------------
// SINGLE LAYER PERCEPTRON TRAINING
// -------------------------------------------------

void Train_Perceptron(
    float* Samples,
    float* Labels,
    int    Size,
    int    inputDim,
    float* Weights,
    float* Bias,
    float  learningRate,
    int    maxEpoch,
    float* epochError
)
{

    for (int epoch = 0; epoch < maxEpoch; epoch++) {

        float totalError = 0.0f;


        for (int i = 0; i < Size; i++) {

            float net = Bias[0];
            for (int j = 0; j < inputDim; j++)
                net += Weights[j] * Samples[i * inputDim + j];

            float y = (net >= 0.0f) ? 1.0f : 0.0f;
            float t = Labels[i];

            float e = t - y;
            totalError += fabs(e);

            for (int j = 0; j < inputDim; j++)
                Weights[j] += learningRate * e * Samples[i * inputDim + j];

            Bias[0] += learningRate * e;
        }
        if (epochError)
            epochError[epoch] = totalError / float(Size);
    }
}

void Train_LinearRegression(
    float* Samples,
    float* Targets,
    int    Size,
    int    inputDim,
    float* Weights,
    float* Bias,
    float  learningRate,
    int    maxEpoch,
    float* epochError
)
{
    for (int epoch = 0; epoch < maxEpoch; epoch++) {

        float mse = 0.0f;

        for (int i = 0; i < Size; i++) {

            // Lineer aktivasyon
            float y = Bias[0];
            for (int j = 0; j < inputDim; j++)
                y += Weights[j] * Samples[i * inputDim + j];

            float e = Targets[i] - y;
            mse += e * e;

            // Gradient descent
            for (int j = 0; j < inputDim; j++)
                Weights[j] += learningRate * e * Samples[i * inputDim + j];

            Bias[0] += learningRate * e;
        }

        if (epochError)
            epochError[epoch] = mse / Size;
    }
}


// -------------------------------------------------
// MLP ACTIVATION FUNCTIONS
// -------------------------------------------------

float activation(float u, int type)
{
    // 0: TANH, 1: SIGMOID, 2: LINEAR
    if (type == 0)
        return tanhf(u);
    else if (type == 1)
        return 1.0f / (1.0f + expf(-u));
    else
        return u;
}

float activation_deriv(float y, int type)//türevi
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
// SINGLE HIDDEN LAYER MLP TRAINING
// -------------------------------------------------

void Train_MLP(
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
                hiddenOut[h] = activation(net, actType);
            }

            float net2 = b2[0];
            for (int h = 0; h < hiddenDim; ++h)
                net2 += W2[h] * hiddenOut[h];
            float y = activation(net2, actType);

            float e = t - y;
            totalError += fabs(e);

            // ---- BACKWARD ----
            float delta2 = e * activation_deriv(y, actType);

            for (int h = 0; h < hiddenDim; ++h) {
                delta1[h] = activation_deriv(hiddenOut[h], actType) * (W2[h] * delta2);
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
// MLP TEST (FORWARD)
// -------------------------------------------------

int Test_Forward_MLP(
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
        hiddenOut[h] = activation(net, actType);
    }

    float net2 = b2[0];
    for (int h = 0; h < hiddenDim; ++h)
        net2 += W2[h] * hiddenOut[h];
    float y = activation(net2, actType);

    delete[] hiddenOut;

    return (y >= 0.5f) ? 1 : 0;
}

