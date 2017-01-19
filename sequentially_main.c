#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//プロトタイプ宣言
int measurement(long maxValue, long *data);
void setCSVFile(long maxValue, long *data, long primeNumberNum);

//素数
int measurement(long maxValue, long *data){
  long i, j;
  long primeNumberNum = 0;
  int flag = 0;

  data[primeNumberNum++] = 2;
  data[primeNumberNum++] = 3;
  data[primeNumberNum++] = 5;

  for(i = 7; i <= maxValue; i+=2){
    for(j = 3; j * j <= i; j++){
      if(i % j == 0){
        flag = 1;
        break;
      }
    }
    if(flag == 0){
      data[primeNumberNum] = i;
      primeNumberNum += 1;
    }else{
      flag = 0;
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

  sprintf(FilePath, "./data/primeNumber_%ld.csv", maxValue);
  if((FilePointer = fopen(FilePath, "w")) == NULL) {
    printf("csv file open error!!\n");
    exit(EXIT_FAILURE);
  }else{
    printf("CSVFilePath     %s\n", FilePath);
    sprintf(Msg, "ID, PrimeNumber\n");
    fputs(Msg, FilePointer);
  }

  for(i = 0; i < primeNumberNum; i++){
    sprintf(Msg, "%d, %ld\n", (i + 1), data[i]);
    fputs(Msg, FilePointer);
  }
}

int main(int argc, char *argv[]){
  long maxValue;
  long *data;
  long primeNumberNum;
  clock_t start, end;

  puts("求める素数の最大値を入力");
  scanf("%ld", &maxValue);
  
  //配列作成
  data = (long *)malloc(sizeof(long) * maxValue);
  
  start = clock();
  
  //素数計算
  primeNumberNum = measurement(maxValue, data);

  end = clock();

  //CSVファイルに書き込み
  setCSVFile(maxValue, data, primeNumberNum);

  //結果表示
  puts("\n-------------------------------");
  printf("Time           is %lf (sec)\n", (double)(end - start) / CLOCKS_PER_SEC);
  
  printf("primeNumberNum is %ld (pieces)\n", primeNumberNum);

  return 0;
}