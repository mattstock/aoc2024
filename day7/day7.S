	.section ".rodata"
	.section ".bss"
	.section ".data"
	.section ".text"

consider:
	save %sp, -96, %sp
	
	ret
	restore
