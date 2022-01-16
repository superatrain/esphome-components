#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace v9260 {

struct v9260_data_t {
  uint8_t header[3];          // FE1109  #0x119 starting with, instead of the 108 from the 9281?
  uint8_t active_power[4];    // W, divided by 100
  uint8_t reactive_power[4];  // divided by 100
  uint8_t voltage[4];         // V, divided by 10
  uint8_t current[4];         // A, divided by 10000
  uint8_t line_frequency[4];  // Hz, divided by 100
  uint8_t frequency[4];       // Hz, divided by 100
  uint8_t checksum;
} PACKED;

class V9260 : public PollingComponent, public switch_::Switch, public uart::UARTDevice {
 public:
  void dump_config() override;
  void setup() override;
  void loop() override;
  void update() override;

  void set_energy(sensor::Sensor *value) { this->energy_ = value; }
  void set_voltage(sensor::Sensor *value) { this->voltage_ = value; }
  void set_current(sensor::Sensor *value) { this->current_ = value; }
  void set_active_power(sensor::Sensor *value) { this->active_power_ = value; }
  void set_reactive_power(sensor::Sensor *value) { this->reactive_power_ = value; }
  void set_apparent_power(sensor::Sensor *value) { this->apparent_power_ = value; }
  void set_frequency(sensor::Sensor *value) { this->frequency_ = value; }
  void set_power_factor(sensor::Sensor *value) { this->power_factor_ = value; }

 protected:
  sensor::Sensor *energy_ = {};
  sensor::Sensor *voltage_ = {};
  sensor::Sensor *current_ = {};
  sensor::Sensor *active_power_ = {};
  sensor::Sensor *reactive_power_ = {};
  sensor::Sensor *apparent_power_ = {};
  sensor::Sensor *frequency_ = {};
  sensor::Sensor *power_factor_ = {};

  float get_val(const uint8_t data[4], float mul);
  uint8_t calc_crc_(const v9260_data_t &data);

  void write_state(bool state) override;
};

}  // namespace v9260
}  // namespace esphome
