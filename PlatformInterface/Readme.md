Timer and external function
define timer class for test execution (CfgTimer shall use these class
to config timeout condition in test operation)

performance times in ISO 15118‐2  are  irrelevant  since  they  are  not  visible  to  the  tester  (black  box  testing).  Hence  only
timeouts can be exactly measured from the tester's perspective and are considered


The timer handling in the test suite is defined as follows: Before sending a stimulus to the SUT the
corresponding message timer is started. After receiving the expected response from the SUT the
message timer will be stopped. In case no response is received from the SUT until the point in time
defined by the corresponding timeout value, the test verdict is set to 'false'

timer name  t_  Local timer  t_wait
timer name  tc_  Timer defined within a component  tc_authMin
The ISO 15118 test suite specific timer identifier is defined as:
[prefix]_[ctx]
The segments of this identifier are described in Table 24. An example for timer identifier is:
tc_V2G_EVCC_Msg_Timer
[prefix]    Type of timer (see Table 23)
[ctx]  {fullname}  Context (e.g. name of timer according to ISO 15118‐2 or if not part of the
standard any given name describing the context of the timer, e.g.
EVCC_SDP_Timer)

Class TimerManager:
  - separated async thread for running multiple timer
  - pass in timer name, return object for checking timeout and start/stop
  - call start timer -> asyn wait -> thread execute
Class Timer:
  - start
  - stop