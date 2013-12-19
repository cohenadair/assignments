.model tiny
.stack
.code
.startup

; ***** put program instructions here *****

mov cx,98cah
mov dx,6755h

stc
mov ax,cx
add ax,dx

stc
mov ax,cx
adc ax,dx

stc
mov ax,cx
sub ax,dx

stc
mov ax,cx
sbb ax,dx

mov ax,dx
sub ax,cx

mov ax,cx
cmp ax,dx

mov ax,dx
cmp ax,cx
cmp ax,ax
stc
mov ax,cx
or ax,dx

mov ax,cx
and ax,dx

mov al,cl
and al,dl

stc
mov ax,cx
xor ax,dx

mov ax,00F0h
clc
rol al,1
clc
rcl al,1
shl al,1

mov al,0F0h
stc
ror al,1
stc
rcr al,1
sar al,1
sar al,1
shr al,1

; *****************************************

	mov ax,4c00h ;quit
	int 21h
end
