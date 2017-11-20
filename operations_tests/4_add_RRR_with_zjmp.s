.name "add_RRR_with_zjmp"
.comment "add"

	live %1
	st r1, 100
	ld %1, r1
	ld %-1, r2
	add r1, r2, r3
	st r3, 100
	zjmp %-15456
