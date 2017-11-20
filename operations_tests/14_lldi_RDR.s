.name "lldi_RDR"
.comment "lldi"

	live %1
	add r1, r1, r2
	st r1, 670
	st r2, 900
	lldi r2, %1, r2
	st r2, 950
	zjmp %1735
