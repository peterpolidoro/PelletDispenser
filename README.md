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

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["PelletDispenser"],
    "functions":[
      "getAssayStatus"
    ],
    "parameters":[],
    "properties":[
      "basePositions",
      "deliverPositions",
      "dispensePositions",
      "toneDelayMin",
      "toneDelayMax",
      "returnDelay",
      "toneFrequency",
      "toneDuration",
      "toneVolume"
    ],
    "callbacks":[
      "deliver",
      "abort"
    ]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
