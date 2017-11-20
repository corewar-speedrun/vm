.name "sti_RRR"
.comment "sti"

	live %1
	ld %20, r1
	st r1, 190
	ld %255, r2
	st r2, 190
	ld %1, r3
	st r3, 190
	sti r3, r1, r2
