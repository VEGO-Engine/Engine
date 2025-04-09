#include "InteractionEventdataStruct.h"

#include "VEGO.h"
#include "VEGO_Event.h"

void InteractionEventdataStruct::triggerEvent()
{
    // TODO: if target is null && strategy is 0, error

    SDL_Event event;
    SDL_zero(event);
    event.type = vego::VEGO_Event_Interaction;
    event.user.data1 = this;

    SDL_PushEvent(&event);
}