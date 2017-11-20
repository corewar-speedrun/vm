.name "ldi_IRR"
.comment "ldi"

	live %1
	add r1, r1, r2
	st r1, 670
	st r2, 900
	ldi -600, r1, r2
	st r2, 950
