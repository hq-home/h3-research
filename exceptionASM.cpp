//==================================================
// MYSEH - Мэт Питрек 1997
// Microsoft Systems Journal, Январь 1997
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

    // Сообщаем, что сработал наш обработчик исключений.
    printf( "Hello from an exception handler!\n" );

    // Изменяем значение регистра EAX в context record таким образом, чтобы оно
    // указывало на какое-либо, доступное для записи место в памяти.
    ContextRecord->Eax = (DWORD)&scratch;

    // Просим ОС еще раз попытаться выполнить вызвавшую исключение инструкцию.
    return ExceptionContinueExecution;
}

int main()
{
    DWORD handler = (DWORD)_except_handler;

    __asm
    {                      // Создаем структуру EXCEPTION_REGISTRATION:
        push    handler    // Адрес функции обработчика исключений.
        push    FS:[0]     // Адрес предыдущего EXECEPTION_REGISTRATION.
        mov     FS:[0],ESP // Добавляем в связанный список EXECEPTION_REGISTRATION.
    }

    __asm
    {
        mov     eax,0      // Обнуляем значение регистра EAX.
        mov     [eax], 1   // Чтобы преднамеренно вызвать исключение, делаем запись
                           // по нулевому адресу.
    }

    printf( " After writing!\n" );

    __asm
    {                       // Удаляем из связанного списка EXECEPTION_REGISTRATION.
        mov     eax,[ESP]   // Получаем указатель на предыдущий
                            // EXECEPTION_REGISTRATION.
        mov     FS:[0], EAX // Устанавливаем в начале списка предыдущий
                            // EXECEPTION_REGISTRATION.
        add     esp, 8      // Удаляем из стека структуру EXECEPTION_REGISTRATION.
    }
    return 0;
}