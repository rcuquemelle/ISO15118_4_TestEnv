ComponentsAndPorts definition

PORT = queue in components


COMPONENTS = MAIN TEST COMPONENT      :: mapping to SystemPort queue.
             PARALLEL TEST COMPONENT  :: handling monitoring/verifying parallel test operation(BasicSignalling)

SYSTEM COMPONENTS :: handling TCP/UDP/BasicSignalling

Main test component, System test component create 1 time
passed to multiple class tc