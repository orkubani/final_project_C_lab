MAIN:   mov @r3 ,LENGTH
LOOP:   jmp L1
        mcro m1 
            sub @r1, @r4
            bne END
        endmcro
; just a comment
        mcro m2
            test1
            test2
        endmcro        
        prn -5
        bne LOOP
        m1
L1:     inc K
        bne LOOP
        m2
END:    stop



STR:    .string “abcdef”
LENGTH: .data 6,-9,15
K:      .data 22