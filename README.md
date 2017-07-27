# PelletDispenser

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

[Examples](./examples)

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

[StepDirController](https://github.com/janelia-arduino/StepDirController)

[StepperController](https://github.com/janelia-arduino/StepperController)

[StageController](https://github.com/janelia-arduino/StageController)

## Clients

[HBridgeController](https://github.com/janelia-arduino/HBridgeController)

[OpticalSwitchInterface](https://github.com/janelia-arduino/OpticalSwitchInterface)

[AudioController](https://github.com/janelia-arduino/AudioController)

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

[stepper_controller](https://github.com/janelia-modular-devices/stepper_controller.git)

[h_bridge_controller](https://github.com/janelia-modular-devices/h_bridge_controller.git)

[optical_switch_interface](https://github.com/janelia-modular-devices/optical_switch_interface.git)

[audio_controller](https://github.com/janelia-modular-devices/audio_controller.git)

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["PelletDispenser"],
    "functions":[
      "setClientPropertyValues",
      "getAssayStatus"
    ],
    "parameters":[],
    "properties":[
      "basePositions",
      "deliverPositions",
      "dispensePosition",
      "buzzPeriod",
      "buzzOnDuration",
      "buzzCount",
      "toneFrequency",
      "toneDuration",
      "toneVolume",
      "toneDelayMin",
      "toneDelayMax",
      "returnDelay"
    ],
    "callbacks":[
      "deliver",
      "abort"
    ]
  }
}
```

## API Verbose

[API Verbose](./api.json)

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
