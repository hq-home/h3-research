//==================================================
// MYSEH - ��� ������ 1997
// Microsoft Systems Journal, ������ 1997
// FILE: MYSEH.CPP
// To compile: CL MYSEH.CPP
//==================================================
#define WIN32_LEAN_AND_MEAN
#include 
#include 

DWORD  scratch;

EXCEPTION_DISPOSITION
__cdecl
_except_handler(
    struct _EXCEPTION_RECORD *ExceptionRecord,
    void * EstablisherFrame,
    struct _CONTEXT *ContextRecord,
    void * DispatcherContext )
{
    unsigned i;

    // ��������, ��� �������� ��� ���������� ����������.
    printf( "Hello from an exception handler!\n" );

    // �������� �������� �������� EAX � context record ����� �������, ����� ���
    // ��������� �� �����-����, ��������� ��� ������ ����� � ������.
    ContextRecord->Eax = (DWORD)&scratch;

    // ������ �� ��� ��� ���������� ��������� ��������� ���������� ����������.
    return ExceptionContinueExecution;
}

int main()
{
    DWORD handler = (DWORD)_except_handler;

    __asm
    {                      // ������� ��������� EXCEPTION_REGISTRATION:
        push    handler    // ����� ������� ����������� ����������.
        push    FS:[0]     // ����� ����������� EXECEPTION_REGISTRATION.
        mov     FS:[0],ESP // ��������� � ��������� ������ EXECEPTION_REGISTRATION.
    }

    __asm
    {
        mov     eax,0      // �������� �������� �������� EAX.
        mov     [eax], 1   // ����� ������������� ������� ����������, ������ ������
                           // �� �������� ������.
    }

    printf( " After writing!\n" );

    __asm
    {                       // ������� �� ���������� ������ EXECEPTION_REGISTRATION.
        mov     eax,[ESP]   // �������� ��������� �� ����������
                            // EXECEPTION_REGISTRATION.
        mov     FS:[0], EAX // ������������� � ������ ������ ����������
                            // EXECEPTION_REGISTRATION.
        add     esp, 8      // ������� �� ����� ��������� EXECEPTION_REGISTRATION.
    }
    return 0;
}