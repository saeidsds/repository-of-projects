#ifndef __PACKET_MGR_H__
#define __PACKET_MGR_H__

class CGameNetwork;

class CPacketMgr : public CSingleton<CPacketMgr>
{
public:
	CPacketMgr()	{}
	~CPacketMgr()	{}

	void init(CGameNetwork* network)	{ s_mGameNetwork = network;	}

private:
	static inline void sendPacket()
	{	s_mGameNetwork->SendPacket(s_mCmdPacket);	}

	static inline void beginWrite()	
	{	s_mCmdPacket.BeginWrite();		}

	static inline void writeString(const char *str)	
	{	s_mCmdPacket.WriteString(str);	}

	static inline void writeByte(char c)	
	{	s_mCmdPacket.WriteByte(c);		}

	static inline void writeShort(short s)	
	{	s_mCmdPacket.WriteShort(s);		}

	static inline void writeInt32(int l)	
	{	s_mCmdPacket.WriteInt32(l);		}

#ifdef WIN32
	static unsigned int WINAPI SenderThread( void* lpData );
#else
	static void* SenderThread( void* data );
#endif
	static bool		sSenderThreadExit;

	// 封包发送函数
public:
	void Init();

	//登录
	static void sendC2SLoginPacket(const char* account, const char* password, const char* lianMeng, const char* ua);

	static void sendC2SRegisterPacket(const char* account, const char* password,int type);
	//请求角色列表
	static void sendC2SPlayerListReqPacket(char* serverKey);

	//选择角色进入游戏
	static void sendC2SEnterGamePacket(char* charKey);

	//创建角色
	static void sendC2SCreateRolePacket(const char* name, int jobId, int sex,bool isVisitor);

	//删除角色
	static void sendC2SDeleteRolePacket(char* charKey);

	//技能树升级
	static void sendC2SUpSkillLevel(int skillID);

	//使用技能
	static void sendC2SAttack(int uuid, int skillID);

	//使用技能
	static void sendC2SPreAttack(int uuid, int skillID);

	//坐标同步
	static void sendC2SLocation(int posX, int posY);

	//坐标改变(摇杆)
	static void sendC2SLocationList(xc::core::array<xc::core::vector2df>& pos);

	//坐标改变(寻路)
	static void sendC2SMoveTo(xc::core::array<xc::core::vector2df>& pos);

	//npc对话
	static void sendC2STalk2NPC(int uuid, int contextType, int taskId);

	//采集
	static void sendC2SCollect(int type, int uuid);

	//地图加载完成
	static void sendC2SMapLoadComplete();

	//技能树保存
	static void sendC2SSkillSave(int which);

	//技能树载入
	static void sendC2SSkillLoad(int which);

	//技能树重置
	static void sendC2SSkillReset();

	//改变杀戮/工会/和平模式
	static void sendC2SChangeAttackType(int attackType);

	//
	// cmd命令协议
	//
	// strCmd - 必须是utf-8编码
	static void sendC2SCmd(const char* strCmd);
	static void sendC2SCmd(std::string& strCmd);
	// strCmd - UString对象
	static void sendC2SCmd(const MyGUI::UString& strCmd);

	static void sendC2SItemInfo(int uuid, int itemServerId);

	//邮件操作
	static void sendEmailInfoC2S(const MyGUI::UString &s_name,unsigned int s_uuid,const MyGUI::UString &s_title,const MyGUI::UString &s_info,int s_money,
		unsigned int s_things_one,unsigned char s_number_one,	
		unsigned int s_things_two,unsigned char s_number_two,
		unsigned int s_things_three,unsigned char s_number_three);
	//聊天
	static void sendC2SSendChatMsg(const MyGUI::UString& srolename, int chattype, const MyGUI::UString& chatontent);

	static void sendC2SSendSomeMessage(void);

	static void sendC2SHonourUpdate(short id);

	//请求地图怪物列表
	void sendC2SMapActor(int mapID);

	//请求地图队友列表
	void sendC2STeamMates(int mapID);

	//请求寻路数据
	void sendC2SPathFinding(int mapDestID,int npcID,int DestX, int DestY);

	bool IsSenderThreadExit()	{ return sSenderThreadExit; }


private:
	static CGameNetwork*	s_mGameNetwork;		//保存CGameNetwork的引用，以便代码更加简洁
	static CCmdPacket		s_mCmdPacket;		//共享变量，被所有发包方法使用

};

#define GetPacketMgr()		CPacketMgr::GetInstance()

#endif