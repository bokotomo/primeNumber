#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "header/qsort.h"
#include "header/omp_functions.h"

//プロトタイプ宣言
int measurement(long maxValue, long *data);
void setCSVFile(long maxValue, long *data, long primeNumberNum);

//素数
int measurement(long maxValue, long *data){
  long i, j;
  long primeNumberNum = 0;
  int flag = 0;
  int threadsNum = getNowThreadsNum();

  data[primeNumberNum++] = 2;

  #pragma omp parallel num_threads(threadsNum),shared(primeNumberNum)
  {
    #pragma omp for private(i,j,flag),reduction(+:primeNumberNum)
    for(i = 3; i <= maxValue; i += 2){
      for(j = 3; j * j <= i; j++){
        if(i % j == 0){
          flag = 1;
          break;
        }
      }
      if(flag == 0){
        //printf("%ld\n", (long)maxValue/threadsNum * omp_get_thread_num() + primeNumberNum);
        data[(long)maxValue/threadsNum * omp_get_thread_num() + primeNumberNum + 1] = i;
        primeNumberNum++;
      }else{
        flag = 0;
      }
    }
  }
  return primeNumberNum;
}

//CSVファイル書き出し
void setCSVFile(long maxValue, long *data, long primeNumberNum){
  int i,j=1;
  FILE *FilePointer;
  char FilePath[100];
  char Msg[100];

  sprintf(FilePath, "./data/primeNumber_%ld.csv", maxValue);
  if((FilePointer = fopen(FilePath, "w")) == NULL) {
    printf("csv file open error!!\n");
    exit(EXIT_FAILURE);
  }else{
    printf("CSVFilePath     %s\n", FilePath);
    sprintf(Msg, "ID, PrimeNumber\n");
    fputs(Msg, FilePointer);
  }

  for(i = maxValue-primeNumberNum; i < maxValue; i++){
    sprintf(Msg, "%d, %ld\n", j++, data[i]);
    fputs(Msg, FilePointer);
  }
}

int main(int argc, char *argv[]){
  double startTime = 0.0, endTime = 0.0, resultTime = 0.0;
  long maxValue;
  long *data;
  long primeNumberNum;
  int threadsNum;
  
  puts("求める素数の最大値を入力");
  scanf("%ld", &maxValue);

  //スレッド数の設定
  threadsNum = atoi(argv[1]);
  setThreadsNum(threadsNum);

  //格納用配列宣言
  data = (long *)malloc(sizeof(long *) * maxValue);

  //計測
  startTime = omp_get_wtime();

  //素数計算
  primeNumberNum = measurement(maxValue, data);

  endTime = omp_get_wtime();
  resultTime = (double)(endTime - startTime);

  //ソート
  QSort(data, 0, maxValue - 1);

  //CSVファイルに書き込み
  setCSVFile(maxValue, data, primeNumberNum);

  //結果表示
  puts("\n-------------------------------");
  printf("Time           is %lf (sec)\n", resultTime);
  
  printf("primeNumberNum is %ld (pieces)\n", primeNumberNum);
  
  return 0;
}