.name "ld_DR"
.comment "alive"

l2:		sti r2, %0, %1
		ld 1, r2
		st r2, r6
		st r6, 900


live:	live %1
		ld %2, r4
		st r4, r5
		zjmp %:live
		