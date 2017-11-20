.name "st_RI"
.comment "st"

	live %1
	ld %55, r2
	# st r2, 8714 ;(mod 4096%, mod %512 = 10)
	st r2, -8190 ;(mod 4096%, mod %512 = 510)
