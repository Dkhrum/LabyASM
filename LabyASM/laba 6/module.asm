.686
.model flat
.stack
public _StrIndex
.code
	_StrIndex proc
	push ebp;
	mov ebp, esp;
	mov ecx, -1;

	mov al, 0;
	mov edi, [ebp + 8];
	
	cld;
	repne scasb;
	je found_1;

	found_1:
	neg ecx;
	sub ecx, 2;
	mov edx, ecx;

	mov ecx, -1;
	push edi;
	mov edi, [ebp + 12];
	
	cld;
	repne scasb;
	je found_2;

	found_2:
	neg ecx;
	sub ecx, 2;
	pop edi;
	mov esi, [ebp + 12];
	mov edi, [ebp + 8];
	

	next_step:
	mov ebx, ecx;
	mov eax, 1;
	looop_continue:
	cmp edx, 0;
	je end_1;
	push eax;
	mov al, byte ptr [esi + ebx - 1];
	cmp al, byte ptr [edi + edx - 1];
	jne looop;
	pop eax;
	dec edx;
	dec ebx;
	inc eax;
	cmp eax, ecx;
	je end_2;
	jmp looop_continue;

	looop:
	pop eax;
	dec edx;
	jmp next_step;

	end_1:
	mov eax, -1;
	pop ebp;
	ret
	end_2:
	mov eax, edx;
	sub eax, 1;
	pop ebp;
	ret

_StrIndex endp

end