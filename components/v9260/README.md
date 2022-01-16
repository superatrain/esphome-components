# V9260 Energy Meter

The `V9260` sensor platform allows you to use `V9260` energy meters sensors (Along with other similar Vango sensors) with `ESPHome`.

> This page refers to version V9260. There are similar common chips like V9260S, V9260F, V9281. This implementation of V9260 is as found on `Orbivo S31`. To use with other models, you may have to modify any of the request data, response data, baud rates, and configuration parameters.

```yaml
# Example configuration entry
...
external_components:
  - source: github://dentra/esphome-components
...
uart:
  rx_pin: GPIO3
  tx_pin: GPIO1
  baud_rate: 2400
  parity: ODD

switch:
  # All the options of v9260 platform are optional
  - platform: v9260
    # energy sensor in kWh, Sensor
    energy:
      name: Energy
    # voltage sensor in V, Sensor,
    voltage:
      name: Voltage
    # current sensor in A, Sensor,
    current:
      name: Current
    # active power in W, Sensor
    active_power:
      name: Active Power
    # active power in VAR, Sensor
    reactive_power:
      name: Reactive Power
    # active power in VA, Sensor
    apparent_power:
      name: Apparent Power
    # power factor, Sensor
    power_factor:
      name: Power Factor
    # frequency in Hz, Sensor
    frequency:
      name: Frequency
    update_interval: 30s
```
