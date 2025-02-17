#pragma once
#ifdef ARDUINO_ARCH_ESP32

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "../miot/miot.h"

namespace esphome {
namespace miot_cgg1 {

class MiotCGG1 : public miot::MiotComponent, public sensor::Sensor {
 public:
  void dump_config() override;

  uint16_t get_product_id() const override { return 0x0347; }
  const char *get_product_code() const override { return "CGG1"; }

  void set_humidity(sensor::Sensor *humidity) { this->humidity_ = humidity; }

 protected:
  sensor::Sensor *humidity_{nullptr};

  bool process_object_(const miot::BLEObject &obj) override;

  void process_temperature_(const miot::BLEObject &obj);
  void process_humidity_(const miot::BLEObject &obj);
  void process_temperature_humidity_(const miot::BLEObject &obj);
};

class MiotCGG1Encrypted : public miot::MiotComponent {
 public:
  uint16_t get_product_id() const override { return 0x0B48; }
};

}  // namespace miot_cgg1
}  // namespace esphome

#endif
