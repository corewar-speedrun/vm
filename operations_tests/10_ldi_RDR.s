.name "ldi_RDR"
.comment "ldi"

	live %1
	add r1, r1, r2
	st r1, 670
	st r2, 900
	ldi r2, %1, r2
	st r2, 950
