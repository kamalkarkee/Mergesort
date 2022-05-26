// Compile
// gcc test.c -o test
// Run
// ./test < inputfile
//compilation used in OMEGA

#include <stdio.h>
#include <stdlib.h>

// global
int *values, *work, *link, *OI, *LI;

int merge(int *in1,int *in2,int *out1,int in1Size,int in2Size)
// Merge (union with duplicates) for two ordered tables in1 and in2
// to give out1.
{
int i,j,k;

i=j=k=0;
while (i<in1Size && j<in2Size)
  if (in1[i]<in2[j])
    out1[k++]=in1[i++];
  else
    out1[k++]=in2[j++];
if (i<in1Size)
  for ( ;i<in1Size;i++)
    out1[k++]=in1[i];
else
  for ( ;j<in2Size;j++)
    out1[k++]=in2[j];
return k;
}
//link list for mergesort
int merge2(int *in1, int *in2, int *li1, int *li2, int *out1, int in1Size, int in2Size)
{
  int i, j, k;
  i = j = k = 0;

  while (i<in1Size && j<in2Size)
    if (in1[i] <= in2[j])
      out1[k++] = li1[i++];
    else
      out1[k++] = li2[j++];
  if (i < in1Size)
  {
    for ( ; i<in1Size-1; i++)
      out1[k++] = li1[i];
    out1[k++] = -1;
  }
  else
  {
    for ( ; j<in2Size-1; j++)
      out1[k++] = li2[j];
    out1[k++] = -1;
  }
  return out1[0];
}

int mergesort(int start, int count) //mergesort variable
{
  int nleft, nright, i;
  if (count<2) return -1;
  
  nleft = count/2;
  nright = count-nleft;
  
  for (i=0; i<count; i++)
    work[i] = values[i];
    LI[i] = OI[i];

  
  mergesort(*LI, nleft);
  mergesort(*(LI+nleft), nright);
  return merge2(work, work+nleft, LI, LI+nleft, link, nleft, nright);
}

int main()
{
  int n, i, r;
  // read n, number of elements
  scanf("%d", &n);
  // set up subscript values / index numbers
  work = (int *) malloc(n*sizeof(int));
  values = (int *) malloc(n*sizeof(int));
  link = (int *) malloc(n*sizeof(int));
  OI = (int *) malloc(n*sizeof(int));
  LI = (int *) malloc(n*sizeof(int));


  // check if malloc worked
  if(!work || !values || !link || !OI || !LI){
    printf("malloc failed\n");
    exit(0);
  }
  // read elements
  for(i=0; i<n; i++){
    OI[i] = i;
    scanf("%d\n", &values[i]);
  }

  r = mergesort(link[0], n);

  printf("First element is at subscript %d\n", r);
  for(i=0; i<n; i++){
    printf("%d\t%d\t%d\n", OI[i], values[i], link[i]);
  }

  // free memory
  free(values);
  free(work);
  free(link);
  free(OI);
  free(LI);
}