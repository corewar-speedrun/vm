.name "xor_RIR"
.comment "xor"

	live %1
	st r1, 190
	st r2, 190	
	xor r1, -8512, r2
	st r1, 300
	st r2, 300
