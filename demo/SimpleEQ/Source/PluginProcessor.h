/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SimpleEQAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleEQAudioProcessor();
    ~SimpleEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    static juce::AudioProcessorValueTreeState::ParameterLayout
    createParameterLayout()
    {
        // do something
        juce::AudioProcessorValueTreeState::ParameterLayout layout;
        layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                               "LowCut Freq",
                                                               "LowCut Freq",
                                                               juce::NormalisableRange<float>(20.f, 20000.f, 1.f,1.f),
                                                               20.f));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                               "HighCut Freq",
                                                               "HighCut Freq",
                                                               juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
                                                               20000.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                               "Peak Freq",
                                                               "Peak Freq",
                                                               juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
                                                               750.f));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                               "Peak Gain",
                                                               "Peak Gain",
                                                               juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f),
                                                               0.0f));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(
                                                               "Peak Quality",
                                                               "Peak Quality",
                                                               juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f),
                                                               1.f));
        juce::StringArray stringArray;
        for(int i = 0; i < 4; i++)
        {
            juce::String str;
            str << (12 + i*12);
            str << "dB/Oct";
            stringArray.add(str);
        }

        layout.add(std::make_unique<juce::AudioParameterChoice>("LowCut Slope", "LowCut Slope",stringArray, 0));
        layout.add(std::make_unique<juce::AudioParameterChoice>("HighCut Slope", "HighCut Slope",stringArray, 0));

        return layout;
    };
    juce::AudioProcessorValueTreeState apvts {*this, nullptr, "Parameters", createParameterLayout()};

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessor)
};
