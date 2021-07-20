//
// Created by james on 19/10/2020.
//

#ifndef EVCC_CHARGINGSTATUSREQ_H
#define EVCC_CHARGINGSTATUSREQ_H

#include "../V2gExiMessage.h"

class ChargingStatusReq : public V2gExiMessage {
public:
    ChargingStatusReq();
    virtual ~ChargingStatusReq();
    void dumpMsg(void) override;
};


#endif //EVCC_CHARGINGSTATUSREQ_H
