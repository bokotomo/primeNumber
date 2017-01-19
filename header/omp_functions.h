int getNowThreadsNum();
void setThreadsNum(int threadsNum);

int getNowThreadsNum(){
  int threadsNum;

  #pragma omp parallel
  {
    #pragma omp single
    {
      threadsNum = omp_get_num_threads();
    }
  }
  return threadsNum;
}

//スレッド数の設定
void setThreadsNum(int threadsNum){
  omp_set_num_threads(threadsNum);

  #pragma omp parallel num_threads(threadsNum)
  {
    #pragma omp single
    {
      printf("ThreadsNum/ThreadsMax = %d/%d\n", omp_get_num_threads(), omp_get_max_threads());
    }
  }  
}