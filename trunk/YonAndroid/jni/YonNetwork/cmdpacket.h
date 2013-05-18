#ifndef _CMDPACKET_H_
#define _CMDPACKET_H_

#include "netconfig.h"

/* define default packet buffer size */
const int DEFAULT_CMD_PACKET_SIZE = 1024;
/* define max packet buffer size */
const int MAX_CMD_PACKET_SIZE	  = 1024 * 16;

/* define some length used in packet class */
const int BYTE_SIZE  = 1;
const int LONG_SIZE  = 4;
const int SHORT_SIZE = 2;
const int FLOAT_SIZE = 4;
const int LONG_LONG_SIZE  = 8;
const int WCHAR_SIZE = 2;		// !! Attention, sizeof(wchar_t) on android = 4

#include "CPacketMgr.h"
#include "basenetwork.h"

//封包类
//对网络流操作（读/写）的封装
//NOTE: 读/写操作注意字节序大小端
class CCmdPacket
{
private:
	SPacketBuffer* m_pBuffer;
	static io::IFileSystem* s_pFileSystem;
	io::IReadStream* m_pReadStream;
	core::array<core::stringc> inPlaces;

	bool ReadData(void *data,int len);
	bool WriteData(void *data,int len);
public:
	CCmdPacket();
	virtual ~CCmdPacket();

	static void setFileSystem(io::IFileSystem* fs);
	SPacketBuffer* getBuffer(){return m_pBuffer;}

	// 字符串采用UTF-8编码传输
	// 格式： | short | UTF8 string | '\0' | 
	//    即：一个short表示后面内容的长度+字符串本身+0结尾
	// 为了效率考虑，提供了一组读取函数，请注意使用说明。
	//
	// ReadString(char* pstr) 
	// - 用户自己提供字符串缓存，注意要提供足够大的缓存，避免越界
	// - 一般用于用户知道该字符串的最大长度，比如账号，密码最长16个字符。 
	//
	// ReadString(char** ppstr) 
	// - 用户不提供字符串缓存，由本函数内部申请，使用完毕后需要用户手动delete。
	// - 一般用于不知道该字符串的确切长度，往往是比较长的字符串。
	//
	// ReadStringInPlace(char** ppstr) 
	// - 用户不提供字符串缓存，本函数内部只是修改地址，也就是直接使用网络模块内部的缓存，
	// - 确保不要越界进行修改，否则可能导致网络模块崩溃。
	// - 重要： 该指针只在调用函数内有效，退出调用函数即失效。
	// - 该函数效率最高，不涉及任何运行时动态内存分配，唯一的要求是谨慎使用！

	bool ReadString(char* pstr);
	//bool ReadString(char** ppstr);//好像没用到
	bool ReadStringInPlace(char** ppstr);

	bool ReadFloat(float *f);
	bool ReadInt32(int *l);
	bool ReadLongLong(long long *ll);
	bool ReadShort(short *s);
	bool ReadByte(unsigned char *c);

	void BeginRead(char *p,int len);	//初始化读状态
	//void BeginRead();//only for emulate Server

	bool ReadBinary(char **data,int *len);

	void BeginWrite();

	bool WriteBinary(char *data,int len);
	// 写入0结尾的c字符串
	// 格式参考ReadString
	// 注意：结尾0字节不写入网络流
	bool WriteString(const char *str);

	bool WriteFloat(float f);
	bool WriteInt32(int l);
	bool WriteShort(short s);
	bool WriteByte(char c);

	char *GetData();
	int   GetDataSize();

	bool  SetSize(int len);
	//bool  CloneFrom(CCmdPacket *packet);//没有用到
};

#endif