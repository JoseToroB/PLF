#include <stdio.h>
#include <string.h>
#include <ctype.h>
//palabras reservadas en mayuscula para printear y en minuscula para comparar
char PRES[30][10]={"PROGRAM","CONST","TYPE","VAR","INTEGER","REAL","BOOLEAN","PROCEDURE","FORWARD","FUNCTION","BEGIN","END","IF","THEN","ELSE","CASE","OF","WHILE","DO","FOR","TO","DOWNTO","REPEAT","UNTIL","OR","DIV","MOD","AND","NOT"};
char pres[30][10]={"program","const","type","var","integer","real","boolean","procedure","forward","function","begin","end","if","then","else","case","of","while","do","for","to","downto","repeat","until","or","div","mod","and","not"};
char sres[19][5]={";",".","=",":",",","+","-","'","(",")","<",">","*","/","..",":=","<=","<>",">="};
int esEntero(char* s){
    int i;
    int l=strlen(s);
    int l2=0;
    for(i=0;i<l;i++){
        if(isdigit(s[i])){
            l2++;
        }
    }
    if(l==l2){
        return 1;
    }
    return 0;
}
int esDecimal(char*s){
    int l=strlen(s);
    int i;
    int cantidadpuntos=0;//si esta bandera es distinto a 1, entonces no es decimal
    int digitos=0;//esta bandera debe terminal como l-1 en su valor final
    for(i=0;i<l;i++){
        if(s[i]=='.'){
            cantidadpuntos++;
        }
        if(isdigit(s[i])){
            digitos++;
        }
    }
    if((cantidadpuntos==1)&&(digitos==(l-1))){//si es distinto a 1, entonces no es decimal
        return 1;
    } 
    return 0;
    
}
int revisartexto(char* s,char* nombre){
    FILE * salida;
    salida = fopen(nombre, "w");//creo el archivo de salida
    int i;
    
    //primero reviso si corresponde tal cual esta a una de las palabras reservadas
    for(i=0;i<30;i++){
        if(strcmp(s,pres[i])==0){
            //printf("%s despues\n",PRES[i]);  //cambiar a fprint
            return 0;
        }
    }
    //ahora reviso si es un simbolo reservado
    for(i=0;i<19;i++){
        if(strcmp(s,sres[i])==0){
            //cambiar a fprin printf("%s\n",s);
            return 0;
        }
    }
    //en otro caso reviso si corresponde a algun tipo de dato como identificador, digito,etc
    //si es entero, se imprimira int largo=strlen(s);//se obtiene el largo del string para recorrerlo
    esEntero(s);
    esDecimal(s);
    /*
    esIdentificador();
    esExpo();
    */
    //sino, reviso caracter a caracter
    return 0;

}
FILE * leerArchivo(char* nombreArchivo){
    FILE* archivo = NULL;
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL){
        return 0;
    } else {
        return(archivo);
    }
}

int existeArchivo(char* nombreArchivo){
    FILE* archivo = NULL;
    archivo = fopen(nombreArchivo, "r"); 
    if (archivo == NULL){ 
        return 0;
    } 
    return 1;

}
void crearArchivoSalida(FILE * archivoEntrada, char* nombreArchivoSalida){
    
    char texto[100];
    int resultado;
    while(fscanf(archivoEntrada,"%s",&texto)!= EOF) {
        //Se busca la palabra leida en el conjunto de terminales
        resultado=revisartexto(texto,nombreArchivoSalida);
        
    }
    fclose(archivoEntrada);
}

int main(int argc,char* argv[]) {

    //Se verifica que se hayan ingresado dos parametros de entrada
    if(argc == 1){
        printf("Error: Faltan par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 0;
    }
    //En caso falte un parametro
    if(argc == 2) {
        printf("Error: Falta par%cmetro.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 0;
    }
    //En caso que se hayan ingresado parametros extra
    if(argc > 3) {
        printf("Demasiados par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 0;
    }

    FILE* archivoEntrada = leerArchivo(argv[1]);

    //Si la funcion leerArchivo devuelve un 0 es porque el archivo no existe o el nombre fue mal ingresado.
    if(archivoEntrada == 0){
        printf("Error: El archivo de entrada no existe.\n");
        return 0;
    }
    //Se verifica en caso el archivo de salida ya exista
    if(existeArchivo(argv[2]) == 1){
        printf("Error: El archivo de salida ya existe.\n");
        return 0;
    }
    //Se escribe el archivo de salida
    crearArchivoSalida(archivoEntrada,argv[2]);
    
    return 0;
}