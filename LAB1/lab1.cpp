#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

string alfa="abcdefghijklmnñopqrstuvwxyzáéíóú ";

int mul_mat(int k, int m, int n){
    uint32_t A[k][m], B[m][n], C[k][n];


    for(int i=0; i<k; ++i)
        for(int j=0; j<m; ++j)
        {
            A[i][j]=rand()%10;
        }


    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
        {
            B[i][j]=rand()%10;
        }

    for(int i=0; i<k; ++i)
        for(int j=0; j<n; ++j)
            C[i][j] = 0;

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    for(int i=0; i<k; ++i){
        for(int j=0; j<n; ++j){
            for(int z=0; z<m; ++z){
                C[i][j] += A[i][z] * B[z][j];
            }
        }
    }
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time para multiplicacion clasica:       %.28f s\n", tiempo/1000);

    /*cout<<"Matriz 1: ";
    for(int i=0; i<k; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Matriz 2: ";
    for(int i=0; i<m; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            cout<<B[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Matriz RESULTADO: ";
    for(int i=0; i<k; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }*/

    return 0;
}

void block_mult(int tam, int l, int m, int n)
{
	uint32_t a[l][m], b[m][n], c[l][n];

    int bi=0;
    int bj=0;
    int bk=0;
    int i=0;
    int j=0;
    int k=0;
    int blockSize=4; 

    for(int i=0; i<l; ++i)
        for(int j=0; j<m; ++j)
        {
            a[i][j]=rand()%10;
        }


    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
        {
            b[i][j]=rand()%10;
        }

    for(int i=0; i<l; ++i)
        for(int j=0; j<n; ++j)
            c[i][j] = 0;

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    for(bi=0; bi<tam; bi+=blockSize)
        for(bj=0; bj<tam; bj+=blockSize)
            for(bk=0; bk<tam; bk+=blockSize)
                for(i=0; i<blockSize; i++)
                    for(j=0; j<blockSize; j++)
                        for(k=0; k<blockSize; k++){
                            c[bi+i][bj+j] += a[bi+i][bk+k]*b[bk+k][bj+j];
                        }

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time multiplicacion por bloques:       %.28f s\n", tiempo/1000);

}

void prueba(int MAX){

	uint32_t A[MAX][MAX], x[MAX], y[MAX];

	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
		  	A[i][j]=rand()%100;
	        x[i]=rand();

		}
    }
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

	for (int i = 0; i < MAX; i++){
		for (int j = 0; j < MAX; j++){
			y[i] += A[i][j]*x[j];
		}
	}

	gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time for 1:       %.28f s\n", tiempo/1000);


    gettimeofday(&ti, NULL);

	for (int j = 0; j < MAX; j++){
		for (int i = 0; i < MAX; i++){
			y[i] += A[i][j]*x[j];
		}
	}
	gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time for 2:       %.28f s\n", tiempo/1000);

}

int main(int argc, char const *argv[])
{
	srand (time(NULL));
	//prueba(1000);
	int x;
	x=200;

	cout<<"Con D="<<x<<endl;

	mul_mat(x, x, x);

	block_mult(x,x,x,x);
	
	x=500;

	cout<<"Con D="<<x<<endl;

	mul_mat(x, x, x);

	block_mult(x,x,x,x);

	return 0;
}
