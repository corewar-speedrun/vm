.name "xor_DRR"
.comment "xor"

	live %1
	st r1, 250
	st r2, 300
	xor %-815, r1, r2
	st r1, 350
	st r2, 400
