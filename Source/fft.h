#pragma once
#include <vector>
#include <math.h>


class FFT {
public:
    FFT();
    ~FFT();
    void Init(int samples_in, int samples_out, int bEqualize=1, float envelope_power=1.0f);
    void time_to_frequency_domain(float* in_wavedata, float* out_spectraldata);
    int  GetNumFreq() { return NFREQ; };
    int  GetNumSamples() { return m_samples_in; };
    void CleanUp();
private:
    int m_ready;
    int m_samples_in;
    int NFREQ;

    void InitEnvelopeTable(float power);
    void InitEqualizeTable();
    void InitBitRevTable();
    void InitCosSinTable();

    int   *bitrevtable;
    float *envelope;
    float *equalize;
    float *temp1;
    float *temp2;
    float (*cossintable)[2];
};

class TSpectrum {
public:
    struct TParams {
        TParams(size_t windowSize)
            : Window(windowSize)
            , FreqCount(windowSize / 2)
        {
        }

        size_t Window;
        size_t FreqCount;
    };

public:
    TSpectrum(TParams&);

    virtual ~TSpectrum();

    void AmplitudeSpectrum(std::vector<float>& origSignal, std::vector<float>& freq);

private:
    size_t Window;
    size_t FreqCount;
    //size_t Shift;
    FFT FFTrans;

    void Init(std::vector<float>& freq, size_t size);
};
