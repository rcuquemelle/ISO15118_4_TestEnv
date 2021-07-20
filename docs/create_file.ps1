$a = @("SupportedAppProtocol","SessionSetup", "ServiceDiscovery", "ServiceDetail",
 "PaymentServiceSelection","PaymentDetails","Authorization",
 "ChargeParameterDiscovery","PowerDelivery","CertificateUpdate",
  "CertificateInstallation", "SessionStop","ChargingStatus", "MeteringReceipt",
  "CableCheck", "PreCharge", "CurrentDemand", "WeldingDetection")
foreach ($i in $a){
    $h = "./include/TB_SECC_"+$i+".h"
    $s = "./src/TB_SECC_"+$i+".cpp"
    if ([System.IO.File]::Exists($h)) {
        rm $h
    }
    if ([System.IO.File]::Exists($s)) {
        rm $s
    }
    ni -ItemType File $h
    ni -ItemType File $s
$test=@"
#include "TB_SECC_$i.h"

TestBehavior_SECC_$i::TestBehavior_SECC_$i(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system)
  : mtc(_mtc), systemSECC(_system)
{

}

TestBehavior_SECC_$i::~TestBehavior_SECC_$i() {

}

"@
    Set-Content -Path $s -Value $test
$temp = $i.ToUpper();
$test=@"
#ifndef __TB_SECC_[REPLACE]_H__
#define __TB_SECC_[REPLACE]_H__

#include "MainTestComponent.h"
#include "ParallelTestComponent.h"

class TestBehavior_SECC_$i {
public:
  TestBehavior_SECC_$i(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_$i();

private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
};

#endif // __TB_SECC_[REPLACE]_H__

"@.Replace("[REPLACE]", $temp)
    Set-Content -Path $h -Value $test
}