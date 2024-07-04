section .text
global isr_stub0, isr_stub1, isr_stub2, isr_stub3, isr_stub4, isr_stub5, isr_stub6, isr_stub7
global isr_stub8, isr_stub9, isr_stub10, isr_stub11, isr_stub12, isr_stub13, isr_stub14, isr_stub15
global isr_stub16, isr_stub17, isr_stub18, isr_stub19, isr_stub20, isr_stub21, isr_stub22, isr_stub23
global isr_stub24, isr_stub25, isr_stub26, isr_stub27, isr_stub28, isr_stub29, isr_stub30, isr_stub31

%macro isr_err_stub 1
isr_stub%+%1:
    call exception_handler
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub%+%1:
    call exception_handler
    iret
%endmacro

extern exception_handler

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

section .data
global isr_stub_table
isr_stub_table:
    dd isr_stub0, isr_stub1, isr_stub2, isr_stub3
    dd isr_stub4, isr_stub5, isr_stub6, isr_stub7
    dd isr_stub8, isr_stub9, isr_stub10, isr_stub11
    dd isr_stub12, isr_stub13, isr_stub14, isr_stub15
    dd isr_stub16, isr_stub17, isr_stub18, isr_stub19
    dd isr_stub20, isr_stub21, isr_stub22, isr_stub23
    dd isr_stub24, isr_stub25, isr_stub26, isr_stub27
    dd isr_stub28, isr_stub29, isr_stub30, isr_stub31
