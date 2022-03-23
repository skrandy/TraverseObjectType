#include<ntddk.h>
void traverseObjectType()
{
	/*
	author：SnA1lGo
	time:	2022/3/3
	作用：	遍历类型对象

	变量说明：
		FunctionName:			函数名称e
		FuncAddr:				函数地址
		ObTypeIndexTableAddr：	类型对象表首地址

	函数流程：
		首先获取ObGetObjectType函数地址，然后通过硬编码偏移15个字节后，取出四个字节的内容得到ObTypeIndexTable地址。
		然后将其作为数组处理。
	*/
	UNICODE_STRING FunctionName;
	PVOID FuncAddr;
	ULONG* ObTypeIndexTableAddr;//内核表的地址
	RtlInitUnicodeString(&FunctionName, L"ObGetObjectType");
	FuncAddr = MmGetSystemRoutineAddress(&FunctionName);
	if (!MmIsAddressValid(FuncAddr))
	{
		KdPrint(("函数地址获取失败\n"));
		return;
	}
	else
	{
		KdPrint(("函数地址%x\n", FuncAddr));
	}
	ObTypeIndexTableAddr = *(ULONG**)((char*)FuncAddr + 15);//先偏移15个字节再取四个字节的内容
	int i = 2;//从下标为2的地方开始
	while (ObTypeIndexTableAddr[i])
	{
		KdPrint(("%d %wZ : %x\n", i, ObTypeIndexTableAddr[i] + 8, ObTypeIndexTableAddr[i]));//遍历内核表
		i++;
	}
}


extern "C"
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
	traverseObjectType();
	return STATUS_SUCCESS;
}