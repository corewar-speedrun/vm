.name "lldi_RRR"
.comment "lldi"

	live %1
	st r2, 900
	st r1, 800
	st r3, 910
	lldi r3, r1, r2
	st r2, 950
	zjmp %1735
	