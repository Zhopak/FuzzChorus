#pragma once

#include <JuceHeader.h>

class FuzzChorusAudioProcessor : public juce::AudioProcessor
{
public:
    FuzzChorusAudioProcessor();
    ~FuzzChorusAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "FuzzChorus"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Параметры эффектов
    struct Parameters {
        float fuzzGain = 5.0f;     // 1-20
        float fuzzMix = 1.0f;       // 0-1
        float chorusRate = 1.0f;    // 0.1-5 Гц
        float chorusDepth = 0.5f;   // 0-1
        float chorusMix = 0.5f;     // 0-1
    } parameters;

    // Объекты для обработки звука
    juce::dsp::Chorus<float> chorus;

    static juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FuzzChorusAudioProcessor)
};
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();