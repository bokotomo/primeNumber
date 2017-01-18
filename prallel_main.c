#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM 5000

//プロトタイプ宣言
int getNowThreadsNum();
int measurement(long maxValue, long *data);
void setCSVFile(long maxValue, long *data, long primeNumberNum);

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

//素数
int measurement(long maxValue, long *data){
  long i;
  long b;
  long primeNumberNum = 0;
  long temp = 0;
  int threadsNum = getNowThreadsNum();

  #pragma omp parallel num_threads(threadsNum)
  {
    #pragma omp for private(i,b,temp)
    for(i=2;i<=maxValue;i++){
      for(b=1;b<=maxValue;b++){
        if(i%b==0){
          temp++;
        }
      }
      if(temp<3){
        data[primeNumberNum] = i;
        primeNumberNum++;
      }
      temp=0;
    }
  }
  return primeNumberNum;
}

//CSVファイル書き出し
void setCSVFile(long maxValue, long *data, long primeNumberNum){
  int i;
  FILE *FilePointer;
  char FilePath[100];
  char Msg[100];

  sprintf(FilePath, "./sosu_%ld.csv", maxValue);
  if((FilePointer = fopen(FilePath, "w")) == NULL) {
    printf("csv file open error!!\n");
    exit(EXIT_FAILURE);
  }else{
    printf("CSVFilePath     %s\n", FilePath);
    sprintf(Msg, "ID, 素数\n");
    fputs(Msg, FilePointer);
  }

  for(i = 0; i < primeNumberNum; i++){
    sprintf(Msg, "%d, %ld\n", (i + 1), data[i]);
    fputs(Msg, FilePointer);
  }
}

int main(int argc, char *argv[]){
  double startTime = 0.0, endTime = 0.0, resultTime = 0.0;
  long maxValue;
  long *data;
  long primeNumberNum;
  
  puts("求める素数の最大値を入力");
  scanf("%ld", &maxValue);

  setThreadsNum(28);

  data = (long *)malloc(sizeof(long *) * maxValue);

  startTime = omp_get_wtime();

  //素数計算
  primeNumberNum = measurement(maxValue, data);

  endTime = omp_get_wtime();
  resultTime = (double)(endTime - startTime);
  printf("Time is %lf (sec)\n", resultTime);
  
  printf("素数の数は %ld (個)\n", primeNumberNum);
  
  //CSVファイルに書き込み
  setCSVFile(maxValue, data, primeNumberNum);

  return 0;
}