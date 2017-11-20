.name "ldi_IDR"
.comment "ldi"

	live %1
	st r1, 741
	add r1, r1, r2
	st r2, 900
	ldi 529, %5, r2
	st r2, 950
