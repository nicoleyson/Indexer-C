# Indexer-C
#Introduction
 In this assignment you will practice using the file system API (as well as pointers in different data
structures). In particular you will be creating, opening, reading, writing, and deleting files.
Your task is to write an indexing program, called an indexer. Given a set of files, an indexer will
parse the files and create an inverted index, which maps each token found in the files to the subset
of files that contain that token. In your indexer, you will also maintain the frequency with which
each token appears in each file. The indexer should tokenize the files and produce an inverted index of
how many times the word occurred in each file, sorted by word. Your output should be in the following
format:
{"list" : [
{"word0" : [
{"filepath0" : count0},
{"filepath1" : count1}
]},
{"word1" : [
{"filepath2" : count2},
{"filepath3" : count3},
{“filepath4” : count4}
]}
]}

Here is an example of how the indexer should work. If you are given the following set of files:
File Path : File Content
/adir/boo : A dog name name Boo
/adir/baa : A cat name Baa

Your indexer should output:
{"list" : [
{"A" : [
{"baa" : 1},
{"boo" : 1}
]},
{"Baa" : [
{"baa" : 1}
]},
{“Boo” : [
{"boo" : 1}
]},
{“cat” : [
{"baa" : 1}
]},
{“dog” : [
{"boo" : 1}
]},
{“name” : [
{"boo" : 1},
{"baa" : 2}
]}
]}

After constructing the entire inverted index in memory, the indexer will save it to a file.
An inverted index is a sequence of mappings where each mapping maps a token (e.g.,
“dog”) to a list of records, with each record containing the name of a file whose content
contains the token and the frequency with which the token appears in the file.
The above depiction gives a logical view of the inverted index. In your program, you
have to define data structures to hold the mappings (token list) and the records (file
name, count).
The mappings are maintained in sorted order of the tokens. You will see later why this is
useful. Your mappings should be maintained in ascending sorted order based on the ASCII coding of
characters (i.e., “a” before “b” and “aa” before “ab”).

Records in each list are maintained in descending sorted order based on frequency counts
of the tokens in the files. Again, you will see later why this is useful.
Tokens are not case sensitive. All upper-case letters should be converted to lower-case.
The tokenizer and sorted-list that you wrote in earlier assignments may be useful for this
assignment (although you have to modify the tokenizer to work with a file, rather than a
string.
# Implementation
 Your program must implement the following command-line interface:
index <inverted-index file name> <directory or file name>
The first argument, <inverted-index file name>, gives the name of a file that you should create to
hold your inverted index. The second argument, <directory or file name>, gives the name of the
directory or file that your indexer should index. If the second argument is a directory, you need to
recursively index all files in the directory (and its sub-directories). If the second argument is a file,
you just need to index that single file.
When indexing files in a directory, you may have files that have the same name in separate
directories. You should prepend the pathname (relative to the input directory name) in every
record in the inverted index, rather than just the file name.
Tokenization is a little different in this assignment than in the previous assignment. You are not
given a set of separators. Instead, we define tokens as any sequence of consecutive alphanumeric
characters (a-z, A-Z, 0-9) starting with an alphabetic character. You can modify your tokenizer to
read() from a file you opened with open().
Examples of tokens according to the above definition include:
a, aba, c123
If a file contains
This an$example12 mail@rutgers
it should tokenize to
this
an
an
example12
mail
rutgers
The inverted index file that your indexer writes must follow the JSON (JavaScript Object Notation)
format. Words must be sorted in alphanumeric order. All characters of the word should be first
converted to lowercase. Your output should print with the lists arranged in ascending sorted order
of the tokens. The file path names in your output should be relative to the directory specified on
the command line, in descending order by frequency count (highest frequency to lowest frequency).
If there is a word with the same frequency in two or more files, order them by path name
alphanumerically (Hint: Use strcmp()).

The JSON format lets us easily read the inverted index for debugging. You should carefully consider
preexisting circumstances and how they relate to the execution of your program. You should outline
and implement a strategy to deal with these circumstances. For example, if a file already exists with the
same name as the inverted-index file name, you should ask the user if they wish to overwrite it. If the
name of the directory or file you want to index does not exist, your indexer should print an error
message and exit gracefully rather than crash. There are many other error cases that you will need to
consider.
You should use multi-file compilation to carefully organize your code. For example, the tokenizer
should be in its own .c file, with a .h file that callers should include. The same applies for the sortedlist.
You should also write a makefile to efficiently compile and link your indexer
