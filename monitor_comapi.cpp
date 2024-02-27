#include "stdafx.h"
#include "monitor_comapi.h"

CMonitor_Comapi::CMonitor_Comapi(unsigned char loginmodel): ComApi()
{
	mi_login_model=loginmodel;
	if(mi_login_model>LOGIN_MODEL_ONLY_MONITOR)
		mi_login_model=LOGIN_MODEL_ALL;
	else
	   printf("mi_login_model=%d\n",mi_login_model);
}

CMonitor_Comapi::~CMonitor_Comapi()
{
  //析构函数
}

//登录的组包解包
int CMonitor_Comapi::Make_Login(CBufferAccess &ba_all,char*charge_id,unsigned char charge_type,unsigned char charge_mode)
{
	// 		起始标识	1Byte	BIN码	固定68H
	// 		帧长度	2Byte	BIN码	00 0BH
	// 		功能码	1Byte	BIN码	10H
	// 		设备编号	8Byte	压缩BCD码	充电设备编号   区域码4字节（地区编码3字节+充电桩类型1字节）+桩号4字节
	// 		充电桩类型	1Byte	BIN码	01交流桩  02 直流桩
	// 		充电模式支持	1Byte	BIN码	01 单充      02 双枪均充  03 双枪轮充  04 双枪混充 05 双枪合充
	
	//登录模式	1Byte	BIN码	0全业务类 1仅监视
	//桩通讯程序版本	3Byte	BCD	上送桩的通讯程序版本
	// 		校验位	1Byte	BIN码	功能码及数据域累加和
	// 		结束标识	1Byte	BIN码	固定16H

	CBufferAccess ba(frame_ByteSeq);
	ba.PutByte(Func_Login_REQ);

	//桩号
	//23630002 00000001
	PutBCD(ba,charge_id);

	//充电桩类型
	ba.PutByte(charge_type);
	//充电模式支持
	ba.PutByte(charge_mode);

	//登录模式	1Byte	BIN码	0全业务类 1仅监视
	ba.PutByte(mi_login_model);

	char ver[7]={0};
	sprintf(ver,Com_Version_112);
	PutBCD(ba,ver);

	return Make_Total_Packet(ba_all,ba);
}
