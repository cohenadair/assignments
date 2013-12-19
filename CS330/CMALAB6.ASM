.model tiny
.stack
.code
.startup

; ***** put program instructions here *****

	; Setup the Line Control Register.
	mov dx,02FBh
	mov al,03h
	out dx,al

Start:  ; Check to see if there was input from the keyboard.
	mov ah,0Bh
	int 21h
	cmp al,00h      ; Checks if there's a character. If not, checks the
			; project.
	jz Proj
	mov ah,01h      ; Stores the key in al and prints it to the screen.
			; 01h is character input with echo.
	int 21h
	cmp al,40h      ; "@" symbol.
	mov bl,al
	jz Done         ; If the "@" key is pressed, terminate the program.
	call PRet       ; Print carriage return.

WaitEm: ; Wait until the Transmitter Buffer Empty and Transmitter Ready
	; flags are set.
	mov dx,02FDh
	in  al,dx
	and al,60h      ; Turn off all bits except 5 and 6.
	cmp al,60h
	jnz WaitEm

	; Send the data to the project.
	mov al,bl
	mov dx,02F8h
	out dx,al
	jmp Start       ; Go back to the start to get a new input.

Proj:   ; Check to see if data has been received.
	mov dx,02FDh
	in  al,dx
	and al,01h
	cmp al,01h
	jnz Start       ; Jump back to the start to check for another input.

	; Get the data from the data buffer.
	mov dx,02F8h
	in  al,dx
	mov bl,al

	; Get ready to print characters to the screen.
	mov ah,02h

	; Tab over three times
	mov cl,02h      ; Used for a counter.
PSpace: mov dl,09h      ; The tab key ASCii code.
	int 21h
	dec cl
	cmp cl,00h
	jnz PSpace      ; Loop until the "Tab" key's been pressed three times.

	; Print character.
	mov al,bl
	mov dl,al
	int 21h

	call PRet
	jmp Start       ; Done, jump back to the start.

PRet:   ; Prints a carriage return and new line to the screen.
	mov ah,02h
	mov dl,0Ah
	int 21h
	mov dl,0Dh
	int 21h
	ret

Done:   mov ah,02h ; Print the "@" symbol.
	mov dl,bl
	int 21h
	NOP

; *****************************************

	mov ax,4c00h ;quit
	int 21h
end

