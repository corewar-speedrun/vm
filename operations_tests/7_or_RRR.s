.name "or_RRR"
.comment "or"

	live %1
	st r1, 192
	st r2, 192
	st r3, 192
	or r1, r2, r3
	st r1, 300
	st r2, 300
	st r3, 300
