#ifndef _YON_I18N_ENCODECONVERTOR_H_
#define _YON_I18N_ENCODECONVERTOR_H_

#include "yonString.h"

namespace yon{
namespace i18n{

	extern "C" YON_API class EncodeConvertor{
	private:
		EncodeConvertor();
		EncodeConvertor(const EncodeConvertor&);
		EncodeConvertor& operator = (const EncodeConvertor&);
	public:
		static EncodeConvertor& getInstance();

		core::stringc UTF8ToGB18030(const c8* str);
		core::stringc GB18030ToUTF8(const c8* str);
	};

}
}
#endif