.name "ldi_DRR"
.comment "ldi"

	live %1
	add r1, r1, r2
	st r1, 700
	st r2, 900
	ldi %8, r1, r2
	st r2, 950
