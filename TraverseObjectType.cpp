#include<ntddk.h>
void traverseObjectType()
{
	/*
	author��SnA1lGo
	time:	2022/3/3
	���ã�	�������Ͷ���

	����˵����
		FunctionName:			��������e
		FuncAddr:				������ַ
		ObTypeIndexTableAddr��	���Ͷ�����׵�ַ

	�������̣�
		���Ȼ�ȡObGetObjectType������ַ��Ȼ��ͨ��Ӳ����ƫ��15���ֽں�ȡ���ĸ��ֽڵ����ݵõ�ObTypeIndexTable��ַ��
		Ȼ������Ϊ���鴦��
	*/
	UNICODE_STRING FunctionName;
	PVOID FuncAddr;
	ULONG* ObTypeIndexTableAddr;//�ں˱�ĵ�ַ
	RtlInitUnicodeString(&FunctionName, L"ObGetObjectType");
	FuncAddr = MmGetSystemRoutineAddress(&FunctionName);
	if (!MmIsAddressValid(FuncAddr))
	{
		KdPrint(("������ַ��ȡʧ��\n"));
		return;
	}
	else
	{
		KdPrint(("������ַ%x\n", FuncAddr));
	}
	ObTypeIndexTableAddr = *(ULONG**)((char*)FuncAddr + 15);//��ƫ��15���ֽ���ȡ�ĸ��ֽڵ�����
	int i = 2;//���±�Ϊ2�ĵط���ʼ
	while (ObTypeIndexTableAddr[i])
	{
		KdPrint(("%d %wZ : %x\n", i, ObTypeIndexTableAddr[i] + 8, ObTypeIndexTableAddr[i]));//�����ں˱�
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