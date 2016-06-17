#include "Classifier.h"
#include <math.h>
#include <iostream>


Classifier::Classifier(void)
    : trainA(100)
    , trainB(100)
{
}

Classifier::~Classifier(void)
{
}

void Classifier::getAmplitudeSpectrum(const float* data, size_t windowSize, std::vector<float>& output) {
    TSpectrum::TParams params(windowSize);
    params.Window = windowSize;
    params.FreqCount = params.Window / 2;
    TSpectrum spectrum(params);
    std::vector<float> input(windowSize, 0.0);
    for (int i = 0; i < windowSize; ++i) {
        input[i] = data[i];
    }
    spectrum.AmplitudeSpectrum(input, output);
}

float Classifier::Classify(const float* data, size_t windowSize, size_t sampleRate)
{
    size_t windowSizeRoundedToPower2 = RoundWindowSizeToPower2(windowSize);
    
    std::vector<float> output(windowSizeRoundedToPower2/2, 0.0);
    getAmplitudeSpectrum(data, windowSizeRoundedToPower2, output);

    std::vector<float> features;
    getFeatures(output, windowSizeRoundedToPower2, sampleRate, features);

    // call classifier
    bool isB = DummyClassifyInternal(features);
    return isB ? 1 : 0;
    //return 0.7;
}

void Classifier::Train(const float* data, size_t windowSize, size_t sampleRate, bool label) {
    if (windowSize > 0) {
        size_t windowSizeRoundedToPower2 = RoundWindowSizeToPower2(windowSize);

        std::vector<float> output(windowSizeRoundedToPower2/2, 0.0);
        getAmplitudeSpectrum(data, windowSizeRoundedToPower2, output);

        std::vector<float> features;
        getFeatures(output, windowSizeRoundedToPower2, sampleRate, features);

        if (label) {
            // trainB
            trainB.push_back(features);
        } else {
            // trainA
            trainA.push_back(features);
        }
    }
}

void Classifier::getFeatures(std::vector<float>& spectrum, size_t windowSize, size_t sampleRate, std::vector<float>& output) {
    output.push_back(SpectralCentroid(spectrum, sampleRate));
    output.push_back(SpectralCrest(spectrum));
    output.push_back(SpectralFlatness(spectrum));
    output.push_back(SpectralRolloff(spectrum, sampleRate));
}

float Classifier::SpectralCentroid(std::vector<float>& data, size_t sampleRate) {
    float sum_fx = 0;
    float sum_x = 0;
    for (int i = 0; i < data.size(); ++i) {
        float x = data[i] * data[i];
        sum_fx += (i * x);
        sum_x += x;
    }
    // convert index to Hz
    return sum_fx / sum_x * (sampleRate / (2 * data.size()));
}

float Classifier::SpectralCrest(std::vector<float>& data) {
    float max = -1;
    float sum = 0;
    for (int i = 0; i < data.size(); i++) {
        float x = data[i] * data[i];
        sum += x;
        if (x > max) {
            max = x;
        }
    }
    return max / sum;
}

float Classifier::SpectralFlatness(std::vector<float>& data) {
    float sumlog = 0;
    float sum = 0;
    for (int i = 0; i < data.size(); i++) {
        float x = abs(data[i]);
        if (x < 1e-8) {
            x = 1e-8;
        }
        sumlog += log(x);
        sum += x;
    }
    sumlog = exp(sumlog / data.size());
    sum /= data.size();
    return sumlog / sum;
}

float Classifier::SpectralFlux(std::vector<float>& data, std::vector<float>& previousData) {
    if (data.size() != previousData.size()) {
        return 0;
    }
    float res = 0;
    for (int i = 0; i < data.size(); i++) {
        float x = data[i] - previousData[i];
        res += (x * x);
    }
    return sqrt(res);
}

float Classifier::SpectralRolloff(std::vector<float>& data, size_t sampleRate) {
    float param = 0.8;
    float sum = 0;
    float accum = 0;
    int index = 0;
    for (int i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    while (accum < param * sum && index < data.size()) {
        accum += data[index++];
    }
    // convert from index to Hz
    return index * (sampleRate / (2 * data.size()));
}

bool Classifier::DummyClassifyInternal(std::vector<float>& features) {
    float minDistance = 10000000.0f;
    bool isB = false;
    for (int i = 0; i < trainA.size(); ++i) {
        float d = EuclideanDistance(features, trainA[i]);
        if (d < minDistance) {
            isB = false;
        }
    }
    for (int i = 0; i < trainB.size(); ++i) {
        float d = EuclideanDistance(features, trainB[i]);
        if (d < minDistance) {
            isB = true;
        }
    }
    return isB;
}