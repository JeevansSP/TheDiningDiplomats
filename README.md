
# The Dining Diplomats


Diplomats from several countries are together for a summit. The banquet on the last day of the summit is
to be served at a big round table. The organisers need to finalise a seating arrangement for the diplomats.
Some pairs of diplomats are known to be friendly to each other, and some other pairs are known to be foes
of each other. Some diplomats are indifferent to all the other diplomats. The organisers would like to design
a seating chart so that no two foes are seated next to each other, unless at least one of them is also seated
next to a friend, and the other is seated next to a friend or an indifferent diplomat.
Write a C++ program that given the facts about friends, foes and indifferent diplomats, generates a
seating arrangement, if any, that satisfies the above condition. If no such seating arrangement exists, the
program should output a suitable message.

## Input 

The input will have several lines of input. Each line may have two names and one integer (1 for friend, and
0 for foe), or just one name for diplomats that are indifferent to all the others. The string of characters
containing the name may contain non-letters; they should not be included in the name. Some of the letters
in the name may be in upper case. These, except the first letter, should be converted to lower case.  
Names and numbers may be separated by one or more blank spaces (’ ’), and/or tab characters (’/t’). On each line,
there may be one or more blank spaces (’ ’), and/or tab characters (’/t’) before the end of line character
(’/n’).  
For example, consider the following input:  

*Jo4e Ma,ry 1*  
*ElizaBet5h June 1*  
*Joe John 0*  
*Joe, JuNe 0*  
*John JUne 1*  
*Margaret*   

The above input indicates that there are 6 diplomats attending the summit: Joe, Mary, Elizabeth, June,
John, and Margaret. The friend pairs are Joe and Mary, Elizabeth and June and John and June.  
The foe
pairs are Joe and John, and Joe and June. Margaret is indifferent to all the others.
You may assume that only those diplomats whose names are included in the input file will be at the summit.  
If a pair of diplomats, say A and B, appear in the input, but do not appear as either a pair of friends, or
a pair of foes, you may assume that they are indifferent to each other.
You may assume that the input file is not contradictory, i.e., if two diplomats are listed as friends, then
they will not be listed as foes, nor will either of them be listed as being indifferent. Similarly, if two diplomats
are listed as foes, they will not be listed as friends, nor will either of them be listed as being indifferent.
If diplomat A is listed as a friend (respectively, foe) of diplomat B, then this implies that B is a friend
(respectively, foe) of A.


## Output
Output
Your program should first output the names of all the diplomats at the summit in alphabetical order.  
Then, your program should output a possible seating arrangement, if one exists. If no seating arrangement is
possible, then your program should print a suitable message.  
For the above input, your program could output:  

*Diplomats: Elizabeth, Joe, John, June, Margaret, Mary.*  
*Seating Arrangement: Joe, Mary, Elizabeth, June, John, Margaret.*  

Note that, since the banquet is at a round table, Margaret is seated next to Joe.
Note that for a given input file, there may be several possible seating arrangements. For example, for
the above input, another possible seating arrangement is:  
*Joe, John, June, Mary, Elizabeth, Margaret*  
In this case the two foes Joe and John are seated next to each other, but John has a friend in June also
seated next to him, and Joe has Margaret, an indifferent diplomat, seated next to him.
If multiple seating arrangements exist, your program can output any one of these possible seating arrangements

## Problem Breakdown
If the problem statement seemed confusing do not worry, let me explain it in simpler terms  
ignore the input format for a second, we will get to that later. Now, there are some number of diplomats (let us assume n) who are supposed to be seated on a round table, by default all diplomats are indifferent to each other unless a relationship between TWO DIPLOMATS is explcitly specified. The relationship can be 0 (foes) or 1 (friends), for example:  

*joe*  
*june john 0*  
*joe john 0*  

this means:  
joe and john are foes  
joe and june are indifferent  
june and john are foes  

Kindly note a relationship is undirected (goes both ways).

Hope this cleared the input format  
For the seating arrangement, two friends or indifferent diplomats can be seated next to each other, but if two foes are to be seated next to each other then one of them MUST also be seated next to a friend and the other MUST also be seated next to a friend OR an indifferent diplomat.  

Example:  
*joe john 0*  
*julia*  
*jacob joe 1*  
*jeffery*  
*joestar john 1*  

Possible valid seating arrangements:  
*Jeffery, Jacob, Joe, John, Joestar, Julia*  
*Jacob, Jeffery, Joe, John, Joestar, Julia*  
*Jeffery,Jacob, Joe, John, Julia, Joestar*  

Possible invalid seating arrangement:  
*Jacob, Jeffery, Joe, John, Julia, Joestar*  

Hope that clears the rules for seating foes next to each other.  



## Solution modeling 
Parsing the input is the easy part hence i will go through it in the end. For simplicity lets do the following assumptions:  
1. We have parsed the input  
2. We have a list of all unique diploamts  
3. We also have the diplomats numbered from 0 to total number of diplomats - 1  
4. We have maps that can give us the diplomat number if we give it a diplomat and vice versa  
5. We have a 2D matrix where if we we can pass in two diplomats' numbers as first index and second index and it will give us 3 possible values: 0 (indifferent), 1 (friends), -1 (foes). I know this is different from the relationship input has specified but i hope it is understood.  

A naive approach would be to try all possible combinations of seating arrangments and check for each arrangement if its valid or not. This is easy to implement but on average gives us a time compleixty of `O(total_number_of_diplomats! * total_number_of_diplomats)` and since the total number of diploamts can go upto 50, this would be computationaly very expensive.  

Let us see if we can improve it.  

I will be using numbers/alphabets to refer to diplomats from this point forward unless i specifically mention their names.  
Assuming there is a valid seating arrangement, it does not matter who we seat first,   
example:  
if the valid seating arrangment is  
a b c d  
then  
c d a b  
d a b c 

are also valid (note they are circular so the array wraps itself in the end)  

in naive approach we started with an empty table and kept adding diplomats randomly, instead of adding randomly let us check the seating constraints and add them   
we start off my adding the 0th diplomat to the table first then recursively we start iterating through all the diploamats from 1 to the end, for each diploamat we will add them based on the the below rules 

1. If a diplomat is already added to the table i ignore them.
2. If the last diplomat and second last diplomat are foes, then based on the relationship between the second last diplomat and their left neighbor i will add a valid diplomat, if there is no person left to the second last diploamt (i.e., current table size is only 2) and last diplomat and current diplomat arent foes, i will simply add any diplomat and move forward.  
3. For all other cases i will simply add any diplomat who has not been added yet.
4. If the table size is full i.e., all diplomats are seated, then we check if the arrangement is valid this will run in constant time (will explain it later).

We can follow this apporach recursively and try to fill each seat one by one and if we dont find a valid arrangment we simply backtrack and try building a different possibly valid arrangment   

Now let me explain why we need to check if the arrangement is valid if we only seat valid diplomats in each call, well that's because the arrangement is not always 100% valid when it reaches max size, we do try to seat valid diplomats but there are some cases where we DO NOT KNOW if it's valid, let me explain those cases below:

**case 1:** dip1 foe2 foe3 dip4 ...... dipN  
table size when placing foe3 diplomat was only 2  
hence we will need to check dip1 - foe2 and foe3 - dip4 relationship which we could not when placing foe3 as dip4 was not placed yet.

**case 2:** dip1 dip2 ......dipN-2 foeN-1 foeN  
We placed foeN thinking we can make a valid foeN-1 - foeN seating arrangment in the next call diplomat placement but then we reach the max table size
here we will need to check dipN-2 - foeN-1 and foeN - dip1 relationship.

**case 3:** foe1 dip2 dip3 ...... dipN-1 foeN  
Of course there is no way to know if first and last diplomats are foes until we reach the end, if they are we will need to check foe1 - dip2 and dipN-1 - foeN relationship.

Now the time complexity on average will become 
`O(k*total_number_of_diplomats^2)` 
where k is total number of valid arrangements.

**Optimizations:**   
*Optimization 1.* Since we only need 1 valid seating arrangement, we can store a variable which will be set to true once we have reached our first valid arrangement and stopping all further recursive calls.  
*Optimization 2.* Suppose we have 3 diplomats with no valid arangments, then once 0 1 2 has been reached and checked there is no point checking 1 2 0 or 2 0 1 permutations, as they are circular hence same. We can avoid this by first keeping 0 on the table and only iterating from [1, total_number_of_diplomats) in each recursive call to add them to the table.


memoization is not really required as we will not be reaching overlapping sub problems due to optimization 2 + the fact that we are backtracking.

Using the above optimizations we can get the average time-complexity to `O(total_number_of_diplomats^2)`    
Note that while worst-case time-compleixty (when no valid arrangements are present) may seem to be `O(total_number_of_diplomats!)` it will not reach that number quantitatively due to the optimizations.


Now let's talk about input parsing:   

we can use cin>> to read each word/number
cin terminates on \t and \n anyway so everytime we do a cin>> we will read a word no matter how many \t s are present before or after the word.  
We can terminate cin when it reached EOF.  

Next we will clean the names by iterating through each character of each name and if it falls withinn the ascii range of lower and upper case letters then only include them, further Pascal case the cleaned name. If it's a number we simply add it.

now the cleaned input vector will be as follows:  

Joe  
Jeffery  
1
Jive  
Joestar  
Jaro  
0  

We know every time we hit 0 or 1 it will correspond to the relationship between the two preceeding diplomats, using this logic we can model our relationship 2D array/vector.  

Finally we collect all unique diplomats and give them numbers starting from 0. 


This concludes the input parsing.  
input parsing + recursive backtracking and pruning will give us a time complexity of   
`O(total_number_of_characters_in_test_case) + O(total_number_of_diplomats^2)`  
and the final space complexity will be `O(total_number_of_words^2)`  


Now I do believe there can be a graph based solution (maybe graph-colouring I'm not sure), or a greedy solution based on some heuristics which can provide a better average and worst-case time complexity but i have not been able to get there yet :)


## Compilation and execution  
You will need to have a [C++ compiler installed](https://www.youtube.com/watch?v=hCLIDph7-mU) (CTRL+click) with the path set in environment variables  
you can complie the code by running the below line in your cmd/powershell/bash terminal, just make sure you are in the right directory  
  `g++ solution.cpp -o solution`  
This will create an executable called solution.exe in your current directory
To run the executable you will need to feed it a valid test case file.  

**Cmd**  `solution.exe < test1.txt` 

**PowerShell** `Get-Content test1.txt | .\solution.exe`    

**Bash** `./solution.exe < test1.txt`    

  
This will give the result in the terminal






