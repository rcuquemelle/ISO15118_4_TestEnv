TestProfiles:
  - CfgPICS: enumerations (Annex A(normative)Configuration specifications)
  - CfgPIXIT: enumerations (Annex A(normative)Configuration specifications)
  - CfgTimer: constant timer for timeout condition of each message (Annex A(normative)Configuration specifications)

TestSystem:
  -  MainTestComponent:
  -  ParallelTestComponent:
  -  SystemTestComponent:
  -  PortType:


import from Services_HAL_61851 all;
import from ComponentsAndPorts all;

global resource for test environment:
Services_HAL_61851: create 61851 service
ComponentsAndPorts: create Component and Ports

these 2 component need to be created and pass to TestCase and TestSuite(pass to testcase under it)
test case shall operate on these component