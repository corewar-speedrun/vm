.name		"overwrite_op"
.comment	"fjkl;j"

live %-1
fork: 	fork %-2
		ld %2, r2
		ld %2, r3
		ld %2, r4
		ld %2, r5
write: sti r1, %:fork, %-1
