#ifndef _YON_PLATFORM_ICALLBACK_H_
#define _YON_PLATFORM_ICALLBACK_H_

#include "yonTypes.h"

namespace yon{
namespace platform{

	//平台回调接口

	enum ENUM_CALLBACK_TYPE{
		ENUM_CALLBACK_TYPE_UI = 0,
		ENUM_CALLBACK_TYPE_HW,
		ENUM_CALLBACK_TYPE_COUNT
	};

	enum ENUM_CALLBACK_UI_TYPE{
		ENUM_CALLBACK_UI_TYPE_CONFIRM = 0,
		ENUM_CALLBACK_UI_TYPE_TOAST,
		ENUM_CALLBACK_UI_TYPE_EDITBOX,
		ENUM_CALLBACK_UI_TYPE_LOADING,
		ENUM_CALLBACK_UI_TYPE_COUNT
	};

	enum ENUM_CALLBACK_HW_TYPE{
		ENUM_CALLBACK_HW_TYPE_RAM_AVAIL = 0,
		ENUM_CALLBACK_HW_TYPE_RAM_TOTAL,
		ENUM_CALLBACK_HW_TYPE_COUNT
	};

	struct SCallbackUI{
		ENUM_CALLBACK_UI_TYPE type;
		bool visible;
		c8* title;
		c8* content;
		c8* positiveButton;
		c8* negativeButton;
	};

	struct SCallbackHW{
		ENUM_CALLBACK_HW_TYPE type;
	};

	struct SCallback{
		ENUM_CALLBACK_TYPE type;
		union{
			SCallbackUI ui;
			SCallbackHW hw;
		};
	};

	class ICallback{
	public:
		virtual bool callback(const platform::SCallback& cb) = 0;
	};
}
}
#endif