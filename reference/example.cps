# example.cps

# Instructions are on a single line
# Anything that starts with a '#' is a comment

# Valid syntax is:
# "<name> = <type_of_Shape> <Args...>"
# where Args is in the same order as specified in the documentation

a = circle 80.0
b = scaled a 0.2 1.0
c = horizontal b b b
d = spacer 40.0 40.0
e = vertical c d c
f = rotated e 20.0
output f