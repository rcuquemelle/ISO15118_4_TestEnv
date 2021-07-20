IEC61851 SUT Interface

Raspberry Control Pilot interface with System Under Test Device

The IEC 61851‐1 SUT adapter shall adapt the HAL 61851‐1 functions to a PWM Signal defined in 7.7.7.

The  parallel  test  component  (PTC)  for  IEC 61851‐1  signaling  continuously  observes  the  protocol
specific parameters positive voltage (state), frequency, duty  cycle and the proximity  resistor value in
accordance with the defined valid  range of values (as defined in IEC 61851‐1:2017, Annex A), during
the entire test case execution.

[V2G4-022] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a function to get
the current PWM state or associated voltage level.
- PWM status (on/off)
- Voltage level

[V2G4-023] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a call‐back
function which reports change events of the current PWM state or associated voltage
level.
- Event on PWM status state (on/off)
- Event on Voltage level change

[V2G4-024] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a function to set
the proximity on SUT side.
- Proximity status

[V2G4-025] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a function to get
the proximity resistor value from SUT side.

[V2G4-026] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a call‐back
function which reports change events of the resistor value for the proximity from SUT
side.

[V2G4-027] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a function to get
the duty cycle in [%].
- PWM Duty

[V2G4-028] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a call‐back
function which reports changes of the duty cycle in [%].
- Event on PWM Duty change

[V2G4-029] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a function to get
the frequency in [Hz].
- PWM frequency

[V2G4-030] The IEC 61851‐1 SUT adapter for SECC or EVCC testing shall provide a call‐back
function which reports change events of the frequency in [Hz].
- Event PWM frequency

[V2G4-031] The IEC 61851‐1 SUT adapter for SECC testing shall provide a function to set the
current PWM state or associated voltage level. State B, C and D or the associated
voltage level shall be supported, other voltage level are optional.