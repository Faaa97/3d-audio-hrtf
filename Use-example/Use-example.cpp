// Use-example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "3d-audio.h"
#include <fstream>

#include <wrl/client.h> // ComPtr
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>
#include <xapo.h>
#include <xapobase.h>

#include <chrono>   //Timer
#include <thread>   //Timer

void loop(IXAPOParameters* pXAPO) {
    spherical_coordinates sound = { 1.4, 0, 1.75 };     // Sound source

    while (true) {

        sound.azimuth = sound.azimuth + 5;

        if (abs(sound.azimuth) == 180) {
            sound.azimuth = -sound.azimuth;
        }
        std::cout << "changing to azimuth: " << sound.azimuth << " elevation: " << sound.elevation << " radius: " << sound.radius << std::endl;

        a3d::setPosition(pXAPO, sound);

        system("pause");
    }
}

void loop2(IXAPOParameters* pXAPO, unsigned time) {

    spherical_coordinates sound = { 1.4, 0, -40 };     // Sound source

    bool forward = true;

    while (true) {

        sound.azimuth = sound.azimuth + 5;

        if (abs(sound.azimuth) >= 180) {
            sound.azimuth = -sound.azimuth;
        }
        else if (sound.azimuth == 0) {
            forward ? sound.elevation += 10 : sound.elevation -= 10;
            if (abs(sound.elevation) >= 40) {
                forward = !forward;
            }
        }
        std::cout << "changing to azimuth: " << sound.azimuth << " elevation: " << sound.elevation << " radius: " << sound.radius << std::endl;

        a3d::setPosition(pXAPO, sound);

        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
}

int main() {

    HRESULT hr;

    // Required for xAudio2
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cout << "CoInitializeEx() failed" << std::endl;
        assert(0);
        return false;
    }

    // Create a instance of xAudio2 Engine
    Microsoft::WRL::ComPtr<IXAudio2> pXAudio2 = NULL;
    hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr)) {
        std::cout << "XAudio2Create() failed" << std::endl;
        assert(0);
        return false;
    }

    // Create a mastering voice
    IXAudio2MasteringVoice* pMasterVoice = NULL;
    hr = pXAudio2->CreateMasteringVoice(&pMasterVoice, 2);
    if (FAILED(hr)) {
        std::cout << "CreateMasteringVoice() failed" << std::endl;
        assert(0);
        return false;
    }

    std::cout << "Loading filters..." << std::endl;

    // Load filters for xAPO class
    filter_data* filters = (filter_data*)malloc(355 * sizeof(filter_data));
    size_t* filters_size = new size_t();

    hr = a3d::utils::loadFilters(filters, filters_size);
    if (FAILED(hr)) {
        std::cout << "loadFilters() failed" << std::endl;
        assert(0);
        return false;
    }

    // Start importing .wav
    WAVEFORMATEXTENSIBLE wfx = { 0 };
    XAUDIO2_BUFFER buffer = { 0 };

    //const std::string strFileName = "audio\\dandelion.wav";
    const std::string strFileName = "audio\\440.wav";

    hr = a3d::utils::openWav(strFileName.c_str(), wfx, buffer); // Output in wfx and buffer
    if (FAILED(hr)) {
        std::cout << "openWav() failed" << std::endl;
        assert(0);
        return false;
    }
    IXAPOParameters* pXAPO = a3d::getXAPO(filters, *filters_size);
    XAUDIO2_EFFECT_DESCRIPTOR descriptor = a3d::getEffectDescriptor(pXAPO);

    std::cout << "Finished!" << std::endl;

    // Structure indicating how many effects we have (1)
    XAUDIO2_EFFECT_CHAIN chain;
    chain.EffectCount = 1;
    chain.pEffectDescriptors = &descriptor;

    // Create a Submix Voice
    IXAudio2SubmixVoice* pSFXSubmixVoice = NULL;
    hr = pXAudio2->CreateSubmixVoice(&pSFXSubmixVoice, 1, 44100, 0, 0, 0, &chain);
    if (FAILED(hr)) {
        std::cout << "CreateSubmixVoice() failed" << std::endl;
        assert(0);
        return false;
    }

    // Populate structures for xaudio2, so it knows where to send data
    XAUDIO2_SEND_DESCRIPTOR voice;
    voice.Flags = 0;
    voice.pOutputVoice = pSFXSubmixVoice;

    XAUDIO2_VOICE_SENDS sendlist;
    sendlist.SendCount = 1;
    sendlist.pSends = &voice;

    // Create source voice
    IXAudio2SourceVoice* pSourceVoice;
    hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx, 0, 2.0, NULL, &sendlist, NULL);
    if (FAILED(hr)) {
        std::cout << "CreateSourceVoice() failed" << std::endl;
        assert(0);
        return false;
    }

    // Submit buffer to voice
    hr = pSourceVoice->SubmitSourceBuffer(&buffer);
    if (FAILED(hr)) {
        std::cout << "SubmitSourceBuffer() failed" << std::endl;
        assert(0);
        return false;
    }

    // Play the sound (when ready)
    hr = pSourceVoice->Start(0);
    if (FAILED(hr)) {
        std::cout << "Start() failed" << std::endl;
        assert(0);
        return false;
    }

    loop2(pXAPO, 100);

    // Pausing so we can hear the sound
    system("pause");
}