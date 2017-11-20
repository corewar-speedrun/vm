.name "ldi_RRR"
.comment "ldi"

	live %1
	add r1, r1, r2
	st r2, 900
	st r1, 800
	ldi r2, r1, r2
	st r2, 950
