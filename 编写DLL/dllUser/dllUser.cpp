// dllUser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "wuygDll.h"
#include <iostream>
#include <windows.h>

#pragma comment(lib, "wuygDll")//用于隐式调用。要链接的导入库（.LIB files）。（生成 DLL 时链接器创建导入库。）

int _tmain(int argc, _TCHAR* argv[])
{
	//隐式调用
	wuygFun();
	
	//显式调用
	typedef int (__stdcall *Fun)(void); //定义函数指针类型
	HMODULE hDll = ::LoadLibrary(L"wuygDll");//加载DDL以及获取模块句柄

	/*因为使用了UNICODE字符集的原因，LoadLibrary实际是使用LoadLibraryW而非LoadLibraryA
而相应的，该函数所需要的参数应该为宽字符串（即UNICODE字符串）而非窄字符串(多字节字符串）。
在字符串方式中附加L前缀则可以变窄字符(串)为宽字符(串).*/

	Fun TestFun = ::GetProcAddress(hDll, "wuygFun");//获取指向应用程序要调用的导出函数的函数指针

	if (!TestFun)
	{
		// handle the error
		FreeLibrary(hDll);//如果指针获取错误则在退出之前必须卸载DLL(FreeLibrary)
		printf_s("ERROR!");
		system("pause");
		return 0;
	}
	else
	{
		// call the function
		TestFun();
		system("pause");
		return 0;
	}
}

