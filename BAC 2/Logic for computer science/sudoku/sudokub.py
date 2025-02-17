#!/usr/bin/python3

import sys
import subprocess
#####
import time
import random
#####

# Saves the start time
start_time = time.time()

# reads a sudoku from file
# columns are separated by |, lines by newlines
# Example of a 4x4 sudoku:
# |1| | | |
# | | | |3|
# | | |2| |
# | |2| | |
# spaces and empty lines are ignored
def sudoku_read(filename):
    myfile = open(filename, 'r')
    sudoku = []
    N = 0
    for line in myfile:
        line = line.replace(" ", "")
        if line == "":
            continue
        line = line.split("|")
        if line[0] != '':
            exit("illegal input: every line should start with |\n")
        line = line[1:]
        if line.pop() != '\n':
            exit("illegal input\n")
        if N == 0:
            N = len(line)
            if N != 4 and N != 9 and N != 16 and N != 25:
                exit("illegal input: only size 4, 9, 16 and 25 are supported\n")
        elif N != len(line):
            exit("illegal input: number of columns not invariant\n")
        line = [int(x) if x != '' and int(x) >= 0 and int(x) <= N else 0 for x in line]
        sudoku += [line]
    return sudoku

# print sudoku on stdout
def sudoku_print(myfile, sudoku):
    if sudoku == []:
        myfile.write("impossible sudoku\n")
    N = len(sudoku)
    for line in sudoku:
        myfile.write("|")
        for number in line:
            if N > 9 and number < 10:
                myfile.write(" ")
            myfile.write(" " if number == 0 else str(number))
            myfile.write("|")
        myfile.write("\n")

# get number of constraints for sudoku
def sudoku_constraints_number(sudoku):
    N = len(sudoku)
    # Calculate the number of constraints for each type of constraint
    count = 0

    # Constraint 1: One number per cell
    # For each cell, you generate N clauses (one for each number)
    count += N * N

    # Constraint 2: At least one number in each cell
    # You've already counted N*N clauses for this in Constraint 1

    # Constraint 3: No two same numbers in a column
    # For each column and each number, generate clauses to ensure no two cells in that column have the same number
    count += N * N * N * (N - 1) // 2

    # Constraint 4: No two same numbers in a row
    # For each row and each number, generate clauses to ensure no two cells in that row have the same number
    count += N * N * N * (N - 1) // 2

    # Constraint 5: No two same numbers in each square of size sqrt(N) x sqrt(N)
    count += (N * N * (N - 1) // 2) * N

    return count




# prints the generic constraints for sudoku of size N
def sudoku_generic_constraints(myfile, N):
    def output(s):
        myfile.write(s)

    def newlit(i, j, k):
        if(N == 4 or N == 9):
            return str(i) + str(j) + str(k) + " "
        else:
            return str(i).zfill(2) + str(j).zfill(2) + str(k).zfill(2) + " "

    def newcl():
        output("0\n")

    if N == 4:
        n = 2
    elif N == 9:
        n = 3
    elif N == 16:
        n = 4
    elif N == 25:
        n = 5
    else:
        exit("Only supports size 4, 9, 16, and 25")

    # Constraint 1: At least one number per cell
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            output(" ".join(newlit(i, j, k) for k in range(1, N + 1)))
            newcl()

    # Constraint 2: One number per cell
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            for k in range(1, N + 1):
                for l in range(k + 1, N + 1):
                    output(f"-{newlit(i, j, k)}-{newlit(i, j, l)}")
                    newcl()

    # Constraint 3: One number per row
    for i in range(1, N + 1):
        for k in range(1, N + 1):
            for j in range(1, N):
                for l in range(j + 1, N + 1):
                    output(f"-{newlit(i, j, k)}-{newlit(i, l, k)}")
                    newcl()

    # Constraint 4: One number per column
    for j in range(1, N + 1):
        for k in range(1, N + 1):
            for i in range(1, N):
                for l in range(i + 1, N + 1):
                    output(f"-{newlit(i, j, k)}-{newlit(l, j, k)}")
                    newcl()

    # Contraints 5: Not 2 same numbers in a square of size n x n
    for i in range(1, N + 1, n):
        for j in range(1, N + 1, n):
            for x in range(i, i + n):
                for y in range(j, j + n):
                    for a in range(i, i + n):
                        for b in range(j, j + n):
                            for c in range(1, N + 1):
                                if (x != a or y != b) and (x * 10 + y < a * 10 + b):
                                 output(f"-{newlit(x,y,c)}-{newlit(a,b,c)}")
                                 newcl()


def sudoku_specific_constraints(myfile, sudoku):

    N = len(sudoku)

    def output(s):
        myfile.write(s)

    def newlit(i,j,k):
        if(N == 4 or N == 9):
            output(str(i)+str(j)+str(k)+ " ")
        else:
            output(str(i).zfill(2) + str(j).zfill(2) + str(k).zfill(2) + " ")

    def newcl():
        output("0\n")

    for i in range(N):
        for j in range(N):
            if sudoku[i][j] > 0:
                newlit(i + 1, j + 1, sudoku[i][j])
                newcl()

def sudoku_other_solution_constraint(myfile, sudoku):
    N = len(sudoku)

    def output(s):
        myfile.write(s)

    def newlit(i,j,k):
        if(N == 4 or N == 9):
            output(str(i)+str(j)+str(k)+ " ")
        else:
            output(str(i).zfill(2) + str(j).zfill(2) + str(k).zfill(2) + " ")

    def newcl():
        output("0\n")

    # We use the negation of every cell to obtain new clauses and find (if possible) a new solution
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            newlit(-i, j, sudoku[i - 1][j - 1])
        newcl()
                
def sudoku_solve(filename):
    command = "java -jar org.sat4j.core.jar sudoku.cnf"
    process = subprocess.Popen(command, shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = process.communicate()
    for line in out.split(b'\n'):
        line = line.decode("utf-8")
        if line == "" or line[0] == 'c':
            continue
        if line[0] == 's':
            if line != 's SATISFIABLE':
                return []
            continue
        if line[0] == 'v':
            line = line[2:]
            units = line.split()
            if units.pop() != '0':
                exit("strange output from SAT solver:" + line + "\n")
            units = [int(x) for x in units if int(x) >= 0]
            N = len(units)
            if N == 16:
                N = 4
            elif N == 81:
                N = 9
            elif N == 256:
                N = 16
            elif N == 625:
                N = 25
            else:
                exit("strange output from SAT solver:" + line + "\n")
            sudoku = [ [0 for i in range(N)] for j in range(N)]
            for number in units:
                if(N == 4 or N == 9) :
                 sudoku[number // 100 - 1][( number // 10 )% 10 - 1] = number % 10
                if( N == 16 or N == 25) :
                 sudoku[number // 10000 - 1][( number // 100 )% 100 - 1] = number % 100
            return sudoku
        exit("strange output from SAT solver:" + line + "\n")
        return []

def sudoku_generate(size):
    complete_sudoku = sudoku_generate_complete(size)
    # Remove a random cell and verify is the solution is unique
    attempts = 0
    while attempts < 2:
        non_empty_cells = [(i, j) for i in range(size) for j in range(size) if complete_sudoku[i][j] != 0]
        if not non_empty_cells:
        # No cell available
            break  # Leave the loop is all cells are already empty

        i, j = random.choice(non_empty_cells)

        # Save the original value of the cell
        original_value = complete_sudoku[i][j]

        # Remove the value in the cell
        complete_sudoku[i][j] = 0
        print("\n Case enlevée :")
        sudoku_print(sys.stdout, complete_sudoku)

        update_cnf_file(complete_sudoku)

        # Verify solution
        solved_grid = sudoku_solve("sudoku.cnf")
        if solved_grid != [] :
            myfile = open("sudoku.cnf", 'a')
            sudoku_other_solution_constraint(myfile, solved_grid)
            myfile.close()
            if sudoku_solve("sudoku.cnf") == []:
                print("\nsolution is unique\n")
                attempts = 0  # Reset the attempt if solution is unique

            else:
                print("\nother solution\n")
                #sudoku_print(sys.stdout, solved_grid)
                complete_sudoku[i][j] = original_value
                attempts += 1


    return complete_sudoku


def sudoku_generate_complete(size):
    # Create an empty grid
    grid = [[0 for _ in range(size)] for _ in range(size)]
    N = len(grid)
    myfile = open("sudoku.cnf", 'w')
    # Notice that this may not be correct for N > 9
    myfile.write("p cnf "+str(N)+str(N)+str(N)+" "+
                 str(sudoku_constraints_number(grid))+"\n")
    sudoku_generic_constraints(myfile, N)
    # Adds a random number
    move_result= random_move(grid)
    
    sudoku_specific_constraints(myfile, grid)
    myfile.close()
    # Solves the sudoku
    sudoku = sudoku_solve("sudoku.cnf")    
    if mode == Mode.CREATEMIN:
    # Remove the numbers equal to <size>
        for i in range(size):
            for j in range(size):
                if sudoku[i][j] == size:
                    sudoku[i][j] = 0  # Replace the cell by 0 if the number is equal to <size>

    return sudoku

def update_cnf_file(sudoku):
    N = len(sudoku)
    myfile = open("sudoku.cnf", 'w')
    myfile.write("p cnf "+str(N)+str(N)+str(N)+" "+
                 str(sudoku_constraints_number(sudoku))+"\n")
    sudoku_generic_constraints(myfile, N)
    sudoku_specific_constraints(myfile, sudoku)
    myfile.close()

def random_move(grid):
    # Picks a random cell
    empty_cells = [(i, j) for i in range(len(grid)) for j in range(len(grid[0])) if grid[i][j] == 0]

    if not empty_cells:
        # No cell available
        return None

    i, j = random.choice(empty_cells)

    # Picks a random number
    value = random.randint(1, len(grid))
    grid[i][j] = value
    return grid

from enum import Enum
class Mode(Enum):
    SOLVE = 1
    UNIQUE = 2
    CREATE = 3
    CREATEMIN = 4

OPTIONS = {}
OPTIONS["-s"] = Mode.SOLVE
OPTIONS["-u"] = Mode.UNIQUE
OPTIONS["-c"] = Mode.CREATE
OPTIONS["-cm"] = Mode.CREATEMIN

if len(sys.argv) != 3 or not sys.argv[1] in OPTIONS :
    sys.stdout.write("./sudokub.py <operation> <argument>\n")
    sys.stdout.write("     where <operation> can be -s, -u, -c, -cm\n")
    sys.stdout.write("  ./sudokub.py -s <input>.txt: solves the Sudoku in input, whatever its size\n")
    sys.stdout.write("  ./sudokub.py -u <input>.txt: check the uniqueness of solution for Sudoku in input, whatever its size\n")
    sys.stdout.write("  ./sudokub.py -c <size>: creates a Sudoku of appropriate <size>\n")
    sys.stdout.write("  ./sudokub.py -cm <size>: creates a Sudoku of appropriate <size> using only <size>-1 numbers\n")
    sys.stdout.write("    <size> is either 4, 9, 16, or 25\n")
    exit("Bad arguments\n")

mode = OPTIONS[sys.argv[1]]
if mode == Mode.SOLVE or mode == Mode.UNIQUE:
    filename = str(sys.argv[2])
    sudoku = sudoku_read(filename)
    N = len(sudoku)
    myfile = open("sudoku.cnf", 'w')
    # Notice that this may not be correct for N > 9
    myfile.write("p cnf "+str(N)+str(N)+str(N)+" "+
                 str(sudoku_constraints_number(sudoku))+"\n")
    sudoku_generic_constraints(myfile, N)
    sudoku_specific_constraints(myfile, sudoku)
    myfile.close()
    sys.stdout.write("sudoku\n")
    sudoku_print(sys.stdout, sudoku)
    sudoku = sudoku_solve("sudoku.cnf")    
    sys.stdout.write("\nsolution\n")
    sudoku_print(sys.stdout, sudoku)
    if sudoku != [] and mode == Mode.UNIQUE:
        myfile = open("sudoku.cnf", 'a')
        sudoku_other_solution_constraint(myfile, sudoku)
        myfile.close()
        sudoku = sudoku_solve("sudoku.cnf")
        if sudoku == []:
            sys.stdout.write("\nsolution is unique\n")
        else:
            sys.stdout.write("\nother solution\n")
            sudoku_print(sys.stdout, sudoku)
elif mode == Mode.CREATE:
    size = int(sys.argv[2])
    sudoku = sudoku_generate(size)
    sys.stdout.write("\ngenerated sudoku\n")
    sudoku_print(sys.stdout, sudoku)
elif mode == Mode.CREATEMIN:
    size = int(sys.argv[2])
    sudoku = sudoku_generate(size)
    sys.stdout.write("\ngenerated sudoku\n")
    sudoku_print(sys.stdout, sudoku)

# Saves the end time
end_time = time.time()

# Calculates the total time
total_time = end_time - start_time

# Display total time
print(f"Total time : {total_time} sec")
