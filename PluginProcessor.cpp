#include "PluginProcessor.h"
#include "PluginEditor.h"

FuzzChorusAudioProcessor::FuzzChorusAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

FuzzChorusAudioProcessor::~FuzzChorusAudioProcessor() {}

void FuzzChorusAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Настройка DSP модулей
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(getTotalNumOutputChannels());

    // Подготовка хоруса
    chorus.prepare(spec);
    chorus.setRate(parameters.chorusRate);
    chorus.setDepth(parameters.chorusDepth);
    chorus.setMix(parameters.chorusMix);
    chorus.setCentreDelay(20.0f);
    chorus.setFeedback(0.0f);
}

void FuzzChorusAudioProcessor::releaseResources() {}

void FuzzChorusAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Очистка неиспользуемых каналов
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Обработка фузза
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            const float input = channelData[sample];

            // Применяем фузз-эффект
            const float distorted = std::tanh(input * parameters.fuzzGain);

            // Смешиваем чистый и искаженный сигнал
            channelData[sample] = (input * (1.0f - parameters.fuzzMix)) +
                (distorted * parameters.fuzzMix);
        }
    }

    // Обработка хоруса
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    chorus.process(context);
}

juce::AudioProcessorEditor* FuzzChorusAudioProcessor::createEditor()
{
    return new FuzzChorusAudioProcessorEditor(*this);
}

void FuzzChorusAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Простая реализация сохранения параметров
    juce::MemoryOutputStream stream(destData, true);
    stream.writeFloat(parameters.fuzzGain);
    stream.writeFloat(parameters.fuzzMix);
    stream.writeFloat(parameters.chorusRate);
    stream.writeFloat(parameters.chorusDepth);
    stream.writeFloat(parameters.chorusMix);
}

void FuzzChorusAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // Загрузка параметров
    juce::MemoryInputStream stream(data, sizeInBytes, false);
    parameters.fuzzGain = stream.readFloat();
    parameters.fuzzMix = stream.readFloat();
    parameters.chorusRate = stream.readFloat();
    parameters.chorusDepth = stream.readFloat();
    parameters.chorusMix = stream.readFloat();
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FuzzChorusAudioProcessor();
}