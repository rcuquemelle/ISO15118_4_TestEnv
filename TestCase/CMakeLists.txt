project(TestCase_lib VERSION 1.0.0)

set(src_files "./src/V2GSDP.cpp"
              "./src/V2GTPSecc.cpp"
              "./src/V2GAppSECCSupportedAppProtocol.cpp"
              "./src/V2GAppSECCSessionSetup.cpp"
              "./src/V2GAppSECCServiceDiscovery.cpp"
              "./src/V2GAppSECCServiceDetail.cpp"
              "./src/V2GAppSECCPaymentServiceSelection.cpp"
              "./src/V2GAppSECCAuthorization.cpp"
              "./src/V2GAppSECCChargeParameterDiscovery.cpp"
              "./src/V2GAppSECCCableCheck.cpp"
              "./src/V2GAppSECCPreCharge.cpp"
              "./src/V2GAppSECCPowerDelivery.cpp"
              "./src/V2GAppSECCCurrentDemand.cpp"
              "./src/V2GAppSECCWeldingDetection.cpp"
              "./src/V2GAppSECCSessionStop.cpp"
              "./src/V2GAppSECCCertificateInstallation.cpp"
              "./src/V2GAppSECCCertificateUpdate.cpp"
              "./src/V2GAppSECCChargingStatus.cpp"
              "./src/V2GAppSECCMeteringReceipt.cpp"
              "./src/V2GAppSECCPaymentDetails.cpp")

# file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(TestCase OBJECT ${src_files})

target_include_directories(TestCase PUBLIC "./include")

target_link_libraries(TestCase
  PUBLIC DataType TestLogging
        CmnFunc ConfigurationFunc PostConditionFunc PreconditionFunc
        TestBehaviorFunc TestManagement)