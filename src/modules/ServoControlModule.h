#pragma once
#include "SinglePortModule.h"
#include <Servo.h>

/**
 * Module to control a servo based on received commands from trusted nodes.
 */
class ServoControlModule : public SinglePortModule
{
public:
    ServoControlModule();

protected:
    virtual ProcessMessage handleReceived(const meshtastic_MeshPacket &mp) override;

private:
    Servo servo;
    void moveServoTo(int angle);
    bool isTrustedNode(const meshtastic_MeshPacket_public_key_t public_key);
};
