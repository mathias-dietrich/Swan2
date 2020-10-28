//
//  Listener.h
//  Swan
//
//  Created by Mathias Dietrich on 28.10.20.
//

#ifndef Listener_h
#define Listener_h
#include <stdio.h>
#include <iostream>

#include "Types.h"

class Listener{
    public:
    virtual void listen(EReply c, int params[]) = 0;
    virtual void listen(EReply c, string s) = 0;
};
#endif /* Listener_h */
