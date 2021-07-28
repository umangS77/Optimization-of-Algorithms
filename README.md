### Umang Srivastava
### 2019101090

# Soware Programming for Performance

# Assignment 1 Report

## Task 1 : Matrix Chain Multiplication

##### Problem Statement: Given a sequence of n matrices,find an efficient way to multiply these matrices together.

### Optimisations :

● Took transpose of the second matrix to improve thechances of getting cache hit,
as the neighbouring elements will now be accesed versusaccesing different
columns of the different matrices.

● Tiling : Loop tiling, also known as loop blocking,is a loop transformation that
exploits spatial and temporal locality of data accesses in loop nests. This
transformation allows data to be accessed in blocks(tiles), with the block size
defined as a parameter of this transformation. Eachloop is transformed in two
loops: one iterating inside each block (intratile)and the other one iterating over
the blocks (intertile). Here, block size of 16 istaken.

● Loop Unrolling - Instead of taking a loop to add 16 elements, added them in a
single line. This reduced the time taken for incrementof loop variable. The aim of
loop unrolling is to speed up a programme by decreasing or removing
loop-controlling instructions, such as pointer arithmetic and "end of loop" checks
on each iteration, reducing branch penalties; andhiding latencies, such as the time
it takes to read data from memory.
```
temp += *(x + k) * *(y + k) + *(x + k+ 1 ) * *(y + k+ 1 ) + *(x + k+ 2 ) * *(y +
k+ 2 )+ *(x + k+ 3 ) * *(y + k+ 3 ) + *(x + k+ 4 ) * *(y + k+ 4 ) + *(x + k+ 5 ) * *(y
+ k+ 5 ) + *(x + k+ 6 ) * *(y + k+ 6 ) + *(x + k+ 7 ) * *(y + k+ 7 ) + *(x + k+ 8 ) *
*(y + k+ 8 ) + *(x + k+ 9 ) * *(y + k+ 9 ) + *(x + k+ 10 ) * *(y + k+ 10 ) + *(x +
k+ 11 ) * *(y + k+ 11 ) + *(x + k+ 12 ) * *(y + k+ 12 ) + *(x + k+ 13 ) * *(y +
k+ 13 ) + *(x + k+ 14 ) * *(y + k+ 14 ) + *(x + k+ 15 ) * *(y + k+ 15 );
```
● Prefer pre-increment over post-increment since post-increment keeps a copy of
previous (existing) value and adds 1 in the existing value while pre-increment is
simply adds 1 without keeping the existing value.
● Using pointer access for memory location instead of array looking.
```
x = *(A->matrix + i);
```
● Using single dimension array for multiplicants.
```
x = *(A->matrix + i);
z = *(result->matrix + i);
y = *(B->matrix + j);
```

## Task 2 : Floyd Warshall Algorithm

##### Problem Statement: For a given Adjacency list of agraph, find the shortest path between every pair of vertices in the graph.

### Optimisations :

● Loop tiling, also known as loop blocking, is a loop transition that uses the spatial
and temporal localization of data accesses in loopnests to create a loop. This
transformation's block size is defined as a parameter,allowing data to be accessed
in blocks (tiles).
```
#define BS 8 // block_size
// loop tiling and loop unrolling here
for (j= 0 ;j<n-BS;j+=BS)
{
register int val = *(B + k) + *(C + j);
if (val < *(B + j))
{
*(B + j) = val;
}

val = *(B + k) + *(C + j + 1 );
if (val < *(B + j + 1 ))
{
*(B + j + 1 ) = val;
}

val = *(B + k) + *(C + j + 2 );
if (val < *(B + j + 2 ))
{
*(B + j + 2 ) = val;
}

val = *(B + k) + *(C + j + 3 );
if (val < *(B + j + 3 ))
{
*(B + j + 3 ) = val;
}

val = *(B + k) + *(C + j + 4 );
if (val < *(B + j + 4 ))
{
*(B + j + 4 ) = val;
}

val = *(B + k) + *(C + j + 5 );
if (val < *(B + j + 5 ))
{
*(B + j + 5 ) = val;
}

val = *(B + k) + *(C + j + 6 );
if (val < *(B + j + 6 ))
{
*(B + j + 6 ) = val;
}
val = *(B + k) + *(C + j + 7 );
if (val < *(B + j + 7 ))
{
*(B + j + 7 ) = val;
}
}
for(;j<n;++j)
{
register int val = *(B + k) + *(C + j);
if (*(B + j) == INF || val < *(B + j))
{
*(B + j) = val;
}
}
```
● Loop unrolling : instead of using a loop to add 8elements, a single line was used.
This cut back on the time it took to increment theloop vector. The aim of loop
unrolling is to speed up a programme by reducing branchpenalties and hiding
latencies, such as the time it takes to read datafrom memory, by decreasing or
deleting loop-controlling instructions, such as pointerarithmetic and "end of loop"
tests on each iteration.

● Prefer pre-increment over post-increment since post-incrementkeeps a copy of
previous (existing) value and adds 1 in the existingvalue while pre-increment is
simply adds 1 without keeping the existing value.
● Using pointer access for memory location instead ofarray looking.
```
int * restrict C = *(matrix + k);
```
● Checking condition for no edge between 2 edges outside, before adding their
weights.
```
if (*(B + k) != INF) // here
{
register int j;
for (j= 0 ;j<n-BS;j+=BS)
{
register int val = *(B + k) + *(C + j);
if (val < *(B + j))
{
*(B + j) = val;
}..... } }
```


