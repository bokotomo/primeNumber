# primeNumber
素数を高速に解くプログラム  

# 手法
1. アルゴリズムの改善  
2. 並列化  
3. メモリの連続アクセス + キャッシュの有効活用  
4. SIMD  

# DEMO
・OpenMPを使った並列処理のプログラム  
sh gcc_prallel.sh  
./a.out 10 (RUNFILE ThreadsNum) 

・並列処理なしのプログラム  
sh gcc_seq.sh  
./a.out  

# PROGRAM
・OpenMPを使った並列処理のプログラム  
prallel_main.c  

・並列処理なしのプログラム  
sequentially_main.c  

# Performance at the moment
0 - 10,000,000(Number of natural numbers)  
###・2.1GHz, 36(core)  
1thread ---------- 18.15(sec)  
36threads -------- 0.7118(sec)  
36threads(numa) -- 0.7116(sec) (numactl --interleave=all ./a.out 36)  

###・2.4GHz, 28(core)  
1thread ---------- 16.25(sec)  
28threads -------- 0.82(sec)  