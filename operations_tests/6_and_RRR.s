.name "and_RRR"
.comment "and"

	live %1
	ld %255, r2
	st r1, 190
	st r2, 190
	st r3, 190
	and r1, r2,r3
	st r1, 300
	st r2, 300
	st r3, 300
