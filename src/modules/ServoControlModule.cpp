#include "ServoControlModule.h"
#include "configuration.h"
#include "main.h"
#include <string.h>

ServoControlModule::ServoControlModule()
    : SinglePortModule("servo", meshtastic_PortNum_TEXT_MESSAGE_APP)
{
    servo.attach(moduleConfig.servo_control.gpio_pin);
    LOG_INFO("Servo attached (pin %d)", moduleConfig.servo_control.gpio_pin);

    moveServoTo(moduleConfig.servo_control.open_position); // Default position
}

bool ServoControlModule::isTrustedNode(const meshtastic_MeshPacket_public_key_t public_key)
{
    if (public_key.size != 32) return false;
    
    // Example: check against a list of trusted node IDs in config
    for (int i = 0; i < moduleConfig.servo_control.authorized_key_count; i++) {
        if (moduleConfig.servo_control.authorized_key[i].size == 32 &&
          memcmp(public_key.bytes, moduleConfig.servo_control.authorized_key[i].bytes, 32) == 0) return true;
    }
    return false;
}

void ServoControlModule::moveServoTo(int angle)
{
    servo.write(angle);
}

ProcessMessage ServoControlModule::handleReceived(const meshtastic_MeshPacket &mp)
{
    if (!moduleConfig.servo_control.enabled) return ProcessMessage::CONTINUE;
    if (!isTrustedNode(mp.public_key)) return ProcessMessage::CONTINUE;

    auto &payload = mp.decoded.payload;
    if (payload.size == 0) return ProcessMessage::CONTINUE;

    if (strncmp((const char *)payload.bytes, "OPEN", payload.size) == 0) {
        moveServoTo(moduleConfig.servo_control.open_position);
        LOG_INFO("Servo moved to OPEN (%d degrees)", moduleConfig.servo_control.open_position);
        return ProcessMessage::STOP;
    } else if (strncmp((const char *)payload.bytes, "CLOSE", payload.size) == 0) {
        moveServoTo(moduleConfig.servo_control.closed_position);
        LOG_INFO("Servo moved to CLOSE (%d degrees)", moduleConfig.servo_control.closed_position);
        return ProcessMessage::STOP;
    }

    return ProcessMessage::CONTINUE;
}
