# What is this?
This is a command-line script, written entirely in C++ and meant to fit in a single file, to analyze the frequencies of characters, tokens, and words. I wrote it over the course of 5 days since I had nothing better to do (most of the work has been done within the last 2 days, additionally) and wanted to make something that could serve at least a marginal amount of utility to someone if any.
# Command line argument formatting
When using this, be sure to:
- Specify 4 numbers at the beginning (modes)
- - The first is to specify how the text is divided up (0 for user-specified tokenization with custom delims, 1 for individual characters, 2 for words, 3 for a specific set of characters)
- - The second is to specify the files provided will be analyzed, either individually or as a collective (0 for individually, 1 for collectively)
- - The third is to specify case-sensitivity (0 for sensitive, 1 for non-sensitive)
- - The fourth is to specify the target file will be cleared or only added to (0 for keep, 1 for purge)
- Specify any number of input files (at least 1 — will exit otherwise)
- Specify an output file

The input files are prefixed with ```input=``` and the single output file is prefixed with ```output=``` (there can only be one).
# Anything else?
I don't believe this'll really be a one-and-done project, as I think it still has some potential to be realized. But we'll see where it goes.
