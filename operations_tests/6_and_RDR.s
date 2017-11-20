.name "and_RDR"
.comment "and"

	live %1
	st r1, 190
	st r2, 190
	and r1, %255, r2
	st r1, 300
	st r2, 300
