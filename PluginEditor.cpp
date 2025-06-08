#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>

FuzzChorusAudioProcessorEditor::FuzzChorusAudioProcessorEditor(FuzzChorusAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Настройка размеров окна
    setSize(500, 300);

    // Настройка заголовка
    titleLabel.setText("Fuzz + Chorus Guitar Effect", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    // Настройка слайдеров и меток для фузза
    fuzzGainSlider.setRange(1.0, 20.0, 0.1);
    fuzzGainSlider.setValue(audioProcessor.parameters.fuzzGain);
    fuzzGainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    fuzzGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    fuzzGainSlider.addListener(this);
    addAndMakeVisible(fuzzGainSlider);

    fuzzGainLabel.setText("Fuzz Gain", juce::dontSendNotification);
    fuzzGainLabel.setJustificationType(juce::Justification::centred);
    fuzzGainLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(fuzzGainLabel);

    fuzzMixSlider.setRange(0.0, 1.0, 0.01);
    fuzzMixSlider.setValue(audioProcessor.parameters.fuzzMix);
    fuzzMixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    fuzzMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    fuzzMixSlider.addListener(this);
    addAndMakeVisible(fuzzMixSlider);

    fuzzMixLabel.setText("Fuzz Mix", juce::dontSendNotification);
    fuzzMixLabel.setJustificationType(juce::Justification::centred);
    fuzzMixLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(fuzzMixLabel);

    // Настройка слайдеров и меток для хоруса
    chorusRateSlider.setRange(0.1, 5.0, 0.01);
    chorusRateSlider.setValue(audioProcessor.parameters.chorusRate);
    chorusRateSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    chorusRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    chorusRateSlider.addListener(this);
    addAndMakeVisible(chorusRateSlider);

    chorusRateLabel.setText("Chorus Rate", juce::dontSendNotification);
    chorusRateLabel.setJustificationType(juce::Justification::centred);
    chorusRateLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(chorusRateLabel);

    chorusDepthSlider.setRange(0.0, 1.0, 0.01);
    chorusDepthSlider.setValue(audioProcessor.parameters.chorusDepth);
    chorusDepthSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    chorusDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    chorusDepthSlider.addListener(this);
    addAndMakeVisible(chorusDepthSlider);

    chorusDepthLabel.setText("Chorus Depth", juce::dontSendNotification);
    chorusDepthLabel.setJustificationType(juce::Justification::centred);
    chorusDepthLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(chorusDepthLabel);

    chorusMixSlider.setRange(0.0, 1.0, 0.01);
    chorusMixSlider.setValue(audioProcessor.parameters.chorusMix);
    chorusMixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    chorusMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    chorusMixSlider.addListener(this);
    addAndMakeVisible(chorusMixSlider);

    chorusMixLabel.setText("Chorus Mix", juce::dontSendNotification);
    chorusMixLabel.setJustificationType(juce::Justification::centred);
    chorusMixLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(chorusMixLabel);
}

FuzzChorusAudioProcessorEditor::~FuzzChorusAudioProcessorEditor()
{
    // Удаляем слушателей перед разрушением
    fuzzGainSlider.removeListener(this);
    fuzzMixSlider.removeListener(this);
    chorusRateSlider.removeListener(this);
    chorusDepthSlider.removeListener(this);
    chorusMixSlider.removeListener(this);
}

void FuzzChorusAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Отрисовка фона
    g.fillAll(juce::Colours::darkgrey);
}

void FuzzChorusAudioProcessorEditor::resized()
{
    const int padding = 15;
    const int sliderWidth = 80;
    const int sliderHeight = 100;
    const int rowHeight = 120;

    // Расположение элементов
    titleLabel.setBounds(padding, padding, getWidth() - 2 * padding, 30);

    // Первый ряд: фузз
    fuzzGainLabel.setBounds(padding, 50, sliderWidth, 20);
    fuzzGainSlider.setBounds(padding, 70, sliderWidth, sliderHeight);

    fuzzMixLabel.setBounds(padding + sliderWidth + padding, 50, sliderWidth, 20);
    fuzzMixSlider.setBounds(padding + sliderWidth + padding, 70, sliderWidth, sliderHeight);

    // Второй ряд: хорус
    chorusRateLabel.setBounds(padding, 70 + rowHeight, sliderWidth, 20);
    chorusRateSlider.setBounds(padding, 90 + rowHeight, sliderWidth, sliderHeight);

    chorusDepthLabel.setBounds(padding + sliderWidth + padding, 70 + rowHeight, sliderWidth, 20);
    chorusDepthSlider.setBounds(padding + sliderWidth + padding, 90 + rowHeight, sliderWidth, sliderHeight);

    chorusMixLabel.setBounds(padding + 2 * (sliderWidth + padding), 70 + rowHeight, sliderWidth, 20);
    chorusMixSlider.setBounds(padding + 2 * (sliderWidth + padding), 90 + rowHeight, sliderWidth, sliderHeight);
}

void FuzzChorusAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // Обновляем параметры процессора при изменении слайдеров
    if (slider == &fuzzGainSlider) {
        audioProcessor.parameters.fuzzGain = static_cast<float>(fuzzGainSlider.getValue());
    }
    else if (slider == &fuzzMixSlider) {
        audioProcessor.parameters.fuzzMix = static_cast<float>(fuzzMixSlider.getValue());
    }
    else if (slider == &chorusRateSlider) {
        audioProcessor.parameters.chorusRate = static_cast<float>(chorusRateSlider.getValue());
        audioProcessor.chorus.setRate(audioProcessor.parameters.chorusRate);
    }
    else if (slider == &chorusDepthSlider) {
        audioProcessor.parameters.chorusDepth = static_cast<float>(chorusDepthSlider.getValue());
        audioProcessor.chorus.setDepth(audioProcessor.parameters.chorusDepth);
    }
    else if (slider == &chorusMixSlider) {
        audioProcessor.parameters.chorusMix = static_cast<float>(chorusMixSlider.getValue());
        audioProcessor.chorus.setMix(audioProcessor.parameters.chorusMix);
    }
}