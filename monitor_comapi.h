#ifndef MONITOR_COMAPI_H
#define MONITOR_COMAPI_H

#include "comapi.h"

//此子类基于ComApi基类,是针对（双平台监视）通讯协议V1.1.2的通讯组包解包类
class CMonitor_Comapi:public ComApi
{
public:
	CMonitor_Comapi(unsigned char loginmodel);
	~CMonitor_Comapi();
	
	virtual int Make_Login(CBufferAccess &ba_all,char*charge_id,unsigned char charge_type,unsigned char charge_mode);
	virtual int Make_ChargeReq(CBufferAccess &ba_all,Charge_Order &chargeOrder,char*charge_id);

public:
	unsigned char mi_login_model;
};
#endif
