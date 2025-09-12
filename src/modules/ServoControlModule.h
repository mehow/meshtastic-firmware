#pragma once
#include "SinglePortModule.h"
#ifdef ARCH_ESP32
#include <ESP32Servo.h>
#else
#include <Servo.h>
#endif

/**
 * Module to control a servo based on received commands from trusted nodes.
 */
class ServoControlModule : public SinglePortModule
{
public:
    ServoControlModule();

protected:
    virtual ProcessMessage handleReceived(const meshtastic_MeshPacket &mp) override;
    virtual meshtastic_MeshPacket *allocReply() override;

private:
    Servo servo;
    void moveServoTo(int angle);
    int getServoPosition();
    bool isTrustedNode(const meshtastic_MeshPacket_public_key_t public_key);
};
