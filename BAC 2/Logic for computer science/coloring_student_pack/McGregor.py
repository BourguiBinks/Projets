#!/usr/bin/python

import sys

def create_graph(filename):
    myfile = open(filename, 'w')

    def output(s):
        myfile.write(s)
    def newcomment(s):
        output("# %s\n"%s)
    def edge(n1, n2):
        if n1 < 10: output("0")
        elif n1 > 99: output("a")
        else: output(str(n1 // 10))
        output(str(n1%10)+" ")   
        if n2 < 10: output("0")
        elif n2 > 99: output("a")
        else: output(str(n2 // 10))
        output(str(n2%10)+"\n")
    
    newcomment("irregularly connected to a9")
    for i in range(0,10):
        edge(109,i)
    edge(109,19)
    newcomment("irregularly connected to 00")
    for i in range(0,6):
        edge(00,100+i)
    edge(00,10)
    newcomment("connected to 10")
    for i in range(5,10):
        edge(10,100+i)
    
    for i in range(0,10):
        newcomment("line "+str(i)+" horizontal")
        for j in range(i,9):
            edge(i*10+j, i*10+j+1)
    for i in range(2,11):
        newcomment("line "+str(i)+" horizontal")
        for j in range(0,i - 1):
            edge(i*10+j, i*10+j+1)
    for i in range(1,10):
        newcomment("line "+str(i)+" down")
        for j in range(i,10):
            edge((i-1)*10+j-1,i*10+j)
            edge((i-1)*10+j,i*10+j)
    for i in range(2,10):
        newcomment("line "+str(i)+" up")
        for j in range(0,i):
            edge((i+1)*10+j,i*10+j)
            edge((i+1)*10+j+1,i*10+j)
    edge(00,100)
    edge(11,100)
    edge(11,90)
    edge(22,90)
    edge(22,80)
    edge(33,80)
    edge(33,70)
    edge(44,70)
    edge(44,60)
    edge(55,60)
    edge(55,50)
    edge(66,50)
    edge(66,40)
    edge(77,40)
    edge(77,30)
    edge(88,30)
    edge(88,20)

    edge(88,99)
    edge(89,99)

    edge(99,20)
    edge(99,21)
    edge(89,21)
    edge(89,32)
    edge(79,32)
    edge(79,43)
    edge(69,43)
    edge(69,54)
    edge(59,54)
    edge(59,65)
    edge(49,65)
    edge(49,76)
    edge(39,76)
    edge(39,87)
    edge(29,87)
    edge(29,98)
    edge(19,98)
    edge(19,109)
    edge( 9,109)

def create_tikz(filename, coloring_list):
    myfile = open(filename, 'w')

    coloring = {}
    if coloring_list != []:
        for (node, color) in coloring_list:
            coloring[node] = color

    def output(s):
        myfile.write(s)
    def newcomment(s):
        output("% %s\n"%s)
    def block_num(n):
        return ("0" if n<10 else "a" if n>99 else str(n // 10)) + str(n % 10)
    def block(n, posn, pos):
        output("\\draw [block"+
               (str(coloring[block_num(n)]) if block_num(n) in coloring else "")
               + "] ")
        first = True
        for i in pos:
            if not first: output(" -- ")
            first = False
            (x, y) = i
            output("(%d,%d)" % (x, y))
        output(";\n")
        (x, y) = posn
        ns = ("0" if n<10 else "a" if n>99 else str(n // 10)) + str(n % 10)
        output("\\node at (%f,%f) {%s};\n" % (x, y, ns));
    def rec_block(n, x, y):
        output("\\draw [block"+
               (str(coloring[block_num(n)]) if block_num(n) in coloring else "")
               + "] ")
        output(" (%d,%d) rectangle +(4,2);\n" % ( x, y ))
        output("\\node at (%d,%d) {%s};\n" % ( x + 2, y + 1, block_num(n) ));
        
    output("\\begin{tikzpicture}[scale=0.15, every node/.style={scale=0.5},\n")
    output("                     block1/.style={draw=black,fill=red!20},\n")
    output("                     block2/.style={draw=black,fill=blue!20},\n")
    output("                     block3/.style={draw=black,fill=teal!20},\n")
    output("                     block4/.style={draw=black,fill=violet!20},\n")
    output("                     block/.style={draw=black,fill=white},]\n")

    for i in range(0,8):
        for j in range(i + 1,9):
            rec_block(i*10 + j, -20 + j * 4 - i * 2, 17 - i * 2)

    for i in range(3,11):
        for j in range(1,i - 1):
            rec_block(i*10 + j, j * 4  - i * 2, 1 - i * 2 )

    block(109,(17.5,-18),[(-21,19), (-21,21), (22,21), (22,-19), (16,-19), (16,-17), (17,-17), (17,0), (20,0), (20,19), (-21,19)])

    block(0,(-18,18),[(-21,19), (-21,-21), (2,-21), (2,-19), (-19,-19), (-19,0), (-18,0), (-18,17), (-16,17), (-16,19), (-21,19)])
    block(10,(11,-20),[(2,-21), (2,-19), (22,-19), (22,-21), (2,-21)])

    for i in range(0,9):
        y = 17 - i * 2
        x = -20 + 9 * 4 - i * 2
        block(i*10+9,(x+2,y+1),[(x,y), (x,y+2), (x+4,y+2), (x+4,0), (x+2,0), (x+2,y), (x,y)])
        if i == 0: continue
        x = -20 + (i + 1) * 4 - i * 2
        block(i*10+i,(x-2,y+1),[(x,y), (x,y+2), (x-4,y+2), (x-4,0), (x-2,0), (x-2,y), (x,y)])

    for i in range(2,11):
        y = 1 - i * 2
        x = 1 * 4  - i * 2
        block(i*10,(x-1.5,y+1),[(x,y), (x,y+2), (x-1,y+2), (x-1,0), (x-3,0), (x-3,y), (x,y)])
        x = (i - 1) * 4  - i * 2
        if i == 10: continue
        block(i*10+(i-1),(x+1.5,y+1),[(x,y), (x,y+2), (x+1,y+2), (x+1,0), (x+3,0), (x+3,y), (x,y)])
        
    rec_block(99, -2, -1)

    output("\end{tikzpicture}")

        
create_graph("McGregor.txt")
create_tikz("McGregor.tikz",[])
# Substitute the empty list by the solution list provided by the script coloring.py
create_tikz("McGregorc.tikz",[])
            
