#pragma once
float* Add_Data(float* sample, int Size, float* x, int Dim);
float* Add_Labels(float* Labels, int Size, int label);
float* init_array_random(int len);

void Z_Score_Parameters(float* x, int Size, int dim, float* mean, float* std);
int  Test_Forward(float* x, float* weight, float* bias, int neuron_count, int inputDim);

// Tek katmanlı perceptron eğitimi
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
);
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
);


// ---- Çok katmanlı ağ (1 gizli katman) için fonksiyonlar ----

// type: 0 = tanh, 1 = sigmoid, 2 = linear
float activation(float u, int type);
float activation_deriv(float y, int type);

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
);

int Test_Forward_MLP(
    float* x,
    int    inputDim,
    int    hiddenDim,
    float* W1,
    float* b1,
    float* W2,
    float* b2,
    int    actType
);