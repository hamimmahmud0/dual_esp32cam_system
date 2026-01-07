#ifndef CONFIG_H
#define CONFIG_H

// System Roles
#define ROLE_MASTER 0
#define ROLE_SLAVE 1
extern int SYSTEM_ROLE;

// Hardware Pins (ESP32-CAM AI-Thinker)
#define TRIGGER_OUTPUT_PIN 12    // Master sends trigger
#define TRIGGER_INPUT_PIN 13     // Slave receives trigger
#define FLASH_LED_PIN 4

// Camera Configuration
#define CAMERA_MODEL_AI_THINKER
#define MAX_RESOLUTION FRAMESIZE_UXGA  // 1600x1200
#define FRAME_BUFFER_COUNT 2
#define JPEG_QUALITY 10  // Only for MJPEG mode

// SD Card Settings
#define SD_MMC_FREQUENCY 20000000  // 20MHz
#define SD_MMC_DATA_WIDTH 4
#define MAX_FILE_SIZE (10 * 1024 * 1024)  // 10MB per file

// Network Settings
#define MASTER_AP_SSID "ESP32-Master"
#define MASTER_AP_PASSWORD "master123"
#define SLAVE_STA_SSID "ESP32-Master"
#define SLAVE_STA_PASSWORD "master123"
#define MASTER_IP "192.168.4.1"
#define SLAVE_IP "192.168.4.2"
#define HTTP_PORT 80

// Timing Constants
#define TRIGGER_HIGH_DURATION_MS 50
#define SYNC_TIMEOUT_MS 5000
#define FILE_TRANSFER_TIMEOUT_MS 10000

// File Naming
#define MAX_FILENAME_LEN 64
#define MAX_METADATA_SIZE 512

#endif