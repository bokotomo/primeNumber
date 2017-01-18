#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 5000

//プロトタイプ宣言
int measurement(long n, long *data);
void setCSVFile(long n, long *data, int primeNumberNum);

//素数
int measurement(long n, long *data){
  long i;
  long b;
  int primeNumberNum = 0;
  long temp = 0;

  for(i=2;i<=n;i++){
    for(b=1;b<=n;b++){
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
  return primeNumberNum;
}

//CSVファイル書き出し
void setCSVFile(long n, long *data, int primeNumberNum){
  int i;
  FILE *FilePointer;
  char FilePath[100];
  char Msg[100];

  sprintf(FilePath, "./sosu_%ld.csv", n);
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
  long n;
  long *data;
  int primeNumberNum;
  
  data = (long *)malloc(sizeof(long) * NUM);

  puts("求める素数の最大値を入力");
  scanf("%ld", &n);
  
  //素数計算
  primeNumberNum = measurement(n, data);

  //CSVファイルに書き込み
  setCSVFile(n, data, primeNumberNum);

  return 0;
}