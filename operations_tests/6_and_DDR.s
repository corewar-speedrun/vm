.name "and_DDR"
.comment "and"

	live %1
	st r1, 250
	and %1, %45, r1
	st r1, 300
	zjmp %1735
