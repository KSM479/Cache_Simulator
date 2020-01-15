  //FULLY ASSOCIATED IS WRONG__NEED TO CHANGE

    /*
Cache Simulator
Level one L1 and level two L2 cache parameters are read from file (block size, line per set and set per cache).
The 32 bit address is divided into tag bits (t), set index bits (s) and block offset bits (b)
//s = log2(#sets)   b = log2(block size)  t=32-s-b
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>

using namespace std;
//access state:
#define NA 0 // no action
#define RH 1 // read hit
#define RM 2 // read miss
#define WH 3 // Write hit
#define WM 4 // write miss




struct config{
       int L1blocksize;
       int L1setsize;
       int L1size;
       int L2blocksize;
       int L2setsize;
       int L2size;
       };

unsigned long shiftbits(bitset<32> inst, int start)
{
    unsigned long ulonginst;
    return ((inst.to_ulong())>>start);

}
/* you can define the cache class here, or design your own data structure for L1 and L2 cache */
class cacheL1 {

  public:
      int bL1,tL1,sL1,uL1,vL1;
   int cachebL1(int Lblock,int Lset,int Lsize )
   {
     bL1= log2(Lblock);


     return bL1;
   }
   int cachesL1(int Lblock,int Lset,int Lsize)
   {
       sL1= (Lset==0)?0:log2((Lsize*1024)/(Lblock*Lset));
       return sL1;
   }
   int cachetL1(int L1ins,int L1inb)
{
     tL1= 32-L1ins-L1inb;
     return tL1;
}
   int cacheuL1(int L1int)
   {
     uL1= 32-tL1;
     return uL1;
   }
    };


int main(int argc, char* argv[]){
    int L1s;
    int L1t;
    int L1u;
    int L1v;
    int L2s;
    int L1LRU;
    int L2LRU;
    int L2v;
    int L2u;
    int L2t;
    int L1b;
    int L2b;
    int offset;
    int L1MRU;
    int L2MRU;
    L1MRU = 0;
    L2MRU = 0;
    string indexL1;
    unsigned long     L1intindex;
    unsigned long     L2intindex;
    string tagL1;
    string tagL2;
    //unsigned long tagL1inint;
    //unsigned long tagL2inint;
    string indexL2;
    bitset<32>tagL1inint;
    bitset<32>tagL2inint;
    unsigned long PowerL1;
    unsigned long PowerL2;
    int i;
    int j;
    int a;
    bool k ;
    k = false;
    bool l ;
    l = false ;
    bool z ;
    z = false;
    bool y;
    y = false;
    bool x;
    x = false;
    int fullyassociatedL1;
    int fullyassociatedL2;

    config cacheconfig;
    ifstream cache_params;
    string dummyLine;
    cache_params.open("cacheconfig.txt");
    while(!cache_params.eof())  // read config file
    {
      cache_params>>dummyLine;
      cache_params>>cacheconfig.L1blocksize;
      cache_params>>cacheconfig.L1setsize;
      cache_params>>cacheconfig.L1size;
      cache_params>>dummyLine;
      cache_params>>cacheconfig.L2blocksize;
      cache_params>>cacheconfig.L2setsize;
      cache_params>>cacheconfig.L2size;
    }
   cacheL1 cL1,cL2;
   L1s = cL1.cachesL1(cacheconfig.L1blocksize,cacheconfig.L1setsize,cacheconfig.L1size);
   L1b = cL1.cachebL1(cacheconfig.L1blocksize,cacheconfig.L1setsize,cacheconfig.L1size);
   L1t = cL1.cachetL1(L1s,L1b);
   L1u = cL1.cacheuL1(L1t);
   fullyassociatedL1 = (cacheconfig.L1size*1024)/(cacheconfig.L1blocksize);
 //   cout << fullyassociatedL1;
   if(cacheconfig.L1setsize == 0)
        {
            cacheconfig.L1setsize = fullyassociatedL1;        //for fully associated we only have 1 row, Hence, we are changing the L1setsize to match the number of columns
        }
   L2s = cL2.cachesL1(cacheconfig.L2blocksize,cacheconfig.L2setsize,cacheconfig.L2size);
   L2b = cL2.cachebL1(cacheconfig.L2blocksize,cacheconfig.L2setsize,cacheconfig.L2size);
   L2t = cL2.cachetL1(L2s,L2b);
   L2u = cL2.cacheuL1(L2t);
   fullyassociatedL2 = (cacheconfig.L2size*1024)/(cacheconfig.L2blocksize);
 //  cout << "              " <<fullyassociatedL1;
      if(cacheconfig.L2setsize == 0)
        {
           cacheconfig.L2setsize = fullyassociatedL2;        //for fully associated we only have 1 row, Hence, we are changing the L1setsize to match the number of columns
        }
    int columnsofL1;
    int columnsofL2;
columnsofL1 =2;
columnsofL2 =2;
    if (cacheconfig.L1setsize == 1 || cacheconfig.L1setsize == 0)
    {
        cacheconfig.L1setsize = columnsofL1;
    }
    else
    {
        cacheconfig.L1setsize = cacheconfig.L1setsize + 1;
    }
    if (cacheconfig.L2setsize == 1 || cacheconfig.L2setsize == 0)
    {
        cacheconfig.L2setsize = columnsofL2;
    }
    PowerL1 = pow(2,L1s);
    PowerL2 = pow(2,L2s);
    bitset<32> tagarrayofL1[PowerL1][cacheconfig.L1setsize-1]  ;
    bitset<32> tagarrayofL2[PowerL2][cacheconfig.L2setsize-1] ;
    unsigned long validL1[PowerL1][cacheconfig.L1setsize-1] ;
    unsigned long validL2[PowerL2][cacheconfig.L2setsize-1] ;
    unsigned long LRUL1[PowerL1][cacheconfig.L1setsize-1] ;
    unsigned long LRUL2[PowerL2][cacheconfig.L2setsize-1] ;
    LRUL2[PowerL2][cacheconfig.L2setsize-1]= {0};
    LRUL1[PowerL1][cacheconfig.L1setsize-1] = {0};
    validL2[PowerL2][cacheconfig.L2setsize-1] = {0};
    validL1[PowerL1][cacheconfig.L1setsize-1] = {0};
    tagarrayofL1[PowerL1][cacheconfig.L1setsize-1] = {0};
    tagarrayofL2[PowerL2][cacheconfig.L2setsize-1] = {0};

    int L1AcceState =0; // L1 access state variable, can be one of NA, RH, RM, WH, WM;
    int L2AcceState =0; // L2 access state variable, can be one of NA, RH, RM, WH, WM;
    ifstream traces;
    ofstream tracesout;
    string outname;
    outname = string("output") + ".out";
    traces.open("trace_small.txt");
    tracesout.open(outname.c_str());
    string line;
    string accesstype;  // the Read/Write access type from the memory trace;
    string xaddr;       // the address from the memory trace store in hex;
    unsigned int addr;  // the address from the memory trace store in unsigned int;
    bitset<32> accessaddr; // the address from the memory trace store in the bitset;
    if (traces.is_open()&&tracesout.is_open()){
        while (getline (traces,line)){   // read mem access file and access Cache
            istringstream iss(line);
            if (!(iss >> accesstype >> xaddr)) {break;}
                stringstream saddr(xaddr);
                saddr >> std::hex >> addr;
                accessaddr = bitset<32> (addr);
                tagL1   =((bitset<32>(addr)).to_string().substr(0,L1t));
                tagL2   =((bitset<32>(addr)).to_string().substr(0,L2t));
                tagL2inint = (bitset<32>(tagL2));
                tagL1inint = (bitset<32>(tagL1));
                indexL1 =((bitset<32>(addr)).to_string().substr((L1t+1),L1s));
                indexL2 =((bitset<32>(addr)).to_string().substr((L2t+1),L2s));
                L1intindex = (bitset<32>(indexL1)).to_ulong();
                L2intindex = (bitset<32>(indexL2)).to_ulong();

if (accesstype.compare("R")==0)
    {

            for (int i = 1; i < cacheconfig.L1setsize; i++)
               {
                if (validL1[L1intindex][i] ==1 && tagarrayofL1[L1intindex][i] == tagL1inint)
                        {
                            L1AcceState = 1;
                            L2AcceState = 0;

                            L1MRU = i;
                            LRUL1[L1intindex][cacheconfig.L1setsize-1] = L1MRU;
                            for (int i = cacheconfig.L1setsize-1; i >0; i--)
                                    { if(i>=2)

                                            {LRUL1[L1intindex][i-1] = LRUL1[L1intindex][i];}

                                    }

                            break;
                        }
               }
if ( L1AcceState == 0)
    {

        for (int i = 0; i < cacheconfig.L2setsize; i++)
                        {       if(validL2[L2intindex][i] == 1 && tagarrayofL2[L2intindex][i] == tagL2inint)
                            { k= 1;
                              l=1;
                                L1AcceState = 2;
                                L2AcceState = 1;

                                L2MRU = i;
                                LRUL2[L2intindex][cacheconfig.L2setsize] = L2MRU;
                                for (int j = cacheconfig.L2setsize; j >0; j--)
                                    { if(j>=1)
                                        {LRUL2[L2intindex][j-1] = LRUL2[L2intindex][j];}
                                    }
                                for(a=0; a < cacheconfig.L1setsize; a++)
                                    {cout <<"    " << validL1[L1intindex][a] << "             ";
                                        if (validL1[L1intindex][a] ==0)
                                            {
                                            tagarrayofL1[L1intindex] [a] = tagL1inint;
                                            validL1[L1intindex] [a] = 1;
                                            k=0;
                                            break;
                                            }

                                    }
                                    if(k)
                                    {
                                        L1LRU=LRUL1[L1intindex][1];
                                        LRUL1[L1intindex][cacheconfig.L1setsize-1] = L1LRU;
                                        validL1[L1intindex][cacheconfig.L1setsize-1] = 1;
                                        tagarrayofL1[L1intindex][cacheconfig.L1setsize-1] = tagL1inint;
                                    }

                               break;
                            }
                        else
                            {   L1AcceState = 2;
                                L2AcceState = 2;
                                for(a=0; a < cacheconfig.L1setsize; a++)
                                    {cout <<"    " << validL1[L1intindex][a] << "             ";
                                        if (validL1[L1intindex][a] ==0)
                                            {
                                            tagarrayofL1[L1intindex] [a] = tagL1inint;
                                            validL1[L1intindex] [a] = 1;
                                            k=0;
                                            break;
                                            }

                                    }
                                    if(k)
                                    {
                                        L1LRU=LRUL1[L1intindex][1];
                                        LRUL1[L1intindex][cacheconfig.L1setsize-1] = L1LRU;
                                        validL1[L1intindex][cacheconfig.L1setsize-1] = 1;
                                        tagarrayofL1[L1intindex][cacheconfig.L1setsize-1] = tagL1inint;
                                    }
                                for(a=0; a < cacheconfig.L2setsize; a++)
                                {
                                    if (validL2[L2intindex][a] ==0)
                                        {
                                            tagarrayofL2[L2intindex] [a] = tagL2inint;
                                            validL2[L2intindex] [a] = 1;
                                            l = 0;
                                            break;
                                        }
                                 }
                                 if(l)
                                 {
                                        L2LRU=LRUL2[L2intindex][1];
                                        LRUL2[L2intindex][cacheconfig.L2setsize] = L2LRU;
                                        validL2[L2intindex][cacheconfig.L2setsize] = 1;
                                        tagarrayofL2[L2intindex][cacheconfig.L2setsize] = tagL2inint;

                                 }
                            }
                        }
                }
}
else
{
     for (int i = 0; i < cacheconfig.L1setsize; i++)
               {
                        if (validL1[L1intindex][i] ==1 && tagarrayofL1[L1intindex][i] == tagL1inint)
                        {
                            L1AcceState = 3;
                            L2AcceState = 3;
                            L1MRU = i;
                            LRUL1[L1intindex][cacheconfig.L1setsize-1] = L1MRU;
                            for (int i = cacheconfig.L1setsize-1; i >0; i--)
                                    { if(i>=2)

                                            {LRUL1[L1intindex][i-1] = LRUL1[L1intindex][i];}

                                    }


                            break;
                        }
               }



if(L1AcceState==0)
                {
                    for (int a = 0; a < cacheconfig.L2setsize; a++)
                        {
                            if(validL2[L2intindex][a] == 1 && tagarrayofL2[L2intindex][a] == tagL2inint)
                            {
                                L1AcceState = 4;
                                L2AcceState = 3;
                                L2MRU = a;
                                LRUL2[L2intindex][cacheconfig.L2setsize] = L2MRU;
                                for (int j = cacheconfig.L2setsize; j >0; j--)
                                    { if(j>=1)
                                        {LRUL2[L2intindex][j-1] = LRUL2[L2intindex][j];}
                                    }
                                    break;
                            }
                            else
                            {
                                L1AcceState = 4;
                                L2AcceState = 4;
                            }
                        }
                }
}
/*
if(k)
{
unsigned long n = cacheconfig.L1setsize;
L1LRU = LRUL1[L1intindex][0]  ;
LRUL1[L1intindex][n] = L1MRU;
for (int i = n; i >0; i--)
{
    LRUL1[L1intindex][i-2] = LRUL1[L1intindex][i-1];
}
tagarrayofL1[L1intindex] [L1LRU] = tagL1inint;
validL1[L1intindex] [L1LRU] = 1;
}

else if(l)
{
unsigned long m = cacheconfig.L2setsize;
L2LRU = LRUL2[L2intindex][0]  ;
LRUL2[L2intindex][m] = L2MRU;
for (int i = m; i >0; i--)
{
    LRUL2[L2intindex][i-2] = LRUL2[L2intindex][i-1];
}
tagarrayofL2[L2intindex] [L2LRU] = tagL2inint;
validL1[L2intindex] [L2LRU] = 1;
}
*/
            tracesout<< L1AcceState << " " << L2AcceState << endl;  // Output hit/miss results for L1 and L2 to the output file;
                L1AcceState = 0;
                L2AcceState = 0;
        }
        traces.close();
        tracesout.close();
    }
    else cout<< "Unable to open trace or traceout file ";
    return 0;
}
