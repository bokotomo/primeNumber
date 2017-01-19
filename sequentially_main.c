#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//プロトタイプ宣言
int measurement(long n, long *data);
void setCSVFile(long n, long *data, int primeNumberNum);

//素数
int measurement(long n, long *data){
  long i,b;
  int primeNumberNum = 0;
  long temp = 0;

  data[primeNumberNum++] = 2;
  data[primeNumberNum++] = 3;
  data[primeNumberNum++] = 5;

  for(i=7;i<=n;i+=2){
    for(b=7;b*b<=i;b++){
      if(i%b==0){
        temp=1;
        break;
      }
    }
    if(temp==0){
      data[primeNumberNum] = i;
      primeNumberNum += 1;
    }else{
      temp=0;
    }
  }
  return primeNumberNum;
}

//CSVファイル書き出し
void setCSVFile(long n, long *data, int primeNumberNum){
  int i;
  FILE *FilePointer;
  char FilePath[100];
  char Msg[100];

  sprintf(FilePath, "./data/primeNumber_%ld.csv", n);
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
  long n;
  long *data;
  int primeNumberNum;
  

  puts("求める素数の最大値を入力");
  scanf("%ld", &n);
  
  data = (long *)malloc(sizeof(long) * n);
  
  //素数計算
  primeNumberNum = measurement(n, data);

  //CSVファイルに書き込み
  setCSVFile(n, data, primeNumberNum);

  return 0;
}