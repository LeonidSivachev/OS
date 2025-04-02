/* 
 * Обработчики прерываний для x86 (синтаксис GAS)
 * Различие между исключениями с кодом ошибки и без
 */

.macro ISR_NOERR num
    .globl isr_stub_\num
    isr_stub_\num:
        pushl $0                     /* Пустой байт ошибки */
        pushl $\num                  /* Номер прерывания */
        call exception_handler
        addl $8, %esp                /* Очистка стека */
        iret
.endm

.macro ISR_ERR num
    .globl isr_stub_\num
    isr_stub_\num:
        /* Код ошибки уже в стеке процессором */
        pushl $\num                  /* Номер прерывания */
        call exception_handler
        addl $8, %esp                /* Очистка стека */
        iret
.endm

.extern exception_handler

/* Генерация обработчиков */
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_ERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_ERR 30
ISR_NOERR 31

/* Таблица указателей на обработчики */
.section .rodata
.globl isr_stub_table
isr_stub_table:
.int isr_stub_0, isr_stub_1, isr_stub_2, isr_stub_3
.int isr_stub_4, isr_stub_5, isr_stub_6, isr_stub_7
.int isr_stub_8, isr_stub_9, isr_stub_10, isr_stub_11
.int isr_stub_12, isr_stub_13, isr_stub_14, isr_stub_15
.int isr_stub_16, isr_stub_17, isr_stub_18, isr_stub_19
.int isr_stub_20, isr_stub_21, isr_stub_22, isr_stub_23
.int isr_stub_24, isr_stub_25, isr_stub_26, isr_stub_27
.int isr_stub_28, isr_stub_29, isr_stub_30, isr_stub_31