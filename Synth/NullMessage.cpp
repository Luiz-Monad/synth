
#include "NullMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    const NullMessage NullMessageClass::null = NullMessageClass();

    bytebuffer GetBytes()
    {
        return bytebufferclass(0);
    }
    
    int NullMessageClass::get_Status()
    {
        return 0;
    }

    MessageType NullMessageClass::get_MessageType()
    {
        return (Midi::MessageType)(9999);
    }
        
    int NullMessageClass::GetHashCode()
    {
        return 0;
    }

    bool NullMessageClass::Equals(IEquatable obj)
    {
        if(!(isinst<NullMessageClass>(obj)))
        {
            return false;
        }
        return true;
    }

}}}

