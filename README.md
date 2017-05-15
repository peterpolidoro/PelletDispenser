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
      "getAssayStatus"
    ],
    "parameters":[],
    "properties":[
      "basePositions",
      "deliverPositions",
      "dispensePositions",
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

```json
{
  "id":"getApiVerbose",
  "result":{
    "firmware":["PelletDispenser"],
    "functions":[
      {
        "name":"getAssayStatus",
        "parameters":[],
        "result_info":{
          "type":"object"
        }
      }
    ],
    "parameters":[],
    "properties":[
      {
        "name":"basePositions",
        "type":"array",
        "array_element_type":"double",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      },
      {
        "name":"deliverPositions",
        "type":"array",
        "array_element_type":"double",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      },
      {
        "name":"dispensePositions",
        "type":"array",
        "array_element_type":"double",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      },
      {
        "name":"buzzPeriod",
        "type":"long",
        "units":"ms",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"buzzOnDuration",
        "type":"long",
        "units":"ms",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"buzzCount",
        "type":"long",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneFrequency",
        "type":"long",
        "units":"Hz",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneDuration",
        "type":"long",
        "units":"s",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneVolume",
        "type":"double",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneDelayMin",
        "type":"long",
        "units":"s",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneDelayMax",
        "type":"long",
        "units":"s",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"returnDelay",
        "type":"double",
        "units":"min",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      }
    ],
    "callbacks":[
      {
        "name":"deliver",
        "properties":[],
        "functions":[
          "trigger",
          "attachTo",
          "detachFrom",
          "detachFromAll"
        ],
        "parameters":[
          "interrupt",
          "mode"
        ]
      },
      {
        "name":"abort",
        "properties":[],
        "functions":[
          "trigger",
          "attachTo",
          "detachFrom",
          "detachFromAll"
        ],
        "parameters":[
          "interrupt",
          "mode"
        ]
      }
    ]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
