#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class FuzzChorusAudioProcessorEditor : public juce::AudioProcessorEditor,
    private juce::Slider::Listener
{
public:
    explicit FuzzChorusAudioProcessorEditor(FuzzChorusAudioProcessor&);
    ~FuzzChorusAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    FuzzChorusAudioProcessor& audioProcessor;

    // Слайдеры
    juce::Slider fuzzGainSlider;
    juce::Slider fuzzMixSlider;
    juce::Slider chorusRateSlider;
    juce::Slider chorusDepthSlider;
    juce::Slider chorusMixSlider;

    // Метки
    juce::Label fuzzGainLabel;
    juce::Label fuzzMixLabel;
    juce::Label chorusRateLabel;
    juce::Label chorusDepthLabel;
    juce::Label chorusMixLabel;
    juce::Label titleLabel;

    // Обработчик изменения слайдеров
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FuzzChorusAudioProcessorEditor)
};