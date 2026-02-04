#pragma once

// Basit: 1 gizli katmanlı MLP, ikili sınıflandırma için (çıktı 0 veya 1).
// Bu dosya mevcut perceptron kodunu etkilemez; bağımsız kullanılır.

// type: 0 = tanh, 1 = sigmoid, 2 = linear
float MLP_Activation(float u, int type);
float MLP_ActivationDeriv(float y, int type);

// Eğitim: 
//  - Samples:  Size x inputDim
//  - Labels:   Size (0 veya 1)
//  - W1:       hiddenDim x inputDim
//  - b1:       hiddenDim
//  - W2:       hiddenDim (tek çıktı nöronu)
//  - b2:       1
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
    float* epochError,   // [maxEpoch] hata eğrisi için (opsiyonel, null olabilir)
    int    actType       // aktivasyon tipi
);

// Test: tek örnek için ileri yayılım, 0 veya 1 döner.
int Test_MLP_Network(
    float* x,
    int    inputDim,
    int    hiddenDim,
    float* W1,
    float* b1,
    float* W2,
    float* b2,
    int    actType
);


