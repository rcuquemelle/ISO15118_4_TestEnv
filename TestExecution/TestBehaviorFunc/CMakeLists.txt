project(TestBehaviorFunc_lib VERSION 1.0.0)

# file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")
set(src_files "./src/TB_SECC_V2GTP.cpp"
              "./src/TB_SECC_SDPMsg.cpp"
              "./src/TB_SECC_SupportedAppProtocol.cpp"
              "./src/TB_SECC_SessionSetup.cpp"
              "./src/TB_SECC_ServiceDiscovery.cpp"
              "./src/TB_SECC_ServiceDetail.cpp"
              "./src/TB_SECC_PaymentServiceSelection.cpp"
              "./src/TB_SECC_Authorization.cpp"
              "./src/TB_SECC_ChargeParameterDiscovery.cpp"
              "./src/TB_SECC_CableCheck.cpp"
              "./src/TB_SECC_PreCharge.cpp"
              "./src/TB_SECC_PowerDelivery.cpp"
              "./src/TB_SECC_CurrentDemand.cpp"
              "./src/TB_SECC_WeldingDetection.cpp"
              "./src/TB_SECC_SessionStop.cpp"
              "./src/TB_SECC_CertificateInstallation.cpp"
              "./src/TB_SECC_CertificateUpdate.cpp"
              "./src/TB_SECC_ChargingStatus.cpp"
              "./src/TB_SECC_MeteringReceipt.cpp"
              "./src/TB_SECC_PaymentDetails.cpp")

add_library(TestBehaviorFunc STATIC ${src_files})

target_include_directories(TestBehaviorFunc PUBLIC "./include")

target_link_libraries(TestBehaviorFunc
PUBLIC asio cppcommon fmt openv2g
  PUBLIC  DataType TCP UDP IEC61851If IFRuntime PlatformInterface Codecs
          Components TestManagement TestLogging ConfigurationFunc CmnFunc
          PostConditionFunc PreconditionFunc LibFunc)