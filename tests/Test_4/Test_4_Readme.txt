This Test checks a scenario when "mov" inst is written with a single operand 
("mov" instruction works only with 2 operands).

Expected result:

Valid "am.file"  - V
Indication Error - V (Terminal)

"ent.file"       - X
"ext.file"       - X
"ob.file"        - X

Actual result:

All pass - V