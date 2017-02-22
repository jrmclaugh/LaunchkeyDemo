/*
 * LaunchkeyMini.h
 *
 *  Created on: Feb 9, 2017
 *      Author: james
 */

#ifndef LAUNCHKEYMINI_H_
#define LAUNCHKEYMINI_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
#include <string>
#include <sstream>
#include <bitset>
#include "Launchpad.h"

class LaunchkeyMini : public MidiInputCallback {
public:

	MidiInput *input;
	Launchpad launchpad;

	LaunchkeyMini(){
		// enumerate devices and initialize
		StringArray inputDevices = MidiInput::getDevices();

		for(int i = 0; i < inputDevices.size(); ++i)
		{
			Logger::outputDebugString(inputDevices[i]);
			if(inputDevices[i].contains("Launchkey Mini MIDI 1"))
			{
				input = MidiInput::openDevice(i, this);
				setMidiInput (i);
				//input = NULL;
			}
		}

		lastInputIndex = 0;
	}

	~LaunchkeyMini(){

	}

private:
    /** Starts listening to a MIDI input device, enabling it if necessary. */
    void setMidiInput (int index)
    {
        const StringArray list (MidiInput::getDevices());

        deviceManager.removeMidiInputCallback (list[lastInputIndex], this);

        const String newInput (list[index]);

        if (! deviceManager.isMidiInputEnabled (newInput))
            deviceManager.setMidiInputEnabled (newInput, true);

        deviceManager.addMidiInputCallback (newInput, this);
        //midiInputList.setSelectedId (index + 1, dontSendNotification);

        lastInputIndex = index;
    }

	void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override
	{
		String str;
		str << "N: " << message.getNoteNumber() << " V: " << message.getVelocity() << " C: " << message.getControllerValue();
		Logger::outputDebugString(str);

		if(message.getVelocity() > 0)
		{
			launchpad.sendRawMessage(0x90, message.getNoteNumber(), 0x30);
		}
		else
		{
			launchpad.sendRawMessage(0x90, message.getNoteNumber(), 0);
		}


	}

	AudioDeviceManager deviceManager;
	int lastInputIndex;
};



#endif /* LAUNCHKEYMINI_H_ */
