#!/bin/bash
while true; do
  echo "EXECUTE DC-AGING TEST "
  /home/pi/hlc/build/TestSuite/DC_SECC_Charging_Control D
  echo "----END----"
donew