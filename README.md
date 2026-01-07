## **GitHub Repository Description**

> A high-performance ESP32-CAM firmware that serves a full web UI from SD card (SDIO mode) and exposes complete OV2640 SCCB register control via REST APIs. Designed for maximum write throughput, real-time camera configuration, and zero hardcoded web assets.

---

## **README.md**

# ESP32-CAM SDIO Web-Controlled OV2640 System

## Overview

This project implements a **fully web-controlled ESP32-CAM system** where:

* All **web files are stored and served from SD card** (SDIO mode, not SPI)
* **OV2640 camera registers** are exposed through REST APIs
* Camera configuration is done **exclusively via SCCB (I²C-like)**
* No HTML/CSS/JS is embedded in firmware
* Designed for **maximum SD write performance**
* Suitable for research, vision experiments, and low-level sensor control

The system allows **direct manipulation of every OV2640 register** from a browser or external application.

---

## Key Features

### Storage & Performance

* SD card operated in **native SDIO (4-bit) mode**
* High-speed file write for images and video frames
* Web assets loaded dynamically from SD card
* No SPIFFS or PROGMEM web files

### Camera Control

* Full OV2640 SCCB register access
* Read / write / masked write support
* Register bank switching (DSP & Sensor)
* Runtime control of:

  * Resolution
  * Output format (RAW / YUV / RGB / JPEG)
  * Exposure
  * Gain
  * White balance
  * Windowing / ROI

### Web Interface

* Browser-based UI served from SD card
* Live configuration without reflashing firmware
* REST API driven architecture
* Supports automation scripts and external control

### System Design

* Clean driver abstraction
* FreeRTOS task separation
* Command queue for camera operations
* Robust error handling and logging

---

## Hardware Requirements

| Component | Requirement                          |
| --------- | ------------------------------------ |
| MCU       | ESP32-CAM (AI Thinker or compatible) |
| Camera    | OV2640                               |
| Storage   | MicroSD card (Class 10 recommended)  |
| SD Mode   | **SDIO (not SPI)**                   |
| Power     | Stable 5V supply (≥1A recommended)   |

---

## Pin Configuration (Typical ESP32-CAM)

> ⚠️ Adjust if your board differs.

### SDIO

| Signal | GPIO   |
| ------ | ------ |
| CLK    | GPIO14 |
| CMD    | GPIO15 |
| D0     | GPIO2  |
| D1     | GPIO4  |
| D2     | GPIO12 |
| D3     | GPIO13 |

### SCCB (Camera Control)

| Signal | GPIO   |
| ------ | ------ |
| SCL    | GPIO21 |
| SDA    | GPIO22 |

---

## Project Structure

```
.
├── src/
│   ├── main.c                 # System initialization & task orchestration
│   ├── sccb_driver.c          # Low-level SCCB (I2C) driver
│   ├── ov2640_control.c       # Register-level camera control
│   ├── web_server.c           # HTTP server & API routing
│   ├── storage.c              # SDIO filesystem management
│   └── camera_capture.c       # Image/video capture pipeline
│
├── include/
│   ├── sccb_driver.h
│   ├── ov2640_regs.h          # Complete OV2640 register definitions
│   ├── ov2640_control.h
│   ├── web_server.h
│   └── storage.h
│
├── sdcard/
│   └── www/
│       ├── index.html
│       ├── styles.css
│       └── app.js
│
└── README.md
```

---

## System Flow

1. ESP32 boots and mounts SD card using **SDIO**
2. Web server starts
3. Static web files are served directly from SD card
4. Browser UI sends REST commands
5. Firmware translates requests into SCCB register operations
6. OV2640 responds in real time
7. Captured data is stored directly on SD card

---

## REST API Documentation

### Read Single Register

**GET**

```
/api/registers/single?bank=0&addr=0x12
```

**Response**

```json
{
  "bank": 0,
  "addr": 18,
  "value": 128
}
```

---

### Write Single Register

**POST**

```
/api/registers/single
```

```json
{
  "bank": 1,
  "addr": 0x13,
  "value": 0xE5
}
```

---

### Masked Register Write

```json
{
  "bank": 1,
  "addr": 0x13,
  "mask": 0x02,
  "value": 0x02
}
```

---

### Dump All Registers

**GET**

```
/api/registers/dump
```

Returns full DSP and Sensor register map.

---

### Capture Image

```json
{
  "type": "single"
}
```

Options:

* `single`
* `burst`
* `video`

---

### System Status

**GET**

```
/api/system/status
```

---

## SD Card Layout

```
/sdcard
├── www/            # Web UI files
├── captures/
│   ├── img_001.raw
│   ├── img_002.raw
│   └── video_001/
└── config.json
```

---

## Build & Flash

### Requirements

* ESP-IDF v5.x+
* Python 3.x
* Proper SDIO wiring

### Build

```
idf.py build
```

### Flash

```
idf.py flash monitor
```

---

## Design Goals

* Zero hardcoded UI
* Maximum SD write speed
* Register-level camera control
* Research-friendly architecture
* Clean separation of hardware and UI

---

## Known Limitations

* No live preview in RAW mode
* SDIO pins limit GPIO availability
* OV2640 SCCB speed limited to 400 kHz

---

## Intended Use Cases

* Camera sensor research
* Embedded vision experiments
* ISP tuning & register testing
* Edge-AI data collection
* Academic & lab projects

---

## License

MIT License
Free to use, modify, and distribute.

---

If you want, I can also:

* Add **API Swagger/OpenAPI spec**
* Write **developer contribution guidelines**
* Create **architecture diagrams**
* Optimize README for **GitHub stars & discoverability**
