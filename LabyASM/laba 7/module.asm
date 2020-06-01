.686
.model flat
.stack
public _IsWhiteSpace
public _TrimAll
.code

_IsWhiteSpace proc
	enter 0, 0;
	xor eax, eax;
	mov cl, byte ptr [ebp + 8];
	cmp cl, 32;
	mov edx, 1;
	cmove eax, edx
	leave;
	ret;
_IsWhiteSpace endp

_TrimAll proc
	enter 0, 0;
	mov edi, [ebp + 8];
	mov edx, [ebp + 12];

	begining:
	mov al, byte ptr [edi];
	push eax;
	call _IsWhiteSpace;
	test al, 1;
	jne end_part;
	xor ebx, ebx;
	deleting:
	cmp ebx, edx;
	je continue_deleting;
	push eax;
	mov al, byte ptr [edi + ebx + 1];
	mov byte ptr [edi + ebx], al;
	inc ebx;
	pop eax;
	jmp deleting;
	continue_deleting:
	dec edx;
	jmp begining;

	end_part:
	mov al, [edi + edx - 1];
	push eax;
	call _IsWHiteSpace;
	cmp al, 1;
	jne middle_part;
	mov byte ptr [edi + edx - 1], 0;
	dec edx;
	jmp end_part;


	middle_part:
	mov al, 32;

	mov ecx, -1;
	cld;
	repne scasb;
	neg ecx;
	sub ecx, 2;

	cmp ecx, edx;
	jg end_;
	continue_deleting_in_middle_part:
	mov al, byte ptr[edi];
	push eax;
	call _IsWhiteSpace;
	cmp al, 1;
	jne middle_part;
	mov esi, edx;
	sub esi, ecx;
	jmp deleting_from_string;


	nothing_end:
	mov eax, ecx;
	leave;
	ret;

	end_:
	mov edi, [ebp + 8];
	pop esi;
	mov eax, edx;
	leave;
	ret;

	deleting_from_string:
	xor ebx, ebx;
	continue_deleting_from_string:
	cmp ebx, edx;
	je dec_edx;
	push eax;
	mov al, byte ptr[edi + ebx + 1];
	mov byte ptr[edi + ebx], al;
	pop eax;
	inc ebx;
	jmp continue_deleting_from_string;
	dec_edx:
	dec edx;
	jmp continue_deleting_in_middle_part;

_TrimAll endp

end