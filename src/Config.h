#pragma once

#include "JuceHeader.h"
#include <string>
#include <vector>

struct ParameterBucketConfig {
    juce::String paramName;
    juce::String strategy; // "Linear", "ExplicitValues", "Log", "EdgeAndCenter"
    float min = 0.0f;
    float max = 1.0f;
    int numBuckets = 0;
    std::vector<float> values;
};

struct Config {
    juce::String pluginPath;
    double sampleRate = 48000.0;
    double seconds = 5.0;
    double preRollSeconds = 0.1; // silence rendered after reset() and before each run, not measured

    // MIDI note: "auto" sends it to plugins with no audio inputs that accept MIDI (instruments), "on" to any
    // plugin, "off" never. Held from noteSettleSeconds before the measurement until a note-off after it.
    juce::String midiMode = "auto";
    int midiNote = 60;
    int midiVelocity = 100;
    int midiChannel = 1;
    double noteSettleSeconds = 0.0;
    int blockSize = 256;
    juce::String signalType; // "sine", "noise", "sweep"
    double sineFrequency = 1000.0;
    double sweepStartHz = 20.0;
    double sweepEndHz = 20000.0;
    std::vector<float> inputGainBucketsDb;
    std::vector<ParameterBucketConfig> parameterBuckets;
    std::vector<juce::String> analyzers;

    // Throws std::runtime_error if the audio or MIDI settings are unusable
    void validate() const;

    static Config fromJson(const juce::File& jsonFile);
    static Config fromJsonString(const juce::String& jsonString);
};
