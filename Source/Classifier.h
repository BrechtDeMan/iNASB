#pragma once

#include "fft.h"

class Classifier
{
public:
    Classifier(void);
    ~Classifier(void);

    float Classify(const float* data, size_t size, size_t sampleRate);
    void Train(const float* data, size_t size, size_t sampleRate, bool label);

private:
    std::vector< std::vector<float> > trainA;
    std::vector< std::vector<float> > trainB;

private:
    inline size_t RoundWindowSizeToPower2(size_t windowSize) {
        return pow(2, ceil(log(windowSize) * 1.0/log(2)));
    }
    void getAmplitudeSpectrum(const float* data, size_t windowSize, std::vector<float>& output);
    void getFeatures(std::vector<float>& spectrum, size_t windowSize, size_t sampleRate, std::vector<float>& output);
    bool DummyClassifyInternal(std::vector<float>& features);

    inline float EuclideanDistance(std::vector<float>& vec1, std::vector<float>& vec2) {
        if (vec1.size() != vec2.size()) {
            return 10000000; // TODO: throw exception
        }
        float sum = 0;
        for (int i = 0; i < vec1.size(); ++i) {
            float x = vec1[i] - vec2[i];
            sum += (x * x);
        }
        return sqrt(sum);
    }

    float SpectralCentroid(std::vector<float>& data, size_t sampleRate);
    float SpectralCrest(std::vector<float>& data);
    float SpectralFlatness(std::vector<float>& data);
    float SpectralFlux(std::vector<float>& data, std::vector<float>& previousData);
    float SpectralRolloff(std::vector<float>& data, size_t sampleRate);
};
