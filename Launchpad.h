/*
 * Launchpad.cpp

 *
 *  Created on: Dec 22, 2016
 *      Author: james
 */


#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
#include <string>
#include <sstream>
#include <bitset>

#define FLASH_DELAY_MS	100

class Launchpad	// : private MidiInput,
				//	private MidiOutput,
				//	public MidiInputCallback
{
public:

	class LaunchpadKey
	{
		// add x-y and drum rack arrays of row/column vs notes and codes
		// use LaunchPadKey object?  or just basic array?  what are benefits of each?
		const uint8_t drumRackLayoutCodes[8][8] = {
				{ 0x40, 0x41, 0x42, 0x43, 0x60, 0x61, 0x62, 0x63 },
				{ 0x3C, 0x3D, 0x3E, 0x3F, 0x5C, 0x5D, 0x5E, 0x5F },
				{ 0x38, 0x39, 0x3A, 0x3B, 0x58, 0x59, 0x5A, 0x5B },
				{ 0x34, 0x35, 0x36, 0x37, 0x54, 0x55, 0x56, 0x57 },
				{ 0x30, 0x31, 0x32, 0x33, 0x50, 0x51, 0x52, 0x53 },
				{ 0x2C, 0x2D, 0x2E, 0x2F, 0x4C, 0x4D, 0x4E, 0x4F },
				{ 0x28, 0x29, 0x2A, 0x2B, 0x48, 0x49, 0x4A, 0x4B },
				{ 0x24, 0x25, 0x26, 0x27, 0x44, 0x45, 0x46, 0x47 }
		};

		const uint8_t xyLayoutCodes[8][8] = {
				{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 },
				{ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 },
				{ 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 },
				{ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37 },
				{ 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 },
				{ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57 },
				{ 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67 },
				{ 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77 }
		};

	public:

		uint8_t key;
		uint8_t velocity;
		uint8_t x_pos;
		uint8_t y_pos;

		enum KeyMap { DrumRack, XY };
		// full brightness defaults
		//enum KeyColor { Off = 0x0C, Red = 0x0F , Green = 0x3C, Yellow = 0x3E , Amber = 0x3F };
		enum KeyColor { Off = 0x00, Red = 0x03 , Green = 0x30, Yellow = 0x3C , Amber = 0x33 };
		enum KeyBrightness { Low, High };

		LaunchpadKey(int row, int col){
			x_pos = col;
			y_pos = row;
			velocity = 0;
			key = drumRackLayoutCodes[y_pos][x_pos];
		}

		~LaunchpadKey(){

		}

		String print_details()
		{
			std::ostringstream str;
			str << "Row: " << (int)y_pos << " Col: " << (int)x_pos << " Key: " << (int)key;

			return str.str();
		}

		void set_key(KeyMap map)
		{
			this->key = get_key(map);
		}

		uint8_t get_key(KeyMap map)
		{
			uint8_t key;

			if(map == DrumRack)
			{
				key = drumRackLayoutCodes[this->y_pos][this->x_pos];
			}
			else if(map == XY)
			{
				key = xyLayoutCodes[this->y_pos][this->x_pos];
			}
			else
			{
				key = drumRackLayoutCodes[this->y_pos][this->x_pos];
			}

			return key;
		}

		void setKeyColor(KeyColor color)
		{

			this->velocity = color;

		}

		// return single (two?) byte velocity value
		uint8_t get_velocity(KeyColor color)
		{
			this->velocity = color;

			return this->velocity;
		}

		bool isKey(uint8_t x_pos, uint8_t y_pos)
		{
			if(this->x_pos == x_pos && this->y_pos == y_pos)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	};

	// begin non-LaunchpadKey

	std::list<LaunchpadKey> KeyList;

	void set_map(LaunchpadKey::KeyMap map)
	{
		std::list<LaunchpadKey>::iterator iterator;

		for(iterator = KeyList.begin(); iterator != KeyList.end(); ++iterator)
		{
			iterator->set_key(map);

		}
	}

	MidiInput *input;
	MidiOutput *output;

	uint8_t velArray[8][8] = { {0x0} };

	uint8_t lastDoubleBufByte;

//public:

//	virtual MidiInputCallback launchpadMessageHandler()
//	{
//
//	}

	Launchpad()// : MidiInput(name),
					//MidiOutput(name)
	{
		// add all key objects based on row and column
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				KeyList.push_back(LaunchpadKey(row, col));
			}
		}

		// enumerate devices and initialize
		StringArray inputDevices = MidiInput::getDevices();
		StringArray outputDevices = MidiOutput::getDevices();

		for(int i = 0; i < inputDevices.size(); ++i)
		{
			Logger::outputDebugString(inputDevices[i]);
			if(inputDevices[i].contains("Launchpad"))
			{
				//input = MidiInput::openDevice(i, &launchpadMessageHandler);
				input = NULL;
			}
		}

		for(int i = 0; i < outputDevices.size(); ++i)
		{
			Logger::outputDebugString(outputDevices[i]);
			if(outputDevices[i].contains("Launchpad"))
			{
				output = MidiOutput::openDevice(i);
			}
		}

		lastDoubleBufByte = 0x34;

		this->resetLaunchpad();

	}

	~Launchpad()
	{
		this->resetLaunchpad();
	}

	void print_keys()
	{
		std::list<LaunchpadKey>::iterator iterator;

		for(iterator = KeyList.begin(); iterator != KeyList.end(); ++iterator)
		{
			Logger::outputDebugString(iterator->print_details());
		}
	}

	void set_map_DrumRack()
	{
		set_map(LaunchpadKey::DrumRack);
	}

	void set_map_XY()
	{
		set_map(LaunchpadKey::XY);
	}

	void setKeyBuf(int x_pos, int y_pos, LaunchpadKey::KeyColor color)
	{

	}

	void writeBufNow()
	{
		static bool firstRun = true;
		uint8_t *bytes;

		// first run send initial set up message
		if(firstRun == true)
		{
			output->sendMessageNow(MidiMessage(0xB0, 0x00, 0x31));
			lastDoubleBufByte = 0x31;
			firstRun = false;
		}

		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j += 2)
			{
				bytes = &velArray[i][j];
				output->sendMessageNow(MidiMessage(0x92, bytes[0], bytes[1], 0));
			}
		}
		// set non-main grid buttons to 0 for now
		for(int i = 0; i < 8; i++)
		{
			output->sendMessageNow(MidiMessage(0x92, 0x0, 0x0, 0));
		}

		// wait for min set up time (TODO optimize)
		Time::waitForMillisecondCounter(Time::getMillisecondCounter()+FLASH_DELAY_MS);

		// switch display buffer
		if(lastDoubleBufByte == 0x34)
		{
			output->sendMessageNow(MidiMessage(0xB0, 0x00, 0x31));
			lastDoubleBufByte = 0x31;
		}
		else
		{
			output->sendMessageNow(MidiMessage(0xB0, 0x00, 0x34));
			lastDoubleBufByte = 0x34;
		}
	}

	void setKey(int x_pos, int y_pos, LaunchpadKey::KeyColor color, bool setNow)
	{
		// find key
		std::list<LaunchpadKey>::iterator iterator;

		for(iterator = KeyList.begin(); iterator != KeyList.end(); ++iterator)
		{
			if(iterator->isKey(x_pos, y_pos))
			{
				iterator->setKeyColor(color);
				if(setNow == true)
				{
					// creates message and writes immediately
					MidiMessage currentMessage(0x90, (int)iterator->key, (int)iterator->velocity, (double)0);
					output->sendMessageNow(currentMessage);
				}
				else
				{
					// assumes 0x0 set initially (or does it need to?)
					velArray[x_pos][y_pos] = iterator->velocity;
				}
				break;
			}

		}

	}

	void resetLaunchpad()
	{
		MidiMessage resetMessage(0xB0, 0x00, 0x00, 0);

		output->sendMessageNow(resetMessage);
	}

	void turnOnAllLow()
	{
		MidiMessage turnAllOnLowMessage(0xB0, 0x00, 0x7D, 0);

		output->sendMessageNow(turnAllOnLowMessage);
	}

	void turnOnAllMed()
	{
		MidiMessage turnAllOnMedMessage(0xB0, 0x00, 0x7E, 0);

		output->sendMessageNow(turnAllOnMedMessage);
	}

	void turnOnAllHigh()
	{
		MidiMessage turnAllOnHiMessage(0xB0, 0x00, 0x7F, 0);

		output->sendMessageNow(turnAllOnHiMessage);
	}

	bool isOutputOpen()
	{
		if(output != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void sendRawMessage(int byte1, int byte2, int byte3)
	{
		output->sendMessageNow(MidiMessage(byte1, byte2, byte3, 0));
	}

	//
	//	void handleIncomingMidiMessage (MidiInput* source,
	//	                                            const MidiMessage& message)
	//	{
	//
	//	}
	//
	//	void handlePartialSysexMessage (MidiInput* source,
	//	                                            const uint8* messageData,
	//	                                            int numBytesSoFar,
	//	                                            double timestamp)
	//	{
	//
	//	}

};
