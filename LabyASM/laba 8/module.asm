.686
.model flat
public _SortString
.stack
.code

_GetStringLength proc;
enter 0, 0;
push edi;
mov edi, [ebp + 8];
mov ecx, -1;
mov al, 0;
repne scasb;
neg ecx;
sub ecx, 2;
mov eax, ecx;
pop edi;
leave;
ret;
_GetStringLength endp;

_Prologue macro N;
enter N, 0;
endm;

_StoreCommonRegs macro;
push ebx;
push esi;
push edi;
endm;

_RestoreCommonRegs macro;
pop edi;
pop esi;
pop ebx;
endm;

_SwapToTheRight proc;
;repe cmpsb;
jl end_swapToTheRight;
mov esi, [edx + ebx*4];
mov edi, [edx + ebx*4 + 4];
mov [edx + ebx*4], edi;
mov [edx + ebx*4 + 4], esi;
end_swapToTheRight:
mov esi, [edx + ebx*4];
mov edi, [edx + ebx*4 + 4];
ret;
_SwapToTheRight endp

_SwapToTheLeft proc;
;repe cmpsb;
jg end_swapToTheRight;
mov esi, [edx + ebx*4 + 4];
mov edi, [edx + ebx*4];
mov [edx + ebx*4 + 4], edi;
mov [edx + ebx*4], esi;
end_swapToTheRight:
mov esi, [edx + ebx*4 + 4];
mov edi, [edx + ebx*4];
ret;
_SwapToTheLeft endp

_SortString proc;
_Prologue 0;
mov ecx, -1;
push ecx;
mov eax, [ebp + 8];
mov edx, [ebp + 12];
mov ebx, 0;
dec eax;

toTheRight:
cmp eax, 0;
je enddd_;
cmp ebx, eax;
je pre_toTheLeft;
mov esi, [edx + ebx*4];
mov edi, [edx + ebx*4 + 4];
call _SwapToTheRight;
inc ebx;
jmp toTheRight;

pre_toTheLeft:
dec eax;
jmp toTheLeft;

pre_toTheRight:
inc ecx;
push ecx;
dec eax;
jmp toTheRight;

toTheLeft:
cmp eax, 0;
je enddd_;
dec ebx;
pop ecx;
cmp ebx, ecx;
je pre_toTheRight;
push ecx;
mov esi, [edx + ebx*4 + 4];
mov edi, [edx + ebx*4];
call _SwapToTheLeft;
jmp toTheLeft;

enddd_:
pop ecx;
leave;
ret;
_SortString endp;

end