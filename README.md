<div align="center">

<h1>Meshtastic Firmware<br>with servo support</h1>

</div>

## Overview

This is a fork of the official Meshtastic firmware, adding servo support.

Meshtastic is an open-source LoRa mesh networking project designed for long-range, low-power communication without relying on internet or cellular infrastructure. The firmware supports various hardware platforms, including ESP32, nRF52, RP2040/RP2350, and Linux-based devices.

Meshtastic enables text messaging, location sharing, and telemetry over a decentralized mesh network, making it ideal for outdoor adventures, emergency preparedness, and remote operations.

This fork adds an ability to remotely control a servo connected to a Meshtastic device. Think remote controlled geocaches, vents, release mechanisms, etc.

## Get Started

- 🔧 **[Building Instructions](https://meshtastic.org/docs/development/firmware/build)** – Learn how to compile the firmware from source.
- ⚡ **[Flashing Instructions](https://meshtastic.org/docs/getting-started/flashing-firmware/)** – Install or update the firmware on your device.

### Configuration

This fork adds additional configuration settings:
- **servo_control.enabled** - true / false
- **servo_control.gpio_pin** - GPIO pin the servo is connected to
- **servo_control.open_position** - OPEN position 0-180°
- **servo_control.closed_position** - CLOSED position 0-180°
- **servo_control.authorized_key** - list of public keys of authorized nodes

Use my fork of [Python CLI](https://github.com/mehow/meshtastic-python) or [Android App](https://github.com/mehow/meshtastic-android) to set them before first use.

### Usage

The firmware recognizes the following text commands:
- **OPEN** moves the servo to the OPEN position
- **CLOSE** moves the servo to the CLOSED position
- **STATUS** responds with the current state of the servo

Use [Quick chat options](https://meshtastic.org/docs/software/android/usage/#quick-chat-options) to make sending those commands faster.
