#pragma once
#include <Windows.h>
#include <mmsystem.h>


void MidiIO(int value, int sleep) {
    HMIDIOUT handle;
    midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
    int volume = 0x7f;
    int voice = 0x0;

    voice = (volume << 16) + (value << 8) + 0x94;

    midiOutShortMsg(handle, voice);
    Sleep(sleep);

    midiOutClose(handle);
}
