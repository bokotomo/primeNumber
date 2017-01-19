#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//プロトタイプ宣言
int measurement(long maxValue, long *data);
void setCSVFile(long maxValue, long *data, int primeNumberNum);

//素数
int measurement(long maxValue, long *data){
  long i,b;
  int primeNumberNum = 0;
  long flag = 0;

  data[primeNumberNum++] = 2;
  data[primeNumberNum++] = 3;
  data[primeNumberNum++] = 5;

  for(i = 7; i <= maxValue; i+=2){
    for(b = 7; b * b <= i; b++){
      if(i%b == 0){
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
void setCSVFile(long maxValue, long *data, int primeNumberNum){
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
  int primeNumberNum;
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

  printf("time   is %f秒\n", (double)(end - start) / CLOCKS_PER_SEC);
  return 0;
}