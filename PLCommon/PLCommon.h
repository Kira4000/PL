// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 PLCOMMON_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// PLCOMMON_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef PLCOMMON_EXPORTS
#define PLCOMMON_API __declspec(dllexport)
#else
#define PLCOMMON_API __declspec(dllimport)
#endif

#if 0
// 此类是从 PLCommon.dll 导出的
class PLCOMMON_API CPLCommon {
public:
	CPLCommon(void);
	// TODO:  在此添加您的方法。
};

extern PLCOMMON_API int nPLCommon;

PLCOMMON_API int fnPLCommon(void);
#endif

#pragma region MyType
typedef long long LLong;
typedef signed char INT8_pl;
typedef unsigned char UINT8_pl;
typedef signed int INT32_pl;
typedef unsigned int UINT32_pl;
#pragma endregion

PLCOMMON_API void PLCommon_Init(float cs, LLong bd, LLong dx);		//这里的底线是单个游戏的底线
PLCOMMON_API INT32_pl PLCommon_GetResult(LLong zy, LLong zd);
PLCOMMON_API bool IsHitTheEndline(LLong zy, LLong zd, LLong cur_round_yl);
