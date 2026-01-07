# JSON Serialization for w-M-Bus–Related Firmware (ESP32)

## Project Overview
This project implements an embedded-friendly JSON serialization library for structured meter data.
It represents a typical smart-meter / w-M-Bus gateway data pipeline:

Meter data → Internal structures → JSON → Gateway / Backend

Radio communication, OMS, encryption, and real meter interaction are intentionally out of scope.

---

## Platform Choice
- Platform: ESP32
- Framework: Arduino ESP32

**Justification:**
ESP32 is widely used in IoT gateways and embedded systems and provides sufficient memory for safe
string-based serialization while remaining embedded-oriented.

---

## Programming Language
- Language: C
- No external JSON libraries
- Deterministic memory usage
- Caller-provided output buffer

---

## Project Structure
