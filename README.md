# Anastasia Gosudarskaya

## Варіант № 5

```
1. <signal-program> --> <program>
2. <program> --> PROGRAM <procedure-identifier> ;
<block>.
3. <block> --> <declarations> BEGIN <statements-list> END
4. <statements-list> --> <empty>
5. <declarations> --> <constant-declarations>
6. <constant-declarations> --> CONST <constant-declarations-list> | <empty>
7. <constant-declarations-list> --> <constant-declaration> <constant-declarations-list> | <empty>
8. <constant-declaration> --> <constant-identifier> = <constant>;
9. <constant> --> <sign> <unsigned-constant>
10. <constant-identifier> --> <identifier>
11. <procedure-identifier> --> <identifier>
12. <identifier> --> <letter><string>
13. <string> --> <letter><string> | <digit><string> | <empty>
14. <unsigned-constant> --> <integer-part><fractional-part>
15. <integer-part> --> <unsigned-integer>
16. <fractional-part> --> #<sign><unsigned-integer> | <empty>
17. <unsigned-integer> --> <digit><digits-string>
18. <digits-string> --> <digit><digits-string> | <empty>
19. <sign> --> + | - | <empty>
20. <digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
21. <letter> --> A | B | C | D | ... | Z
```
