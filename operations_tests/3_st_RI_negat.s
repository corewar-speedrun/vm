.name "st_RI_negat"
.comment "st"

	live %1
	ld %55, r2
	st r2, 65503;(mod 4098%, mod %512 = -33)
	# st r2, -1
	# st r1, 800
