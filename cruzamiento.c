#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Pi 3.1416
void obten_aptitudes(),ordena(),imprime_poblacion(),cruzamiento(),imprime_poblacion_cruzada();
float ** genera_poblacion();
int MayorEntero(float);
int main(){
	int tam_poblacion;
	float **poblacion=NULL;
	float a,b,precision;
	int tam_cromosoma;
	poblacion=genera_poblacion(poblacion,&tam_poblacion,&tam_cromosoma,&a,&b,&precision);
	obten_aptitudes(poblacion,tam_poblacion,tam_cromosoma,&a,&b,&precision);
	return 0;
}

float** genera_poblacion(float** poblacion,int* tam_poblacion,int* tam_cromosoma,float *a,float *b,float *precision){
	float temp=0;
	printf("\n\nTamaño de la poblacion: ");
	scanf("%d",tam_poblacion);
	while(*tam_poblacion%2!=0 || *tam_poblacion==0){
		system("clear");
		printf("Tamaño de la poblacion: ");
		scanf("%d",tam_poblacion);
	}
	printf("\n Ingrese presicion: ");
	scanf("%f",precision);
	printf("\n Ingrese a: ");
	scanf("%f",a);
	printf("\n Ingrese b: ");
	scanf("%f",b);
	temp=log(abs((*b)-(*a))*(*precision))/(log(2));
	*tam_cromosoma=MayorEntero(temp);
	printf("\nTamaño cromosoma: %d\n\n",*tam_cromosoma);
	poblacion=(float **)malloc(sizeof(float *)*(((*tam_poblacion)*2)));
	int i=0,j=0;
	while(i<(*tam_poblacion)*2){
		j=0;
		*(poblacion+i)=(float *)malloc(sizeof(float)*(*tam_cromosoma+2));
		while(j<*tam_cromosoma){
			*(*(poblacion+i)+j)=rand()%2;
			j++;
		}
		i++;
	}
	return poblacion;
}
int MayorEntero(float temp){
	int t=(int)temp;
	if(temp>t){
		return(t+1);
	}
	else{
		return(t);
	}
}
void obten_aptitudes(float** poblacion,int tam_poblacion,int tam_cromosoma,float *a,float *b,float *precision){
	int i=0,j=0;
	float dec,x=0;
	printf("POBLACION BASE NO ORDENADA\n====================================\n");
	printf("Cromosoma\tAptidud\n");
	while(i<tam_poblacion){
		dec=0;
		j=0;
		while(j<tam_cromosoma){
			if(j<tam_cromosoma){
				dec+=(*(*(poblacion+i)+j))*pow(2,tam_cromosoma-1-j);
				x=((*a)+(dec)*abs(*b-*a))/(pow(2,*precision)-1);
				*(*(poblacion+i)+tam_cromosoma)=x*sin(10*Pi*x)+1.0;
			}
			printf("%.0f",*(*(poblacion+i)+j));
			j++;
		}
		printf("\t\t%.3f",*(*(poblacion+i)+tam_cromosoma));
		printf("\n");
		i++;
	}
	ordena(poblacion,tam_poblacion,tam_cromosoma,a,b,precision);
}

void ordena(float** poblacion,int tam_poblacion,int tam_cromosoma,float *a,float *b,float *precision){
	int i=0,j=0;
	while(i<(tam_poblacion-1)){
		for(j=0;j<tam_poblacion-1;j++){
			if((*(*(poblacion+j)+tam_cromosoma))<(*(*(poblacion+(j+1))+tam_cromosoma))){
				float *tmp=(float*)malloc(sizeof(float)*tam_cromosoma);
				tmp=*(poblacion+j+1);
				*(poblacion+j+1)=*(poblacion+(j));
				*(poblacion+(j))=tmp;
			}
		}
		i++;
	}
	imprime_poblacion(poblacion,tam_poblacion,tam_cromosoma);
	cruzamiento(poblacion,tam_poblacion,tam_cromosoma,a,b,precision);
}
void cruzamiento(float** poblacion,int tam_poblacion,int tam_cromosoma,float *a,float *b,float *precision){
	int i=0,k=0,j=0;
	int cruce=tam_cromosoma/2;
	while(i<tam_poblacion){
		k=0;
		while(k<2){
			if(k==0){
				j=0;
				while(j<tam_cromosoma){
					if(j<cruce){
						*(*(poblacion+(tam_poblacion+i))+j)=*(*(poblacion+i)+j);
					}
					else{
						*(*(poblacion+(tam_poblacion+i))+j)=*(*(poblacion+(i+1))+j);	
					}
					j++;
				}
			}
			else{
				j=0;
				while(j<tam_cromosoma){
					if(j<cruce){
						*(*(poblacion+(tam_poblacion+i))+j)=*(*(poblacion+i)+j);
					}
					else{
						*(*(poblacion+(tam_poblacion+i))+j)=*(*(poblacion+(i-1))+j);
					}
					j++;
				}
			}
			k++;
			i++;
		}
	}
	imprime_poblacion_cruzada(poblacion,tam_poblacion*2,tam_cromosoma);	
}
void imprime_poblacion(float** poblacion,int tam_poblacion,int tam_cromosoma){
	printf("Cromosoma\tAptidud\n");
	int i,j;
	i=0;
	while(i<tam_poblacion){
		j=0;
		while(j<tam_cromosoma){
			printf("%.0f",*(*(poblacion+i)+j));
			j++;
		}
		printf("\t\t%.3f",*(*(poblacion+i)+tam_cromosoma));
		printf("\n");
		i++;
	}
}
void imprime_poblacion_cruzada(float** poblacion,int tam_poblacion,int tam_cromosoma){
	printf("Cromosoma\tAptidud\n");
	int i,j;
	i=tam_poblacion/2;
	while(i<tam_poblacion){
		j=0;
		while(j<tam_cromosoma){
			printf("%.0f",*(*(poblacion+i)+j));
			j++;
		}
		printf("\t\t%.3f",*(*(poblacion+i)+tam_cromosoma));
		printf("\n");
		i++;
	}
}

