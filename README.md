# Text_Compression

Work In progress. Lossy compression algorithm for text files, case sensetive information is lost, everything else is retained.

This was designed by me.
The algorith works as follows:
  1. Tokenize the text file into individual words.
  2. Create a linked list with one node for each word.
          ->Each word also has a count, meaning the number of times it appears in the file.
  3. New words are dynamically added to the end of the linked list, while repeated words get their count updated. (case insensitive)

Once this linked list structure is ready, the idea now is to calculate a compression value for each word. this is given by

                                  memory_saved=(word_length * count) - length - count -1

Explanation is provided later.

  4. Out of all the words, the 256 words with the highest compression value are selected.
  5. These words will be replaced by a unique number in the output file.

This algorithm works best when input text has lots of repeated words and long words, as should be clear from the given equation.

The total memory saved is the summation of memory saved for all 256 of the words. If instead of 1 bytes, we are willing to use 2 bytes to encode individual words, the algorithm can be improved further.

The implementation of the table that contains the key and the actual reading of the file to make a new file is incomplete.

**Explanation for the given equation**
Each character takes up 1 byte of memory. The memory consumed by a particular word can be expressed as (word_lenth * count). Since each of these occurences is replaced by a 1 byte integer, we must subtract (1 * count) from the total. Also, memory is required for the table, which will contain the word itself (requiring 1 * word_length bytes) and a corresponding int, which is another byte that must be subtracted.
