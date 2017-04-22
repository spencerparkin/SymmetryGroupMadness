# Puzzle5Generators.py

matrix = []
rows = 8
cols = 10

for i in range( rows ):
    matrix_col = []
    for j in range( cols ):
        matrix_col.append({})
    matrix.append( matrix_col )
    
for i in range( rows ):
    for j in range( cols ):
        entry = matrix[i][j]
        entry[ 'used' ] = True
        if i < 2 and j < 4:
            entry[ 'used' ] = False
        elif i >= 6 and j >= 6:
            entry[ 'used' ] = False
            
number = 0
for i in range( rows ):
    for j in range( cols ):
        entry = matrix[i][j]
        if entry[ 'used' ]:
            entry[ 'number' ] = number
            number += 1

def PrintGenerator( row, col, label, transform ):
    print( '' )
    print( 'Permutation %s;' % label )
    print( '%s.DefineIdentity();' % label )
    for i in range(6):
        for j in range(6):
            entry = matrix[ row + i ][ col + j ]
            number = entry[ 'number' ]
            x, y = transform( i, j )
            other_entry = matrix[ row + x ][ col + y ]
            other_number = other_entry[ 'number' ]
            if number != other_number:
                print( '%s.Define( %d, %d );' % ( label, number, other_number ) )

def ReflectDiagonal( i, j ):
    return j, i

def ReflectOtherDiagonal( i, j ):
    return 5 - j, 5 - i

def ReflectVertical( i, j ):
    return i, 5 - j

def ReflectHorizontal( i, j ):
    return 5 - i, j

def RotateCCW( i, j ):
    i, j = ReflectDiagonal( i, j )
    i, j = ReflectHorizontal( i, j )
    return i, j
    
PrintGenerator( 0, 4, 'permR0', RotateCCW )
PrintGenerator( 0, 4, 'permD0p', ReflectOtherDiagonal )
PrintGenerator( 0, 4, 'permV0', ReflectVertical )
PrintGenerator( 0, 4, 'permD0', ReflectDiagonal )
PrintGenerator( 0, 4, 'permH0', ReflectHorizontal )

PrintGenerator( 2, 0, 'permR1', RotateCCW )
PrintGenerator( 2, 0, 'permD1p', ReflectOtherDiagonal )
PrintGenerator( 2, 0, 'permV1', ReflectVertical )
PrintGenerator( 2, 0, 'permD1', ReflectDiagonal )
PrintGenerator( 2, 0, 'permH1', ReflectHorizontal )
                
# Puzzle5Generators.py