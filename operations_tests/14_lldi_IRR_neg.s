.name "lldi_IRR"
.comment "lldi"

	live %1
	add r1, r1, r2
	st r1, 670
	st r2, 900
	lldi -600, r1, r2
	st r2, 950
	zjmp %1783
	
