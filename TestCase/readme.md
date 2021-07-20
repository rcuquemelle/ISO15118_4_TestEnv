Annex E(normative)Test-case specifications for 15118-2 V2G application layer messages
Annex D(normative)Test-case specifications for 15118-2 SDP messages
Annex C(normative)Test-case specifications for 15118-2 V2GTP

test case definition
to test specific context - message, signal name according to standard
test case shall follow template:
Precondition
  - configuration : test component, port map, communication binding, pilot signal
  - bring SUT to valid & known state
test behavior
  - execute test behavior and analysis reaction of SUT -> verdict
Post condition
  - reset SUT to initial state

SYSTEM GLOBAL INIT:
  COMPONENTS AND PORTS
    RUNTIME (ASIO SERVICE)
    SYSTEM_SECCthis->stc component 61851, TCP, UDP, PORTS)
    SECC_TESTER(main test component create timer, verdict object)
  LOGGING SYSTEM


a)	 Initialize.
  1)	 Create	PTC	components.
  2)	 Map	all	MTC/PTC/system	ports	and	communication	bindings	according	to	the	underlying	test configuration.
b)	 Pre‐condition
The	test	system	is	supposed	to	start	in	a	state	so	that	a	communication	or	data	exchange	with	the
SUT	is	possible.	In	the	pre‐condition	of	a	test	case	the	tester	as	well	as	the	SUT	therefore	initialize
into	known	and	stable	state.	This	incorporates	the	following	action.
  1)	 Bring	SUT	and	tester	to	a	valid	and	known	state	before	the	actual	test	behavior	is	executed.
c)	 Test	behavior
The	 actual	test	behavior	defines	the	 set	of	 steps	during	the	test	 execution	which	 are	 essential	in
order	to	achieve	the	test	purpose	and	assign	verdicts	to	the	possible	outcomes.	This	involves	the
following	actions.
  1)	 Initialize	and	start	relevant	timer(s)	on	the	tester	side.
  2)	 Execute	test	behavior	(send	stimulus	to	the	SUT).
  3)	 Listen	to	any	events	and	verify	SUT	response	(stop	timers).
  4)	 Assign	test	verdict	for	this	test	behavior.
d)	 Post‐condition
  1)	 Bring	SUT	and	tester	into	final/initial	state.
e)	 Shutdown
  1)	 Unmap	all	connected	ports	&	communication	bindings.
  2)	 Shutdown	PTC	components.

Each test cases module = class
-> class constructor shall take environment(global) component during init
init required data/component then used in test case(method of class)
-> class shall be list of timer for communicationSetup timing, message monitor timing
-> verdict result data

global component for test cases
SECC_Tester
SystemSECC
log system

all other callled function by class method(test case) shall operate
on global data and class data (passed to)


ComponentsAndPorts: init SECC_Tester and SystemSECC
create Parallel test component
create verdict
