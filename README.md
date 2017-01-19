# primeNumber
素数を高速に解くプログラム  

# 手法
1. アルゴリズムの改善  
2. 並列化  
3. メモリの連続アクセス + キャッシュの有効活用  
4. SIMD  

# DEMO
OpenMPを使った並列処理のプログラム  
sh gcc_prallel.sh  
./a.out 10 (RUNFILE ThreadsNum) 

並列処理なしのプログラム  
sh gcc_seq.sh  
./a.out  

# PROGRAM
並列処理なしのプログラム  
sequentially_main.c  

OpenMPを使った並列処理のプログラム  
prallel_main.c  
