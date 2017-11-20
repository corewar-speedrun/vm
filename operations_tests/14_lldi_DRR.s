.name "lldi_DRR"
.comment "lldi"

	live %1
	add r1, r1, r2
	st r1, 700
	st r2, 900
	lldi %8, r1, r2
	st r2, 950
	zjmp %1783
