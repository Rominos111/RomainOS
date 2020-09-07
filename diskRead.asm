; 512 bytes apres 0x7c00
PROGRAM_SPACE equ 0x7e00

readDisk:
    ; Configure le bus pour lire le disque
    mov ah, 0x02

    ; Pour que le BIOS sache où mettre la data en mémoire
    mov bx, PROGRAM_SPACE

    ; Nombre de secteurs du disque virtuel, ici 4*512 = 2048 bytes
    mov al, 4

    ; Quel disque choisir
    mov dl, [BOOT_DISK]

    ; Cylindre num 0 (hard drive)
    mov ch, 0x00

    ; Head num 0 (hard drive)
    mov dh, 0x00

    ; Lecture à partir du 2e secteur, le 1er étant le boot sector
    mov cl, 0x02

    ; Interruption BIOS pour lire
    int 0x13

    ; Jmp if carry set (= erreur disque)
    jc diskReadError

    ret

diskReadErrorString:
    db "Disk read failed", 0

diskReadError:
    mov bx, diskReadErrorString
    call printString
    ; Boucle infinie parce que erreur de toute façon
    jmp $

BOOT_DISK:
    db 0