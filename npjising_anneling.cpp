#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <random>

#define N 300

using namespace std;

int CheckE(int *Spin,int *J){

    int Echk=0,i,j;
    for(i=0; i<N; i++)
        for(j=i+1; j<N; j++)
            Echk += J[i*N + j] * Spin[i] * Spin[j];

    return Echk;





}

double uni01(){

     return ((double) rand() / (RAND_MAX)) ;

}

int main(int argc,char* argv[]){

    //if(argc < 2){   printf("%s","ERROR! No input for solve.\n"); return 1;}

    ///define variables
    int Spin[N],SpinAns[N];

    int *Field=(int*)calloc(N,sizeof(int));

    int *J =(int*)calloc(N*N,sizeof(int));
    int i,j,k;
    int Enr , EnrAns=999999;

    int dE;




     ///read file:
    if(argc<2){cout << "Please give the input."<<endl ; return -2;}


    FILE* inputfile =fopen(argv[1], "r");
    if (!inputfile) {
        printf("InteractionConstantFile: %s not found.\n", argv[1]);
        return -1;
    }

    while (fscanf(inputfile, "%d %d %d", &i, &j, &k) != EOF)
        J[i*N + j] = J[j*N + i] = k;

    fclose(inputfile);





    double T0=0.;
    double T1=8.;
    int Step = 100;
    double Tstep = (T1-T0)/Step;
    int eqmcs = 1000;

    double invT;
    int is;

//for(int rel=0;rel<100;rel++){

for(int r=0;r<100;r++){
    ///initial status
    Enr = 0 ;
    memset(Field,0,sizeof(int)*N);



    ///init configuration:
    for(i=0;i<N;i++)
        Spin[i] = 1 - 2*(rand()%2);

    ///calculate field:
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            Field[i] += Spin[j]*J[i*N+j];

    ///Enr:
    for(i=0;i<N;i++)
        Enr += Spin[i] * Field[i];

    Enr/=2;


    ///start anneling:
    for(int tt=0;tt<Step;tt++){
        invT = 1./(T1 - Tstep*tt);
        for(int cnt=0; cnt<eqmcs; cnt++){

            ///propose update:

                 is = rand()%N;
                 dE = -2*Spin[is]*Field[is];
                 //cout << uni01()<<endl;
                 if(uni01() < exp(-invT*dE)){
                    Enr += dE;
                    Spin[is]*=-1;
                    ///update fields
                    for( i=0;i<N;i++){
                        if(i==is) continue;
                        Field[i] += 2*Spin[is]*J[i*N+is];
                    }

                 }


        }


    }
    //cout << "Enr :" << Enr<<endl;
    //cout << "Echeck : " << CheckE(Spin,J) << endl;
    if(Enr < EnrAns){
        EnrAns = Enr;
        memcpy(SpinAns,Spin,sizeof(int)*N);
    }

}


     printf("%s","v");
     for(i=0;i<N;i++)
        printf(" %d",SpinAns[i]);
     /*
    cout << endl;

    cout << "Enr :" << EnrAns<<endl;
    cout << "Echeck : " << CheckE(SpinAns,J) << endl;
     */



}
