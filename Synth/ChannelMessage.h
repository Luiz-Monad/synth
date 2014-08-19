#ifndef CHANNELMESSAGE_H
#define CHANNELMESSAGE_H

//REGION(License)

/* Copyright (c) 2005 Leslie Sanford
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

//ENDREGION()

//REGION(Contact)

/*
 * Leslie Sanford
 * Email: jabberdabber@hotmail.com
 */

//ENDREGION()

#include "Types.h"
#include "ShortMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {
    
    REGION(Channel Command Types)

    /// <summary>
    /// Defines constants for ChannelMessage types.
    /// </summary>
    enum ChannelCommand 
    {
        /// <summary>
        /// Represents the note-off command type.
        /// </summary>
        NoteOff = 0x80,

        /// <summary>
        /// Represents the note-on command type.
        /// </summary>
        NoteOn = 0x90,

        /// <summary>
        /// Represents the poly pressure (aftertouch) command type.
        /// </summary>
        PolyPressure = 0xA0,

        /// <summary>
        /// Represents the controller command type.
        /// </summary>
        Controller = 0xB0,  
  
        /// <summary>
        /// Represents the program change command type.
        /// </summary>
        ProgramChange = 0xC0,

        /// <summary>
        /// Represents the channel pressure (aftertouch) command 
        /// type.
        /// </summary>
        ChannelPressure = 0xD0,   
     
        /// <summary>
        /// Represents the pitch wheel command type.
        /// </summary>
        PitchWheel = 0xE0
    };

    ENDREGION()

    REGION(Controller Types)

    /// <summary>
    /// Defines constants for controller types.
    /// </summary>
    enum ControllerType
    {
        /// <summary>
        /// The Bank Select coarse.
        /// </summary>
        BankSelect,

        /// <summary>
        /// The Modulation Wheel coarse.
        /// </summary>
        ModulationWheel,

        /// <summary>
        /// The Breath Control coarse.
        /// </summary>
        BreathControl,

        /// <summary>
        /// The Foot Pedal coarse.
        /// </summary>
        FootPedal = 4,

        /// <summary>
        /// The Portamento Time coarse.
        /// </summary>
        PortamentoTime,

        /// <summary>
        /// The Data Entry Slider coarse.
        /// </summary>
        DataEntrySlider,

        /// <summary>
        /// The Volume coarse.
        /// </summary>
        Volume,

        /// <summary>
        /// The Balance coarse.
        /// </summary>
        Balance,

        /// <summary>
        /// The Pan position coarse.
        /// </summary>
        Pan = 10,

        /// <summary>
        /// The Expression coarse.
        /// </summary>
        Expression,

        /// <summary>
        /// The Effect Control 1 coarse.
        /// </summary>
        EffectControl1,

        /// <summary>
        /// The Effect Control 2 coarse.
        /// </summary>
        EffectControl2,

        /// <summary>
        /// The General Puprose Slider 1
        /// </summary>
        GeneralPurposeSlider1 = 16,

        /// <summary>
        /// The General Puprose Slider 2
        /// </summary>
        GeneralPurposeSlider2,

        /// <summary>
        /// The General Puprose Slider 3
        /// </summary>
        GeneralPurposeSlider3,

        /// <summary>
        /// The General Puprose Slider 4
        /// </summary>
        GeneralPurposeSlider4,

        /// <summary>
        /// The Bank Select fine.
        /// </summary>
        BankSelectFine = 32,

        /// <summary>
        /// The Modulation Wheel fine.
        /// </summary>
        ModulationWheelFine,

        /// <summary>
        /// The Breath Control fine.
        /// </summary>
        BreathControlFine,

        /// <summary>
        /// The Foot Pedal fine.
        /// </summary>
        FootPedalFine = 36,

        /// <summary>
        /// The Portamento Time fine.
        /// </summary>
        PortamentoTimeFine,

        /// <summary>
        /// The Data Entry Slider fine.
        /// </summary>
        DataEntrySliderFine,

        /// <summary>
        /// The Volume fine.
        /// </summary>
        VolumeFine,

        /// <summary>
        /// The Balance fine.
        /// </summary>
        BalanceFine,

        /// <summary>
        /// The Pan position fine.
        /// </summary>
        PanFine = 42,

        /// <summary>
        /// The Expression fine.
        /// </summary>
        ExpressionFine,

        /// <summary>
        /// The Effect Control 1 fine.
        /// </summary>
        EffectControl1Fine,

        /// <summary>
        /// The Effect Control 2 fine.
        /// </summary>
        EffectControl2Fine,

        /// <summary>
        /// The Hold Pedal 1.
        /// </summary>
        HoldPedal1 = 64,

        /// <summary>
        /// The Portamento.
        /// </summary>
        Portamento,

        /// <summary>
        /// The Sustenuto Pedal.
        /// </summary>
        SustenutoPedal,

        /// <summary>
        /// The Soft Pedal.
        /// </summary>
        SoftPedal,

        /// <summary>
        /// The Legato Pedal.
        /// </summary>
        LegatoPedal,

        /// <summary>
        /// The Hold Pedal 2.
        /// </summary>
        HoldPedal2,

        /// <summary>
        /// The Sound Variation.
        /// </summary>
        SoundVariation,

        /// <summary>
        /// The Sound Timbre.
        /// </summary>
        SoundTimbre,

        /// <summary>
        /// The Sound Release Time.
        /// </summary>
        SoundReleaseTime,

        /// <summary>
        /// The Sound Attack Time.
        /// </summary>
        SoundAttackTime,

        /// <summary>
        /// The Sound Brightness.
        /// </summary>
        SoundBrightness,

        /// <summary>
        /// The Sound Control 6.
        /// </summary>
        SoundControl6,

        /// <summary>
        /// The Sound Control 7.
        /// </summary>
        SoundControl7,

        /// <summary>
        /// The Sound Control 8.
        /// </summary>
        SoundControl8,

        /// <summary>
        /// The Sound Control 9.
        /// </summary>
        SoundControl9,

        /// <summary>
        /// The Sound Control 10.
        /// </summary>
        SoundControl10,

        /// <summary>
        /// The General Purpose Button 1.
        /// </summary>
        GeneralPurposeButton1,

        /// <summary>
        /// The General Purpose Button 2.
        /// </summary>
        GeneralPurposeButton2,

        /// <summary>
        /// The General Purpose Button 3.
        /// </summary>
        GeneralPurposeButton3,

        /// <summary>
        /// The General Purpose Button 4.
        /// </summary>
        GeneralPurposeButton4,

        /// <summary>
        /// The Effects Level.
        /// </summary>
        EffectsLevel = 91,

        /// <summary>
        /// The Tremelo Level.
        /// </summary>
        TremeloLevel,
        
        /// <summary>
        /// The Chorus Level.
        /// </summary>
        ChorusLevel,

        /// <summary>
        /// The Celeste Level.
        /// </summary>
        CelesteLevel,

        /// <summary>
        /// The Phaser Level.
        /// </summary>
        PhaserLevel,

        /// <summary>
        /// The Data Button Increment.
        /// </summary>
        DataButtonIncrement,

        /// <summary>
        /// The Data Button Decrement.
        /// </summary>
        DataButtonDecrement,

        /// <summary>
        /// The NonRegistered Parameter Fine.
        /// </summary>
        NonRegisteredParameterFine,

        /// <summary>
        /// The NonRegistered Parameter Coarse.
        /// </summary>
        NonRegisteredParameterCoarse,

        /// <summary>
        /// The Registered Parameter Fine.
        /// </summary>
        RegisteredParameterFine,

        /// <summary>
        /// The Registered Parameter Coarse.
        /// </summary>
        RegisteredParameterCoarse,

        /// <summary>
        /// The All Sound Off.
        /// </summary>
        AllSoundOff = 120,

        /// <summary>
        /// The All Controllers Off.
        /// </summary>
        AllControllersOff,

        /// <summary>
        /// The Local Keyboard.
        /// </summary>
        LocalKeyboard,
        
        /// <summary>
        /// The All Notes Off.
        /// </summary>
        AllNotesOff,

        /// <summary>
        /// The Omni Mode Off.
        /// </summary>
        OmniModeOff,

        /// <summary>
        /// The Omni Mode On.
        /// </summary>
        OmniModeOn,

        /// <summary>
        /// The Mono Operation.
        /// </summary>
        MonoOperation,

        /// <summary>
        /// The Poly Operation.
        /// </summary>
        PolyOperation
    };

    ENDREGION()
    
    class ChannelMessageClass;
    typedef ChannelMessageClass& ChannelMessage;

    /// <summary>
    /// Represents MIDI channel messages.
    /// </summary>
    class ChannelMessageClass : public ShortMessageClass
    {
        REGION(ChannelMessage Members)

        REGION(Constants)

    private:

        //
        // Bit manipulation constants.
        //

        static const int MidiChannelMask = ~15;
        static const int CommandMask = ~240;

    public:

        /// <summary>
        /// Maximum value allowed for MIDI channels.
        /// </summary> 
        static const int MidiChannelMaxValue = 15;

        ENDREGION()

        REGION(Construction)
        
    public:

        /// <summary>
        /// Initializes a new instance of the ChannelEventArgs class with the
        /// specified command, MIDI channel, and data 1 values.
        /// </summary>
        /// <param name="command">
        /// The command value.
        /// </param>
        /// <param name="midiChannel">
        /// The MIDI channel.
        /// </param>
        /// <param name="data1">
        /// The data 1 value.
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException">
        /// If midiChannel is less than zero or greater than 15. Or if 
        /// data1 is less than zero or greater than 127.
        /// </exception>
        ChannelMessageClass(ChannelCommand command, int midiChannel, int data1);

        /// <summary>
        /// Initializes a new instance of the ChannelEventArgs class with the 
        /// specified command, MIDI channel, data 1, and data 2 values.
        /// </summary>
        /// <param name="command">
        /// The command value.
        /// </param>
        /// <param name="midiChannel">
        /// The MIDI channel.
        /// </param>
        /// <param name="data1">
        /// The data 1 value.
        /// </param>
        /// <param name="data2">
        /// The data 2 value.
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException">
        /// If midiChannel is less than zero or greater than 15. Or if 
        /// data1 or data 2 is less than zero or greater than 127. 
        /// </exception>
        ChannelMessageClass(ChannelCommand command, int midiChannel, int data1, int data2);

        ChannelMessageClass(int message);

        ENDREGION()

        REGION(Methods)

    public:

        /// <summary>
        /// Returns a value for the current ChannelEventArgs suitable for use in 
        /// hashing algorithms.
        /// </summary>
        /// <returns>
        /// A hash code for the current ChannelEventArgs.
        /// </returns>
        /*override*/ int GetHashCode();

        /// <summary>
        /// Determines whether two ChannelEventArgs instances are equal.
        /// </summary>
        /// <param name="obj">
        /// The ChannelMessageEventArgs to compare with the current ChannelEventArgs.
        /// </param>
        /// <returns>
        /// <b>true</b> if the specified object is equal to the current 
        /// ChannelMessageEventArgs; otherwise, <b>false</b>.
        /// </returns>
        /*override*/ bool Equals(IEquatable obj);

        /// <summary>
        /// Returns a value indicating how many bytes are used for the 
        /// specified ChannelCommand.
        /// </summary>
        /// <param name="command">
        /// The ChannelCommand value to test.
        /// </param>
        /// <returns>
        /// The number of bytes used for the specified ChannelCommand.
        /// </returns>
        static int DataBytesPerType(ChannelCommand command);
   
        /// <summary>
        /// Unpacks the command value from the specified integer channel 
        /// message.
        /// </summary>
        /// <param name="message">
        /// The message to unpack.
        /// </param>
        /// <returns>
        /// The command value for the packed message.
        /// </returns>
        static ChannelCommand UnpackCommand(int message);
     
        /// <summary>
        /// Unpacks the MIDI channel from the specified integer channel 
        /// message.
        /// </summary>
        /// <param name="message">
        /// The message to unpack.
        /// </param>
        /// <returns>
        /// The MIDI channel for the pack message.
        /// </returns>
        static int UnpackMidiChannel(int message);

        /// <summary>
        /// Packs the MIDI channel into the specified integer message.
        /// </summary>
        /// <param name="message">
        /// The message into which the MIDI channel is packed.
        /// </param>
        /// <param name="midiChannel">
        /// The MIDI channel to pack into the message.
        /// </param>
        /// <returns>
        /// An integer message.
        /// </returns>
        /// <exception cref="ArgumentOutOfRangeException">
        /// If midiChannel is less than zero or greater than 15.
        /// </exception>
        static int PackMidiChannel(int message, int midiChannel);

        /// <summary>
        /// Packs the command value into an integer message.
        /// </summary>
        /// <param name="message">
        /// The message into which the command is packed.
        /// </param>
        /// <param name="command">
        /// The command value to pack into the message.
        /// </param>
        /// <returns>
        /// An integer message.
        /// </returns>
        static int PackCommand(int message, ChannelCommand command);

        ENDREGION()

        REGION(Properties)

    public:
        
        /// <summary>
        /// Gets the channel command value.
        /// </summary>
        ReadOnlyProperty<ChannelCommand> Command;
        
        /// <summary>
        /// Gets the MIDI channel.
        /// </summary>
        ReadOnlyProperty<int> MidiChannel;

        /// <summary>
        /// Gets the first data value.
        /// </summary>
        ReadOnlyProperty<int> Data1;
        
        /// <summary>
        /// Gets the second data value.
        /// </summary>
        ReadOnlyProperty<int> Data2;

        /// <summary>
        /// Gets the EventType.
        /// </summary>
        /*override*/ ReadOnlyProperty<Midi::MessageType> MessageType;

        ENDREGION()

        ENDREGION()

    private:
        void init();
        ChannelCommand get_Command();
        int get_MidiChannel();
        int get_Data1();
        int get_Data2();
        Midi::MessageType get_MessageType();

    public:
        static const ChannelMessage null;

    };

}}}

#endif
