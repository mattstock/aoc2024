	.section ".rodata"
	.section ".bss"
	.section ".data"
	.section ".text"

	.global coord2pos
	! %i0 - x
	! %i1 - y
	! return pos
coord2pos:
	save %sp, -176, %sp

	set cols, %l0
	ld [%l0], %l0
	inc %l0  ! for the newline
	! integer division is rows
	mulx %i1, %l0, %l0
	add %l0, %i0, %i0
	ret
	restore

	.global pos2coord
	! %i0 - pos
	! %i1 - ptr to x
	! %i2 - ptr to y
pos2coord:
	save %sp, -176, %sp

	set cols, %l0
	ld [%l0], %l0
	inc %l0

	udivx %i0, %l0, %l1
	st %l1, [%i2]
	mulx %l0, %l1, %l2
	sub %i0, %l2, %l2
	st %l2, [%i1]
	ret
	restore

	! %i0 - pos
	! %i1 - val (char)
	! return score
!yodel:	
!	save %sp, -176, %sp

	

	
!	ret
!	restore
