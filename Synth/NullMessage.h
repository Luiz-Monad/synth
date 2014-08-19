#ifndef NULLMESSAGE_H
#define NULLMESSAGE_H

#include "Types.h"
#include "IMidiMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    class NullMessageClass;
    typedef NullMessageClass& NullMessage;

    class NullMessageClass : public IMidiMessageIf
    {

    private:

        bytebuffer GetBytes();
        int get_Status();
        Midi::MessageType get_MessageType();

    public:
        int GetHashCode();
        bool Equals(IEquatable obj);

    public:
        static const NullMessage null;

    };

}}}

#endif
