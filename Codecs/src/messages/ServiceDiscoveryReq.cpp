
#include <string.h>
#include "messages/ServiceDiscoveryReq.h"

ServiceDiscoveryReq::ServiceDiscoveryReq() : V2gExiMessage(V2gExiMessage::V2G_MSG_SERVICE_DISCOVERY_REQ)
{
  init_iso1BodyType(&mExiData.V2G_Message.Body);
  mExiData.V2G_Message.Body.ServiceDiscoveryReq_isUsed = 1;
  init_iso1ServiceDiscoveryReqType(&mExiData.V2G_Message.Body.ServiceDiscoveryReq);
}

ServiceDiscoveryReq::~ServiceDiscoveryReq()
{
}

void ServiceDiscoveryReq::setServiceCategory(serviceCategoryType category)
{
  // enable ServiceCategory encode flag
  mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceCategory_isUsed = 1;
  mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceCategory = category;
  mServiceCategory = category;
}

serviceCategoryType ServiceDiscoveryReq::getServiceCategory()
{
  if (mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceCategory_isUsed == 1)
  {
    mServiceCategory = mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceCategory;
  }
  else
  {
    mServiceCategory = iso1serviceCategoryType_EVCharging;
  }
  return mServiceCategory;
}

void ServiceDiscoveryReq::setServiceScope(const std::string& scope)
{
  mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceScope_isUsed = 1;
  mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceScope.charactersLen = scope.length();
  memcpy((void *)mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceScope.characters, (void *)scope.c_str(), scope.length());
  mServiceScope = scope;
}

std::string& ServiceDiscoveryReq::getServiceCope()
{
  if (mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceScope_isUsed == 1)
  {
    mServiceScope = std::string(mExiData.V2G_Message.Body.ServiceDiscoveryReq.ServiceScope.characters);
  }
  else
  {
    mServiceScope = "";
  }
  return mServiceScope;
}

void ServiceDiscoveryReq::dumpMsg(void)
{
  std::string outstr = getHeaderStr();
  outstr.append(fmt::format("  ServiceScope={}\n", this->getServiceCope()));
  outstr.append(fmt::format("  ServiceCategory={}", SERVICE_CAT[this->getServiceCategory()]));
  Logging::info(LogMsgDump_ENABLE, outstr);
}