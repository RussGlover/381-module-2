By Aaron Cui
2015-04-02

euclidean, euclidean_interface, euclidean_hw were the original intended implmentation that does not work
Because they cannot handle a 255bit write directly, otherwise should work

euclidean_library is currently (2015-04-02) an unfinished intended implementation for
passing in all library (genre) data in one go (up to 7) and later on to be used
for comparison with the live music being played
- this may not be continued due to the algorithm / approach 

euclidean_single, euclidean_single_interface, euclidean_single_hw are the simple implementation 
which takes 1 bin at a time and compares them individually, 
calculation and algorithm handled on the software side with
euclidean.c which contains 3 functions, only 2 of which can be used currently
documented in the software source file itself 

The current concentration is on the adaptation between euclidean and euclidean single
Either fix the euclidean by achieving direct hardware memory writes with DMA / something
Or more simply put the hardcoded software loops / data holding in the hardware
but still reading and writing 32 bit at a time
This can be done by adding a "state" address that changes what the hardware does on writes

One extra possible hardware implementation is to have an average calculator 
since our library isn't a hard data but rather a dynamically created from hundreds of songs
Due to the difference between software / hardware algorithms being very different at this point
We might as well separate them completely and change some of our original approach 