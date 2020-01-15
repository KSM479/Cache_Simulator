Basic: 

I have added the makefile with the code. I have also renamed my cachesimulator.cpp to MIPS_pipeline.cpp. ( The makefile is the same as Lab 1 and I have not changed the makefile at all ) 
I have renamed my Lab 2 cachesimulator to MIPS_pipeline.cpp 

THE INPUT TO MY CODE HAS TO BE FROM "trace_small.txt" and the output can be observed from "output.out".
THE CACHE PARAMETERS MUST BE COMING FROM THE FILE "cacheconfig.txt" . 
 


Step by step guide to run the code:
1) Upload the makefile and MIPS_pipeline.cpp on gauss. (MIPS_pipeline is just renamed file cache_simulator.cpp)
2) rename your input files to "cacheconfig.txt" and "trace_small.txt"
3) On Gauss, you can compile your design by typing “make” which would create the MIPS_pipeline executable. Run the executable using “./MIPS_pipeline” command. :)
4) Output will be stored in "output.out" which can be observed using command "cat output.out" on Gauss. 
5) If you wish to test the with different input values then you will have to rename your input files to "cacheconfig.txt" or "trace_small.txt"

> I changed the file names as my compiler could not take argv[1] and argv[2] and generated some errors. I wrote my entire code using that same compiler and hence, I fixed the filenames when I ran the code on gauss.
IF YOU WISH TO USE ARGV[1] AND ARGV[2] THEN YOU CAN REPLACE WITH ARGV[1] ON LINE 124 AND WITH ARGV[2] ON LINE 193 AND 194. But, I cannot guarantee that the code will execute as expected. 

 
 
