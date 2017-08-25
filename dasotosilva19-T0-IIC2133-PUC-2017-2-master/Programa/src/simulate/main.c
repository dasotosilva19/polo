#include "../watcher/watcher.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        printf("Debes ingresar los parámetros de ruta de archivo y generaciones de baterias.\n");
        return -1;
    }

    /*char ruta = argv[1];*/
    int generaciones = atoi(argv[2]);


	//ahora procedemos a leer el archivo

	char aux[1000];
	FILE *archivo;
	archivo = fopen(argv[1],"r");

	if(archivo == NULL){
		printf("archivo vacio.\n");
		exit(1);
	}


	//aca definimos el numero de filas y columnas
	fscanf(archivo, "%s", aux);
	int filas = atoi(aux);
	fscanf(archivo, "%s", aux);
	int columnas = atoi(aux);


	//aca armamos la grilla de la población bacteriana
	int** grilla = calloc(filas, sizeof(int*));  // pedimos memoria para N filas

    for (int i = 0; i < filas; i++) {
        int* row = calloc(columnas, sizeof(int));  // pedimos memoria para los M elementos de cada fila
        for (int j = 0; j < columnas; j++) {
        	fscanf(archivo,"%s",aux);
            row[j] = atoi(aux);
        }
        grilla[i] = row; 
    }
    fclose(archivo);


    //empezamos la simulacion

    watcher_open(filas, columnas);

    //vista inicial
	for(int row = 0; row < filas; row++)
	{
		for(int col = 0; col < columnas; col++)
		{
			if(grilla[row][col] == 0){
				watcher_set_cell(row, col, false);
			}

			else if(grilla[row][col] == 1){
				watcher_set_cell(row, col, true);
			}
		}
	}

	watcher_refresh(); 

    for (int k = 0; k < generaciones; k++){
	    for (int i = 0; i < filas; i++) {
	        for (int j = 0; j < columnas; j++) {

	        	int count = 0;

	        	//verificación derecha
	        	if(j < columnas-1){
	        		if(grilla[i][j+1] == 1){
	        			count++;
	        		}
	        	}

	        	else if(j == columnas-1){
	        		if(grilla[i][0] == 1){
	        			count++;
	        		}
	        	}
	 
	 			//verificacion izquierda
	 			if(j > 0){
		        	if(grilla[i][j-1] == 1){
		        		count++;
		        	}
		        }

		        else if(j == 0){
		        	if(grilla[i][columnas-1] == 1){
		        		count++;
		        	}
		        }


		        //verificacion abajo
		        if(i<filas-1){
		        	if(grilla[i+1][j] == 1){
		        		count++;
		        	}
		        }

		        else if(i == filas-1){
		        	if(grilla[0][j] == 1){
		        		count++;
		        	}
		        }


		        //verificación arriba
		        if(i > 0){
		        	if(grilla[i-1][j] == 1){
		        		count++;
		        	}
		        }

		        else if(i == 0){
		        	if(grilla[filas-1][j] == 1){
		        		count++;
		        	}
		        }


		        //verificacion diagonal superior derecha
		        if(i>0 && j < filas-1){
		        	if(grilla[i-1][j+1] == 1){
		        		count++;
		        	}
		        }

		        else if(i>0 && j == filas-1){
		        	if(grilla[i-1][0] == 1){
		        		count++;
		        	}
		        }

		        else if(i==0 && j < filas-1){
		        	if(grilla[filas-1][j+1] == 1){
		        		count++;
		        	}
		        }

		        else if(i==0 && j == filas-1){
		        	if(grilla[filas-1][0] == 1){
		        		count++;
		        	}
		        }


		        //verificación diagonal superior izquierda
		        if(i>0 && j > 0){
		        	if(grilla[i-1][j-1] == 1){
		        		count++;
		        	}
		        }

		        else if(i>0 && j == 0){
		        	if(grilla[i-1][columnas-1] == 1){
		        		count++;
		        	}
		        }

		        else if(i==0 && j > 0){
		        	if(grilla[filas-1][j] == 1){
		        		count++;
		        	}
		        }

		        else if(i==0 && j==0){
		        	if(grilla[filas-1][columnas-1] == 1){
		        		count++;
		        	}
		        }


		        //verificación diagonal inferior izquierda
		        if(i < filas-1 && j>0){
		        	if(grilla[i+1][j-1] == 1){
		        		count++;
		        	}
		        }

		        else if(i < filas-1 && j == 0){
		        	if(grilla[i+1][columnas-1] == 1){
		        		count++;
		        	}
		        }

		        else if(i == filas-1 && j > 0){
		        	if(grilla[0][j-1] == 1){
		        		count++;
		        	}
		        }

		        else if(i == filas-1 && j == 0){
		        	if(grilla[0][columnas-1] == 1){
		        		count++;
		        	}
		        }


		        //verificacion diagonal inferior derecho
		        if(i < filas-1 && j < columnas-1){
		        	if(grilla[i+1][j+1] == 1){
		        		count++;
		        	}
		        }

		        else if(i < filas-1 && j == columnas-1){
		        	if(grilla[i+1][0] == 1){
		        		count++;
		        	}
		        }

		        else if(i == filas-1 && j < columnas-1){
		        	if(grilla[0][j+1] == 1){
		        		count++;
		        	}
		        }

		        else if(i == filas-1 && j == columnas-1){
		        	if(grilla[0][0] == 1){
		        		count++;
		        	}
		        }



	        	//verificacion de generaciones futuras


	        	if(count > 3){
	        		grilla[i][j] = 0;
	        		watcher_set_cell(i, j, false);
	        	}

	        	else if(count < 2){
	        		grilla[i][j] = 0;
	        		watcher_set_cell(i, j, false);

	        	}

	        	else if(count == 3){
	        		grilla[i][j] = 1;
	        		watcher_set_cell(i, j, true);
	        	}

	        	else if(count == 2){
	        		grilla[i][j] = 1;
	        		watcher_set_cell(i, j, true);
	        	}
	        }

	    }

	    watcher_refresh(); 
	}

    // Liberamos cada fila
    for (int i = 0; i < filas; i++) {
        free(grilla[i]);
    }
    // Finalmente liberamos la matriz
    free(grilla);

}