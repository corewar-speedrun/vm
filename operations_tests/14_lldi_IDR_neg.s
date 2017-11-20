.name "lldi_IDR"
.comment "lldi"

	live %1
	add r1, r1, r2
	st r2, 900
	lldi -522, %5, r2
	st r2, 950
	zjmp %1783
	