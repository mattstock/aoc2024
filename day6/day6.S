	! For this project, I'm using SPARC assembly.  That said, I will
	! be leveraging some of the C functions available on the platform
	! to avoid some of the scaffolding grunge like file access
	! and memory allocation.

	
	.section ".rodata"
	
argerr:	.asciz "day6 <inputfile>"

map:	.asciz	"....#.....",
		".........#",
		"..........",
		"..#.......",
		".......#..",
		"..........",
		".#..^.....",
		"........#.",
		"#.........",
		"......#..."
col:	.byte	10
	
	.section ".text"

	! %i0 is argc
	! %i1 is argv
	.align 4
	.global main
main:
	save %sp, -96, %sp
	cmp %i0, 2
	bne .args
	nop
	mov %i1, %l0
	add %l0, 4, %l0
	! open(argv[1], 0)
	ld [%l0], %o0
	mov 0, %o1
	call open
	nop
	! %i0 has the file descriptor
	call close
	nop
	ba .exit
	nop
.args:
	set argerr, %o0
	call puts, 0
	nop
.exit:
	mov 0, %i0
	ret
	restore
	
