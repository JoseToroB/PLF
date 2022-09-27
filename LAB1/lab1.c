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
int esIdentificador(char* s){
    //para que una entrada sea identificador debe cumplir con tener solo alfanumericos y _ ademas de no comenzar con un digito
    //ya que en la imagen se entiende que un identificador puede comenzar con _ o letra, luego puede terminar, contare ese caso como posible
    //es decir, _ ya es un identificador por si solo, ademas de que este caracter no es reservado ni utilizado en los simbolos, no deberia ser problema con ello
    int l=strlen(s);
    int i;
    //revisamos los casos en que no comience con una letra o con un _
    if((isalpha(s[0]))||(s[0]=='_')){//si comienza con letra o _ se revisa el resto
        int contador=0;//ya revise la primera pos pero la revisare denuevo igualmente
        for(i=0;i<l;i++){//ahora recorrere todo el string
            if((isalpha(s[i]))||('_'==s[i])||(isdigit(s[i]))){//es letra,_ o numero
                contador++;
            }
        }
        //terminado de revisar el string completo, reviso si todo concuerda
        if(contador==l){
            return 1;//si el revise todo el string y todo este concuerda con el formato, si es identificador
        }
    }
    return 0;//si no comienza con letra o _, no es identificador
    
    
    //si estaba compuesto solo por 
}
int esExpo(char*s){
    //enteroE+entero o -
    //decimalE+entero o -
    //es decir, maximo un punto, una E, 1 simbolo + o - y solamente digitos luego
    //como no se si se acepta enteroEentero , es decir sin simbolo, no lo considero valido, es decir, si o si debe llevar signo positivo o negativo
    int i;
    int l=strlen(s);
    int contadorE=0;
    int contadorPto=0;
    int contadorSigno=0;
    int contadorNumb=0;
    //al finalizar de revisar los contadores sumados deben ser = a l, contadorE, contadorSigno y contadorPto no deben ser mayores que 1
    for(i=0;i<l;i++){
        if(s[i]=='E'){//E
            if(contadorE==1){//si entra denuevo y el contador ya es 1, significa que encontro una segunda coincidencia
                return 0;
            }
            contadorE++;
        }
        if((s[i]=='+')||(s[i]=='-')){//signo
             if(contadorSigno==1){//si entra denuevo y el contador ya es 1, significa que encontro una segunda coincidencia
                return 0;
            }
            contadorSigno++;
        }
        if(s[i]=='.'){//punto
            if(contadorPto==1){//si entra denuevo y el contador ya es 1, significa que encontro una segunda coincidencia
                return 0;
            }
            contadorPto++;
        }
        if(isdigit(s[i])){//digitos
            contadorNumb++;
        }
    }
    int total=contadorE+contadorNumb+contadorPto+contadorSigno;
    //reviso igualmente que cumplan el formato
    if((contadorE==1)&&(contadorPto==1)&&(contadorSigno==1)&&(total==l)){
        return 1;
    }
    return 0;//si no cumple se retorna 0
}

int revisartexto(char* s,char* nombre){
    FILE * salida;
    salida = fopen(nombre, "w");//creo el archivo de salida
    int i;
    
    //primero reviso si corresponde tal cual esta a una de las palabras reservadas
    for(i=0;i<30;i++){
        if(strcmp(s,pres[i])==0){
            //printf("%s despues\n",PRES[i]);  //cambiar a fprint
            return 1;
        }
    }
    //ahora reviso si es un simbolo reservado
    for(i=0;i<19;i++){
        if(strcmp(s,sres[i])==0){
            //cambiar a fprin printf("%s\n",s);
            return 1;
        }
    }
    //en otro caso reviso si corresponde a algun tipo de dato como identificador, digito,etc
    if(esEntero(s)){
       // printf("%s es entero\n",s); cambiar a fprint
        return 1;
    }
    if(esDecimal(s)){
        // printf("%s es decimal\n",s); cambiar a fprint
        return 1;
    }
    if(esIdentificador(s)){
        // printf("%s es identificador\n",s); cambiar a fprint
        return 1;
    }
    if(esExpo(s)){
        // printf("%s es expo\n",s); cambiar a fprint
        return 1;
    }
    //sino, reviso caracter a caracter
    //primero creare un buffer para almacenar lo leido, con el largo correspondiente +1
    int l=strlen(s);
    char* buffer=(char*)malloc(sizeof(char)*(l+1));
    //con esto revisare los casos donde vengan cosas juntas por ejemplo for123, entregando en el archivo de salida FOR\nENTERO\n
    
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