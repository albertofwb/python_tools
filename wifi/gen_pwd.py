prefix = [
"workhard", "hello", "helloworld", "xaut"
]

magic_digits = [ 748, 666, 123, 1234, 4321 ]
special_char = [".", "..", "...", "?" ]

for p in prefix:
    for d in magic_digits:
        for c in special_char:
            print "%s%d%s" %(p, d, c)
