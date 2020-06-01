.686
.model flat
.stack
.code

_IntegrateCotan proc
FINIT;
FILD dword ptr[esp + 4];
MOV ecx, dword ptr[esp + 4];
MOV ebx, 4;
dec ecx;
PUSH ebx;
FILD dword ptr[esp];
POP ebx;
FMUL ST, ST(1);
FXCH ST(1);
FFREE ST(0);
FINCSTP;
FLDPI;
FDIV ST, ST(1);
FXCH ST(1);
FFREE ST(0);
FINCSTP;
FLDPI;
MOV ebx, 4;
PUSH ebx;
FILD dword ptr[esp];
POP ebx;
FDIVP ST(1), ST;
FLD ST;
FPTAN;
FDIV ST, ST(1);
FXCH ST(1);
FFREE ST(0);
FINCSTP;
MOV ebx, 2;
PUSH ebx;
FILD dword ptr[esp];
POP ebx;
FDIVP ST(1), ST;
FXCH ST(1);

looop:
FADD ST, ST(2);
FLD ST;
FPTAN;
FDIV ST, ST(1);
FXCH ST(1);
FFREE ST(0);
FINCSTP;
FADD ST, ST(2);
FXCH ST(2);
FFREE ST;
FINCSTP;
loop looop;

FXCH ST(1);
FMUL ST, ST(2);
FSTP dword ptr[esp + 4];
MOV eax, dword ptr[esp + 4];
RET;
_IntegrateCotan endp

end