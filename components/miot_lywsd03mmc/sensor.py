import logging
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, miot
from esphome.const import (
    CONF_HUMIDITY,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_PERCENT,
)

_LOGGER = logging.getLogger(__name__)

CODEOWNERS = ["@dentra"]
AUTO_LOAD = ["miot"]

miot_lywsd03mmc_ns = cg.esphome_ns.namespace("miot_lywsd03mmc")
MiotLYWSD03MMC = miot_lywsd03mmc_ns.class_(
    "MiotLYWSD03MMC", miot.MiotComponent, sensor.Sensor
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(MiotLYWSD03MMC),
            cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_HUMIDITY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        },
    )
    .extend(miot.MIOT_BLE_DEVICE_SCHEMA)
)


async def to_code(config):
    _LOGGER.warning(
        "miot_lywsd03mmc is deprecated, please use miot_thermogigro instead."
    )
    var = await miot.new_sensor_device(config)
    if CONF_HUMIDITY in config:
        sens = await sensor.new_sensor(config[CONF_HUMIDITY])
        cg.add(var.set_humidity(sens))
