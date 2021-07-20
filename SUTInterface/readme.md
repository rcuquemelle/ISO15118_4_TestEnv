system under test interface
test framework communication with SUT shall be carry out by IEC61851 Interface(control pilot)
ISO15118 Interface (TCP layer, TLS layer(encryption with Plug&Charge), UDP (SECC Discovery Protocol))

SUTRuntime: shall be provide runtime environment for HLC and Basic Signaling Interface component
runtime environment: i.e. threading and io execution context

TestFramework (test preconditon - init function):
Create main test component, parallel test component, system test component

System test component -> Initialize SUTRuntime before any Interface usage, runtime init shall return
io execution context to be use in initialize SUT If(SUT If object shall refer the io_service(io_context) from SUTRuntime), mapping SUTIf to component port queue.

- propagate message  requests and procedure based calls from the Test Execution to the SUT
- notify the Test Execution of any received test events by appending them to its port queues.
- send/receive the encoded SDP requests/responses through UDP
- send/receive the encoded V2G messages through a TCP