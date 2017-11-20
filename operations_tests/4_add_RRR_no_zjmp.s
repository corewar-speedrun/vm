.name "add_RRR_no_zjmp"
.comment "add"

	live %1
	st r2, 100
	st r1, 100
	st r3, 100
	add r1, r1, r3
	st r3, 100
	zjmp %165489
